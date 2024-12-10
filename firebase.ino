

#include "credentials.h"

#define sensorFrameSize  19
#define sensorWaitingTime 1000

String kebun_id = "kebun1";

FirebaseData fbdo;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig config;

float target_ec;
float calc_A;
float calc_B;
String status;
float times;

void initFirebase() {
  Serial.println("Connection to Firebase");
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  uid = UID; 

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.database_url = DATABASE_URL; 
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
}

void readFirebase(){
  Serial.println("Getting User UID");
  path = "/smart_farming/" + String(uid) + "/realtime_kebun";
  pathMonitoring = String (path) + "/"+ String(kebun_id) +"/monitoring";
  pathNutrient = String (path) + "/"+ String(kebun_id) +"/nutrient";
  pathControlling = String (path) + "/"+ String(kebun_id) +"/controlling";
}

void get_status() {
    fetchControllingDataNonBlocking();
    fetchNutrientData();
    observeNutrientStatus();
}


unsigned long fetchStartTime = 0;
#define firebaseWaitingTime 4000
#define READ_INTERVAL 1500 
void fetchControllingDataNonBlocking() {
    switch (fetchState) {
        case IDLE:
            Serial.println("idlee");
            break;
        case FETCH_INIT:
            if (millis() - fetchStartTime >= READ_INTERVAL) {
                //Serial.println("init fetch con data");
                if (Firebase.getJSON(fbdo, pathControlling)) {
                    fetchState = FETCH_WAIT;
                    fetchStartTime = millis();
                } else {
                    Serial.println("Failed to start fetching: " + String(fbdo.errorReason()));
                    fetchState = FETCH_DONE;
                }
            }
            break;

        case FETCH_WAIT:
            if (fbdo.dataAvailable()) {
                fetchState = FETCH_PROCESS;
            } else if (millis() - fetchStartTime > firebaseWaitingTime) {
                Serial.println("Timeout while waiting for data.");
                fetchState = FETCH_DONE;
            }
            break;

        case FETCH_PROCESS:
            if (fbdo.dataType() == "json") {
                FirebaseJson &json = fbdo.jsonObject();
                FirebaseJsonData jsonData;
                
                for (auto &device : devices) {
                    if (json.get(jsonData, device.path)) {
                        device.firebase_state = jsonData.intValue;
                        Serial.printf("%s: %d\n", device.path, device.firebase_state);
                        fetchState = UPDATE_DEVICE;
                    } else {
                        //Serial.printf("Failed to get %s\n", device.path);
                        fetchState = FETCH_DONE;
                    }
                }
            } else {
                Serial.println("Data type is not JSON.");
                fetchState = FETCH_DONE;
            }
            
            break;
        case UPDATE_DEVICE:
            for (auto &device : devices) {
                bool gpioState = readGPIOState(device.pin);
                //Serial.print(gpioState);
                if (device.firebase_state) {
                    lv_obj_add_state(device.uiButton, LV_STATE_CHECKED); // Turn the button ON
                } else {
                    lv_obj_clear_state(device.uiButton, LV_STATE_CHECKED); // Turn the button OFF
                }
                if (gpioState != device.firebase_state) {
                    Serial.println(device.path);
                    controlDevice(device);

                }
            }
            fetchState = FETCH_DONE;
            break;

        case FETCH_DONE:
            fetchState = FETCH_INIT; // Reset for the next call
            break;
    }
}


enum ObserveStatusState {
    OBSERVE_IDLE,
    OBSERVE_CHECK_STATUS,
    OBSERVE_WAIT_PROCESS
};

ObserveStatusState observeStatusState = OBSERVE_CHECK_STATUS;

unsigned long fetchNutStartTime = 0;
const unsigned long fetchTimeout = 5000;
bool isWaiting1 = false;
bool isWaiting2 = false;  
unsigned long startTime = 0;

FirebaseData fbdo2;
FirebaseJson json2;            
FirebaseJsonData jsonData;

#define READ_INTERVAL_NUT 1000


void fetchNutrientData() {
    switch (fetchNutrientState) {
        case FETCH_IDLE:
            break;

        case FETCH_INIT_NUT:
            if (millis() - fetchNutStartTime >= READ_INTERVAL_NUT) {
                //Serial.println("init fetch nut data");
                if (Firebase.getJSON(fbdo2, pathNutrient)) {
                    fetchNutStartTime = millis();
                    fetchNutrientState = FETCH_WAIT_NUT;
                } else {
                    Serial.println("Failed to fetch JSON: " + fbdo2.errorReason());
                    fetchNutrientState = FETCH_DONE_NUT;
                }
            }
            break;

        case FETCH_WAIT_NUT:
            if (millis() - fetchNutStartTime >= fetchTimeout) {
                Serial.println("Timeout waiting for data.");
                fetchNutrientState = FETCH_DONE_NUT;
            } else if (fbdo2.dataAvailable()) {
                fetchNutrientState = FETCH_GET_JSON;
            }
            break;

        case FETCH_GET_JSON:
            if (fbdo2.dataType() == "json") {
                json2 = fbdo2.jsonObject();
                fetchNutrientState = FETCH_CONVERT_TO_NUTRIENT;
            } else {
                Serial.println("Data is not JSON.");
                fetchNutrientState = FETCH_DONE_NUT;
            }
            break;

        case FETCH_CONVERT_TO_NUTRIENT:
            if (json2.get(jsonData, "target_ec") && jsonData.type == "int") {
                nutrient.target_ec = jsonData.intValue;
            }
            if (json2.get(jsonData, "calc_A") && jsonData.type == "int") {
                nutrient.calc_A = jsonData.intValue;
            }
            if (json2.get(jsonData, "calc_B") && jsonData.type == "int") {
                nutrient.calc_B = jsonData.intValue;
            }
            if (json2.get(jsonData, "status") && jsonData.type == "string") {
                nutrient.status = jsonData.stringValue;
                observeStatusState = OBSERVE_CHECK_STATUS;
            }
            if (json2.get(jsonData, "time") && jsonData.type == "int") {
                nutrient.times = jsonData.intValue;
            }
            Serial.printf("Target EC: %d, Calc A: %d, Calc B: %d, Status: %s, Time: %d\n",
                          nutrient.target_ec, nutrient.calc_A, nutrient.calc_B, 
                          nutrient.status.c_str(), nutrient.times);
            

            fetchNutrientState = FETCH_DONE_NUT;
            break;

        case FETCH_DONE_NUT:
            fetchNutrientState = FETCH_INIT_NUT;
            break;
    }
}

