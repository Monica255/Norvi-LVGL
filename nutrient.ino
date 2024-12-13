
void updateStartButtonState(bool onprocess) {
    lv_obj_add_state(ui_ButtonStart, LV_STATE_DISABLED);
    if (onprocess) {
        lv_obj_set_style_bg_color(ui_ButtonStart, lv_color_hex(0xFF0000), LV_PART_MAIN); // Update button color RED
        lv_label_set_text(ui_LabelButtonStart, "Stop"); 
    } else {
        lv_obj_set_style_bg_color(ui_ButtonStart, lv_color_hex(0x0000FF), LV_PART_MAIN); // Update button color BLUE
        lv_label_set_text(ui_LabelButtonStart, "Start"); 
        lv_textarea_set_text(ui_TextAreaECTarget, "");
        lv_textarea_set_text(ui_TextAreaMixTime, "");
        startTime = 0;
        targetEC = 0;
        mixTime = 0;
    }
    lv_obj_clear_state(ui_ButtonStart, LV_STATE_DISABLED);
}


void observeNutrient(){
  if (isProcessing) {
        unsigned long elapsedTime = (millis() - startTime) / 1000; // Elapsed time in seconds
        int remainingTime = mixTime - elapsedTime;                // Calculate remaining time
        if (remainingTime >= 0) {
            // Update the countdown text in the UI
            char countdownText[16];
            snprintf(countdownText, sizeof(countdownText), "Time: %ds", remainingTime);
            lv_label_set_text(ui_LabelTime, countdownText); 
        }

        // Check if the process should stop
        if (ec >= targetEC || remainingTime <= 0) {
            OnOffDevice(false, 2);
            isProcessing = false;
            startTime = 0;
            targetEC = 0;
            mixTime = 0;

            updateStartButtonState(false);
            lv_label_set_text(ui_LabelTime, "Done");
        }
    }
}