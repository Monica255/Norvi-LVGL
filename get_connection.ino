void updateWiFiButtonState(bool enable, lv_color_t color, const char *labelText) {
    if (enable) {
        lv_obj_clear_state(ui_ButtonWifi, LV_STATE_DISABLED);
    } else {
        lv_obj_add_state(ui_ButtonWifi, LV_STATE_DISABLED);
    }
    lv_obj_set_style_bg_color(ui_ButtonWifi, color, LV_PART_MAIN); // Update button color
    lv_label_set_text(ui_LabelWifi1, labelText); // Assuming `ui_LabelWifi1` is the label object
}

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