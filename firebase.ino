
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
  // pathPompa1 =  String(pathControlling) + "/pompa_1/state";
  // pathPompa2 =  String(pathControlling) + "/pompa_2/state";
  // pathPompa3 =  String(pathControlling) + "/pompa_3/state";
  // pathExh =  String(pathControlling) + "/exhaust_fan_1/state";
  
}

void get_status() {
  // Firebase.getJSON(fbdo, pathControlling);
  // if (fbdo.dataType() == "json") {
  //     //Serial.println(fbdo.jsonString());  // Debug: Print entire JSON response
  //     FirebaseJson &json = fbdo.jsonObject();
  //     FirebaseJsonData jsonData; 

  //     if (json.get(jsonData, "pompa_1/state")) {
  //         statePompa1 = jsonData.intValue; // Convert and store as int
  //         Serial.printf("Pompa 1: %d\n", statePompa1);
  //     } else {
  //         Serial.println("Failed to get pompa_1/state");
  //     }

  //     if (json.get(jsonData, "pompa_2/state")) {
  //         statePompa2 = jsonData.intValue; // Convert and store as int
  //         Serial.printf("Pompa 2: %d\n", statePompa2);
  //     } else {
  //         Serial.println("Failed to get pompa_2/state");
  //     }

  //     if (json.get(jsonData, "pompa_3/state")) {
  //         statePompa3 = jsonData.intValue; // Convert and store as int
  //         Serial.printf("Pompa 3: %d\n", statePompa3);
  //     } else {
  //         Serial.println("Failed to get pompa_3/state");
  //     }

  //     if (json.get(jsonData, "exhaust_fan_1/state")) {
  //         stateExh = jsonData.intValue; // Convert and store as int
  //         Serial.printf("Exhaust: %d\n", stateExh);
  //     } else {
  //         Serial.println("Failed to get exhaust_1/state");
  //     }
  // } else {
  //     Serial.println("Failed to retrieve JSON or data type is not JSON.");
  //     Serial.println("Error: " + String(fbdo.errorReason())); // Debugging error
  // }

  Firebase.getJSON(fbdo, pathControlling);

    if (fbdo.dataType() == "json") {
        FirebaseJson &json = fbdo.jsonObject();
        FirebaseJsonData jsonData;

        for (auto &device : devices) {
            if (json.get(jsonData, device.path)) {
                device.old_state = device.state;  // Store the current state as the old state before updating
                device.state = jsonData.intValue; // Update the state directly in the device
                Serial.printf("%s: %d\n", device.path, device.state);
            } else {
                Serial.printf("Failed to get %s\n", device.path);
            }
        }
    } else {
        Serial.println("Failed to retrieve JSON or data type is not JSON.");
        Serial.println("Error: " + String(fbdo.errorReason())); // Debugging error
    }

    updateControlStates();

  // if (LED1 != statePompa2) {
  //     controlDevice(GPIO8, statePompa1, 0x00001, LED1, ui_ButtonONOFF1);
  // }
  // if (LED2 != statePompa2) {
  //     controlDevice(GPIO7, statePompa2, 0x00002, LED2, ui_ButtonONOFF2);
  // }
  // if (LED3 != statePompa3) {
  //     controlDevice(GPIO6, statePompa3, 0x00003, LED3, ui_ButtonONOFF3);
  // }
  // if (LED4 != stateExh) {
  //     controlDevice(GPIO5, statePompa3, 0x00004, LED4, ui_ButtonONOFF4);
  // }

  // Read each nutrient data field from Firebase
    // if (Firebase.getFloat(fbdo, pathNutrient + "/target_ec", &target_ec)) {
    //     Serial.printf("Target EC: %.2f\n", target_ec);
    // } else {
    //     Serial.println("Failed to read target_ec: " + String(fbdo.errorReason()));
    // }

    // if (Firebase.getFloat(fbdo, pathNutrient + "/calc_A", &calc_A)) {
    //     Serial.printf("Calc A: %.2f\n", calc_A);
    // } else {
    //     Serial.println("Failed to read calc_A: " + String(fbdo.errorReason()));
    // }

    // if (Firebase.getFloat(fbdo, pathNutrient + "/calc_B", &calc_B)) {
    //     Serial.printf("Calc B: %.2f\n", calc_B);
    // } else {
    //     Serial.println("Failed to read calc_B: " + String(fbdo.errorReason()));
    // }

    // if (Firebase.getString(fbdo, pathNutrient + "/status", &status)) {
    //     Serial.printf("Status: %s\n", status.c_str());
    // } else {
    //     Serial.println("Failed to read status: " + String(fbdo.errorReason()));
    // }

    // if (Firebase.getString(fbdo, pathNutrient + "/time", &times)) {
    //     Serial.printf("Time: %.2f\n", times);
    // } else {
    //     Serial.println("Failed to read time: " + String(fbdo.errorReason()));
    // }
 
}

void updateControlStates() {
    for (auto &device : devices) {
        if (device.state != device.old_state) { 
            controlDevice(device.pin, device.state, device.coil, device.old_state, device.uiButton);
        }
    }
}

void updateFirebaseState(const String &path, int state)
{
    if (Firebase.setInt(fbdo, path, state)) {
        Serial.println("Firebase updated successfully!");
    } else {
        Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
    }
}


void sent_data() {
  json.set("temperatur", temperatureC);
  json.set("RH", RH);
  json.set("kelembaban_tanah_1", valSoil);
  json.set("ec", ec);
  json.set("ph", ph);
  Firebase.setJSON(fbdo, pathMonitoring, json);
}