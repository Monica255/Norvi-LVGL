// void get_connection(){
//     if (WiFi.status() != WL_CONNECTED){
//       Serial.println("Disconnect, offline");
//       delay(1000);
//       Serial.println("Try to connection");
//       ESP.restart();
//       delay(3000);
//     }
// }
void observeWifi(){
  if (WiFi.status() == WL_CONNECTED) {
          if (!Firebase.ready()) {
              initFirebase();
          }else if(Firebase.ready() && !isWiFiConnecting){
            isWiFiConnecting = true; 
            updateWiFiButtonState(true, lv_color_hex(0xFF0000),"Disconnect");
          }
    } else{
        if (millis() - wifiAttemptStartTime >= wifiTimeout && startConnection) {
            startConnection=false;
            wifiAttemptStartTime =0;
            isWiFiConnecting = false; 
            updateWiFiButtonState(true, lv_color_hex(0x0000FF),"Connect");
            Serial.println("timeout");
        }
    }
}

void reconnectWiFi(bool connect) {
    if (!connect) {
        startConnection = true;
        updateWiFiButtonState(false, lv_color_hex(0x0000FF),"...");
        WiFi.disconnect();  
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        wifiAttemptStartTime = millis();
    } else {
        updateWiFiButtonState(false, lv_color_hex(0xFF0000),"...");
        if (Firebase.ready()) {
            disconnectFirebase();
            Serial.println("Firebase disconnected");
        }
        WiFi.disconnect();          // Disconnect Wi-Fi
        Serial.println("WiFi disconnected.");
        isWiFiConnecting = false;   // Reset connection state
        updateWiFiButtonState(true, lv_color_hex(0x0000FF),"Connect");
    }
}