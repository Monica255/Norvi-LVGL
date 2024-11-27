#include "credentials.h"
void readFirebase(){
  Serial.println("Getting User UID");

  path = "/smart_farming/" + String(uid) + "/realtime_kebun";
  pathPompa1 =  String(path) + "/kebun_1/controlling/pompa_1/state";
  pathPompa2 =  String(path) + "/kebun_1/controlling/pompa_2/state";
  pathPompa3 =  String(path) + "/kebun_1/controlling/pompa_3/state";
  pathExh =  String(path) + "/kebun_1/controlling/exhaust_1/state";
  pathMonitoring = String (path) + "/kebun_1/monitoring";
  pathNutrient = String (path) + "/kebun_1/nutrient";
}

void get_status() {
  // Get status from firebase

  Serial.printf("Get int pompa_1... %s\n", Firebase.getInt(fbdo, pathPompa1, &statePompa1) ? String(statePompa1).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int pompa_2... %s\n", Firebase.getInt(fbdo, pathPompa2, &statePompa2) ? String(statePompa2).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int pompa_3... %s\n", Firebase.getInt(fbdo, pathPompa3, &statePompa3) ? String(statePompa3).c_str() : fbdo.errorReason().c_str());
  Serial.printf("Get int exhaust_1... %s\n", Firebase.getInt(fbdo, pathExh, &stateExh) ? String(stateExh).c_str() : fbdo.errorReason().c_str());

  // digitalWrite(POMPA1PIN, statePompa1);
  // digitalWrite(LAMPU1PIN, stateLampu1);
  // controlPompa1(statePompa1);
  // controlPompa2(statePompa2);
  controlPompa3(statePompa3);

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

// void read_sensor() {
//   // membaca sensor kelembaban
//   const int soilTreshold = 100;
//   // read soil sensor 1
//   int readSoil = analogRead(SOILPIN);
//   if (readSoil >= soilTreshold && readSoil <= 4095) {
//     valSoil = (100 - ((readSoil / 4095.0) * 100));
//   } else {
//     Serial.println(F("Failed to read soil sensor 1!"));
//     // Set valSoil to 0 if the soil sensor 1 reading is out of range
//     valSoil = 0;
//   }
  
//   Serial.println("Moisture: " + String(valSoil) + "%");

//   delay(500);
// }

void updateFirebaseState(const String &path, int state)
{
    // Update the state in Firebase
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