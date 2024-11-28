
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
    fetchControllingData();
    updateDeviceStates();

    fetchNutrientData();
}

void fetchControllingData(){
  Firebase.getJSON(fbdo, pathControlling);

  if (fbdo.dataType() == "json") {
      FirebaseJson &json = fbdo.jsonObject();
      FirebaseJsonData jsonData;

      for (auto &device : devices) {
          if (json.get(jsonData, device.path)) {
              device.firebase_state = jsonData.intValue; // Update the state directly in the device
              Serial.printf("%s: %d\n", device.path, device.firebase_state);
          } else {
              Serial.printf("Failed to get %s\n", device.path);
          }
      }
  } else {
      Serial.println("Failed to retrieve JSON or data type is not JSON.");
      Serial.println("Error: " + String(fbdo.errorReason())); // Debugging error
  }
}

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
      } else {
          Serial.println("Data is not JSON.");
      }
  } else {
      Serial.println("Failed to fetch JSON: " + fbdo.errorReason());
  }
}

bool readGPIOState(uint8_t gpio) {
    uint8_t inputState = readInput(); // Read the current state of all GPIOs
    return (inputState & gpio) != 0;  // Check if the specified GPIO bit is set
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

void updateDeviceStates() {
    for (auto &device : devices) {
        if (device.firebase_state != device.device_state) { 
            controlDevice(device);
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