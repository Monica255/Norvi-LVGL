

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
    // fetchNutrientData();
}


//FetchState fetchState = FETCH_INIT;
unsigned long fetchStartTime = 0;

void fetchControllingDataNonBlocking() {
    switch (fetchState) {
        case IDLE:
            Serial.println("idlee");
;        case FETCH_INIT:
            if (Firebase.getJSON(fbdo, pathControlling)) {
                fetchState = FETCH_WAIT;
                fetchStartTime = millis();
            } else {
                Serial.println("Failed to start fetching: " + String(fbdo.errorReason()));
                fetchState = FETCH_DONE;
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
                        //Serial.printf("%s: %d\n", device.path, device.firebase_state);
                        
                    } else {
                        Serial.printf("Failed to get %s\n", device.path);
                    }
                }
                fetchState = UPDATE_DEVICE;
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

unsigned long startTime = 0; // To track time
bool isWaiting = false;      // To manage the timing state

void fetchNutrientData() {
  if (Firebase.getJSON(fbdo, pathNutrient)) {
    if (fbdo.dataType() == "json") {
          FirebaseJson &json = fbdo.jsonObject();
          FirebaseJsonData jsonData;

          if (json.get(jsonData, "target_ec") && jsonData.type == "float") {
              nutrient.target_ec = jsonData.floatValue;
          }

          if (json.get(jsonData, "calc_A") && jsonData.type == "float") {
              nutrient.calc_A = jsonData.floatValue;
          }

          if (json.get(jsonData, "calc_B") && jsonData.type == "float") {
              nutrient.calc_B = jsonData.floatValue;
          }

          if (json.get(jsonData, "status") && jsonData.type == "string") {
              nutrient.status = jsonData.stringValue;
          }

          if (json.get(jsonData, "times") && jsonData.type == "float") {
              nutrient.times = jsonData.floatValue;
          }

          Serial.printf("Target EC: %.2f, Calc A: %.2f, Calc B: %.2f, Status: %s, Time: %.2f\n",
                        nutrient.target_ec, nutrient.calc_A, nutrient.calc_B, 
                        nutrient.status.c_str(), nutrient.times);

          if (nutrient.status == "start") {
              startNutrient();
          } else if (nutrient.status == "on progress"){
            bool gpio7State = readGPIOState(GPIO7);
            if (!gpio7State) {
                Serial.println("GPIO7 is OFF. Starting nutrient process...");
                if (!isWaiting) {
                    OnOffDevice(true, devices[3]); // Start device 3
                    startTime = millis();         // Record the start time
                    isWaiting = true;            
                }

                if (ec >= nutrient.target_ec) {
                  Serial.println("EC target reached. Stopping...");
                  OnOffDevice(false, devices[3]); // Turn OFF device 3
                  isWaiting = false;              // Reset timing state
                  updateNutrientState("done");
                }

                if (isWaiting && millis() - startTime >= nutrient.times * 1000) {
                    OnOffDevice(false, devices[3]); // Stop device 3 after the time
                    isWaiting = false;              // Reset waiting state
                    updateNutrientState("done");
                }
            } else if(nutrient.status == "stop"){
                OnOffDevice(false, devices[2]);
                OnOffDevice(false, devices[3]);
            }
          }
      } else {
          Serial.println("Data is not JSON.");
      }
  } else {
      Serial.println("Failed to fetch JSON: " + fbdo.errorReason());
  }
}

void startNutrient(){
  if (ec < nutrient.target_ec) {
      Serial.println("EC is below target, starting automation...");
      updateNutrientState("on progress");
      OnOffDevice(true, devices[2]);
  } else {
      Serial.println("EC is already above the target.");
      updateNutrientState("stop");
  }
}

void updateNutrientState(String state)
{
    if (Firebase.setString(fbdo, pathNutrient + "/status", state)) {
        Serial.println("Firebase updated successfully!");
    } else {
        Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
    }
}

void updateFirebaseState(const String &path, int state)
{
    Serial.println("Firebase updated start!");
    if (Firebase.setInt(fbdo, pathControlling+"/"+path, state)) {
        Serial.println("Firebase updated successfully! "+ String(state));
    } else {
        Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
    }
}

void sent_datarhtemp() {
  json.set("temperatur", temperatureC);
  json.set("humidity", RH);
  Firebase.setJSON(fbdo, pathMonitoring, json);
}

void sent_dataecph() {
  json.set("ec", ec);
  json.set("ph", ph);
  Firebase.setJSON(fbdo, pathMonitoring, json);
}
