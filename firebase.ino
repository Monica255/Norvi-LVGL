

#include "credentials.h"

#define sensorFrameSize  19
#define sensorWaitingTime 1000

#include "credentials.h"

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
  readFirebase();
}

void disconnectFirebase() {
      Firebase.reconnectWiFi(false); 
      Serial.println("Disconnected from Firebase.");
}


void readFirebase(){
  Serial.println("Getting User UID");
  path = "/smart_farming/" + String(uid) + "/realtime_kebun";
  pathMonitoring = String (path) + "/"+ String(kebun_id) +"/monitoring";
  pathNutrient = String (path) + "/"+ String(kebun_id) +"/nutrient";
  pathControlling = String (path) + "/"+ String(kebun_id) +"/controlling";
}

void get_status() {
    if (isWiFiConnecting) {
        if (Firebase.ready()) {
            fetchControllingDataNonBlocking();
        }
    } 
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
                // Serial.println("init fetch con data");
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
            // Serial.println("fetch wait");
            if (fbdo.dataAvailable()) {
                fetchState = FETCH_PROCESS;
            } else if (millis() - fetchStartTime > firebaseWaitingTime) {
                Serial.println("Timeout while waiting for data.");
                fetchState = FETCH_DONE;
            }
            break;

        case FETCH_PROCESS:
            // Serial.println("fetch process");
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
            for (size_t index = 0; index < devices.size(); ++index) {
                auto &device = devices[index];
                bool gpioState = readGPIOState(device.pin);
                
                if (gpioState != device.firebase_state) {
                    if (device.tempState == -1) {
                        if (device.firebase_state) {
                            updateDeviceButtonState(true, index);
                        } else {
                            updateDeviceButtonState(false, index); 
                        }
                        controlDevice(device);
                    } else {
                        updateFirebaseDeviceState(index, device.tempState);
                    }
                }else{
                    device.tempState = -1;
                }
            }

            fetchState = FETCH_DONE;
            break;

        case FETCH_DONE:
            fetchState = FETCH_INIT; // Reset for the next call
            break;
    }
}

void updateFirebaseDeviceState(int index, int state)
{
    if (Firebase.setInt(fbdo, pathControlling+"/"+devices[index].path, state)) {
        devices[index].tempState = -1;
    } else {
        devices[index].tempState = state;
        Serial.println("Failed to update Firebase: " + String(state));
    }
}
void sent_datarhtemp() {
  if (Firebase.setFloat(fbdo, pathMonitoring+"/humidity", RH)) {
        // Serial.println("Firebase updated successfully! "+ String(state));
  } else {
      Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
  }
  if (Firebase.setFloat(fbdo, pathMonitoring+"/temperatur", temperatureC)) {
      // Serial.println("Firebase updated successfully! "+ String(state));
  } else {
      Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
  }
}

void sent_dataecph() {
  if (Firebase.setFloat(fbdo, pathMonitoring+"/ec", ec)) {
        // Serial.println("Firebase updated successfully! "+ String(state));
  } else {
      Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
  }
  if (Firebase.setFloat(fbdo, pathMonitoring+"/ph", ph)) {
      // Serial.println("Firebase updated successfully! "+ String(state));
  } else {
      Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
  }
  if (Firebase.setFloat(fbdo, pathMonitoring+"/temperatur_air", tp)) {
      // Serial.println("Firebase updated successfully! "+ String(state));
  } else {
      Serial.println("Failed to update Firebase: " + String(fbdo.errorReason()));
  }
}