#define READ_INTERVAL_STATUS 500
unsigned long checkStatusStartTime = 0;

void observeNutrientStatus() {
    switch (observeStatusState) {
        case OBSERVE_IDLE:
            break;

        case OBSERVE_CHECK_STATUS:
            if (millis() - checkStatusStartTime >= READ_INTERVAL_STATUS) {
                //Serial.println("obsv cek status");
                checkStatusStartTime = millis();
                if (nutrient.status == "start") {
                    startNutrient();
                } else if (nutrient.status == "on progress") {
                    handleProgressState();
                    observeStatusState = OBSERVE_WAIT_PROCESS;
                } else if (nutrient.status == "stop") {
                    stopDevices();
                    observeStatusState = OBSERVE_IDLE;
                }
            }
            
            break;

        case OBSERVE_WAIT_PROCESS:
            //Serial.println("wait process");
            if (ec >= nutrient.target_ec || (isWaiting2 && millis() - startTime >= nutrient.times * 1000)) {
                OnOffDevice(false, devices[2]);
                isWaiting2 = false;
                startTime = 0;
                updateNutrientState("done");
                nutrient.status = "done";
                observeStatusState = OBSERVE_CHECK_STATUS;
            }
            break;
    }
}

void handleProgressState() {
    //Serial.println("Waiting pompa 2 to off");
    bool gpio7State = readGPIOState(GPIO7);
    if (!gpio7State && isWaiting1) {
        isWaiting1=false;
        //Serial.println("GPIO7 is OFF. Starting nutrient process...");
        if (!isWaiting2) {
            OnOffDevice(true, devices[2]);  // Start device 3
            startTime = millis();           // Record the start time
            isWaiting2 = true;              
        }
    }
}

void stopDevices() {
    bool gpio7State = readGPIOState(GPIO7);
    if (gpio7State){
        OnOffDevice(false, devices[1]);
    }
    bool gpio6State = readGPIOState(GPIO6);
    if (gpio6State){
        OnOffDevice(false, devices[2]);
    }

}

void startNutrient() {
    if (ec < nutrient.target_ec) {
        Serial.println("EC is below target, starting automation...");
        updateNutrientState("on progress");
        nutrient.status = "on progress";
        OnOffDevice(true, devices[1]);  // Start device 2
        isWaiting1 = true;
    } else {
        Serial.println("EC is already above the target.");
        updateNutrientState("stop");
    }
}

void updateNutrientState(String state) {
    if (Firebase.setString(fbdo2, pathNutrient + "/status", state)) {
        //Serial.println("Firebase updated successfully!");
    } else {
        Serial.println("Failed to update Firebase: " + String(fbdo2.errorReason()));
    }
}
FirebaseJson nutrientJson;
void updateNutrientData(Nutrient nut) {
    // Serialize the Nutrient struct to JSON
    nutrientJson.clear();
    nutrientJson.set("target_ec", nut.target_ec);
    nutrientJson.set("calc_A", nut.calc_A);
    nutrientJson.set("calc_B", nut.calc_B);
    nutrientJson.set("status", nut.status);
    nutrientJson.set("time", nut.times);

    // Push the JSON object to Firebase
    if (Firebase.setJSON(fbdo, pathNutrient, nutrientJson)) {
        Serial.println("Nutrient data updated successfully.");
    } else {
        Serial.println("Failed to update nutrient data: " + fbdo.errorReason());
    }
}

void updateFirebaseState(const String &path, int state)
{
    if (Firebase.setInt(fbdo, pathControlling+"/"+path, state)) {
        // Serial.println("Firebase updated successfully! "+ String(state));
    } else {
        Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
    }
}

void sent_datarhtemp() {
  json.set("temperatur", temperatureC);
  json.set("humidity", RH);
  // json.set("kelembaban_tanah", valSoil);
  Firebase.setJSON(fbdo, pathMonitoring, json);
}

void sent_dataecph() {
  json.set("ec", ec);
  json.set("ph", ph);
  Firebase.setJSON(fbdo, pathMonitoring, json);
}

