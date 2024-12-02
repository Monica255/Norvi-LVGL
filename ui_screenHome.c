// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"

void ui_screenHome_screen_init(void)
{
ui_screenHome = lv_obj_create(NULL);
lv_obj_clear_flag( ui_screenHome, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_screenHome, lv_color_hex(0x4A9C79), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_screenHome, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageWaterTank = lv_img_create(ui_screenHome);
lv_img_set_src(ui_ImageWaterTank, &ui_img_water_tank_png);
lv_obj_set_width( ui_ImageWaterTank, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageWaterTank, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageWaterTank, -272 );
lv_obj_set_y( ui_ImageWaterTank, 13 );
lv_obj_set_align( ui_ImageWaterTank, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageWaterTank, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageWaterTank, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_panelPH = lv_obj_create(ui_screenHome);
lv_obj_set_width( ui_panelPH, 150);
lv_obj_set_height( ui_panelPH, 100);
lv_obj_set_x( ui_panelPH, -100 );
lv_obj_set_y( ui_panelPH, -20 );
lv_obj_set_align( ui_panelPH, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_panelPH, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LabelPHValue = lv_label_create(ui_panelPH);
lv_obj_set_width( ui_LabelPHValue, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelPHValue, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelPHValue, 0 );
lv_obj_set_y( ui_LabelPHValue, -30 );
lv_obj_set_align( ui_LabelPHValue, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelPHValue,"PH Value");

ui_phValue = lv_label_create(ui_panelPH);
lv_obj_set_width( ui_phValue, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_phValue, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_phValue, 0 );
lv_obj_set_y( ui_phValue, lv_pct(20) );
lv_obj_set_align( ui_phValue, LV_ALIGN_CENTER );
lv_label_set_text(ui_phValue,"30");
lv_obj_set_style_text_font(ui_phValue, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_panelEC = lv_obj_create(ui_screenHome);
lv_obj_set_width( ui_panelEC, 150);
lv_obj_set_height( ui_panelEC, 100);
lv_obj_set_x( ui_panelEC, -100 );
lv_obj_set_y( ui_panelEC, 100 );
lv_obj_set_align( ui_panelEC, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_panelEC, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LabelECValue = lv_label_create(ui_panelEC);
lv_obj_set_width( ui_LabelECValue, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelECValue, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelECValue, 0 );
lv_obj_set_y( ui_LabelECValue, -30 );
lv_obj_set_align( ui_LabelECValue, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelECValue,"EC Value");

ui_ecValue = lv_label_create(ui_panelEC);
lv_obj_set_width( ui_ecValue, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ecValue, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ecValue, -20 );
lv_obj_set_y( ui_ecValue, lv_pct(20) );
lv_obj_set_align( ui_ecValue, LV_ALIGN_CENTER );
lv_label_set_text(ui_ecValue,"30");
lv_obj_set_style_text_font(ui_ecValue, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ecValue1 = lv_label_create(ui_panelEC);
lv_obj_set_width( ui_ecValue1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ecValue1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ecValue1, 35 );
lv_obj_set_y( ui_ecValue1, lv_pct(20) );
lv_obj_set_align( ui_ecValue1, LV_ALIGN_CENTER );
lv_label_set_text(ui_ecValue1,"uS/cm");

ui_panelSensor = lv_obj_create(ui_screenHome);
lv_obj_set_width( ui_panelSensor, 250);
lv_obj_set_height( ui_panelSensor, 300);
lv_obj_set_x( ui_panelSensor, 150 );
lv_obj_set_y( ui_panelSensor, 40 );
lv_obj_set_align( ui_panelSensor, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_panelSensor, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LabelTemp = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_LabelTemp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelTemp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelTemp, 0 );
lv_obj_set_y( ui_LabelTemp, -120 );
lv_obj_set_align( ui_LabelTemp, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelTemp,"Temperature");

ui_LabelHumidity = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_LabelHumidity, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelHumidity, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelHumidity, 0 );
lv_obj_set_y( ui_LabelHumidity, -30 );
lv_obj_set_align( ui_LabelHumidity, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelHumidity,"Humidity");

ui_labelSoil = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_labelSoil, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_labelSoil, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_labelSoil, 0 );
lv_obj_set_y( ui_labelSoil, 70 );
lv_obj_set_align( ui_labelSoil, LV_ALIGN_CENTER );
lv_label_set_text(ui_labelSoil,"Soil Moisture");

ui_temp = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_temp, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_temp, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_temp, -105 );
lv_obj_set_y( ui_temp, lv_pct(-35) );
lv_obj_set_align( ui_temp, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_temp,"30");
lv_obj_set_style_text_align(ui_temp, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_temp, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_temp1 = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_temp1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_temp1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_temp1, 35 );
lv_obj_set_y( ui_temp1, lv_pct(-35) );
lv_obj_set_align( ui_temp1, LV_ALIGN_CENTER );
lv_label_set_text(ui_temp1,"°C");
lv_obj_set_style_text_font(ui_temp1, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_humidity = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_humidity, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_humidity, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_humidity, -105 );
lv_obj_set_y( ui_humidity, lv_pct(0) );
lv_obj_set_align( ui_humidity, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_humidity,"30");
lv_obj_set_style_text_font(ui_humidity, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_humidity1 = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_humidity1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_humidity1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_humidity1, 35 );
lv_obj_set_y( ui_humidity1, lv_pct(0) );
lv_obj_set_align( ui_humidity1, LV_ALIGN_CENTER );
lv_label_set_text(ui_humidity1,"%");
lv_obj_set_style_text_font(ui_humidity1, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Soil_Moisture = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_Soil_Moisture, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Soil_Moisture, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Soil_Moisture, -105 );
lv_obj_set_y( ui_Soil_Moisture, lv_pct(40) );
lv_obj_set_align( ui_Soil_Moisture, LV_ALIGN_RIGHT_MID );
lv_label_set_text(ui_Soil_Moisture,"30");
lv_obj_set_style_text_font(ui_Soil_Moisture, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Soil_Moisture1 = lv_label_create(ui_panelSensor);
lv_obj_set_width( ui_Soil_Moisture1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Soil_Moisture1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Soil_Moisture1, 35 );
lv_obj_set_y( ui_Soil_Moisture1, lv_pct(40) );
lv_obj_set_align( ui_Soil_Moisture1, LV_ALIGN_CENTER );
lv_label_set_text(ui_Soil_Moisture1,"%");
lv_obj_set_style_text_font(ui_Soil_Moisture1, &ui_font_arial30B8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ButtonControlling1 = lv_btn_create(ui_screenHome);
lv_obj_set_width( ui_ButtonControlling1, 100);
lv_obj_set_height( ui_ButtonControlling1, 60);
lv_obj_set_x( ui_ButtonControlling1, 160 );
lv_obj_set_y( ui_ButtonControlling1, -160 );
lv_obj_set_align( ui_ButtonControlling1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ButtonControlling1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ButtonControlling1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ButtonControlling1, lv_color_hex(0x0F8161), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ButtonControlling1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_ButtonControlling1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ButtonControlling1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelControlling1 = lv_label_create(ui_ButtonControlling1);
lv_obj_set_width( ui_LabelControlling1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelControlling1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_LabelControlling1, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelControlling1,"Controlling");

ui_ButtonNutrient1 = lv_btn_create(ui_screenHome);
lv_obj_set_width( ui_ButtonNutrient1, 100);
lv_obj_set_height( ui_ButtonNutrient1, 60);
lv_obj_set_x( ui_ButtonNutrient1, 285 );
lv_obj_set_y( ui_ButtonNutrient1, -160 );
lv_obj_set_align( ui_ButtonNutrient1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ButtonNutrient1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ButtonNutrient1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ButtonNutrient1, lv_color_hex(0x0F8161), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ButtonNutrient1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_ButtonNutrient1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ButtonNutrient1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelNutrient1 = lv_label_create(ui_ButtonNutrient1);
lv_obj_set_width( ui_LabelNutrient1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelNutrient1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_LabelNutrient1, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelNutrient1,"Nutrient");

ui_ButtonHome1 = lv_btn_create(ui_screenHome);
lv_obj_set_width( ui_ButtonHome1, 100);
lv_obj_set_height( ui_ButtonHome1, 60);
lv_obj_set_x( ui_ButtonHome1, 35 );
lv_obj_set_y( ui_ButtonHome1, -160 );
lv_obj_set_align( ui_ButtonHome1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ButtonHome1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags
lv_obj_clear_flag( ui_ButtonHome1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_ButtonHome1, lv_color_hex(0x426A5E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_ButtonHome1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_color(ui_ButtonHome1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_ButtonHome1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelHome1 = lv_label_create(ui_ButtonHome1);
lv_obj_set_width( ui_LabelHome1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelHome1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_LabelHome1, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelHome1,"Home");

lv_obj_add_event_cb(ui_ButtonControlling1, ui_event_ButtonControlling1, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ButtonNutrient1, ui_event_ButtonNutrient1, LV_EVENT_ALL, NULL);

}
