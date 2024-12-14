#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <ModbusMaster.h>

ModbusMaster node;

#define Display_50
#define USE_UI
#define SDA 19
#define SCL 20

#if defined USE_UI
#include <lvgl.h>
#include "ui.h"
#endif

#include <Arduino_GFX_Library.h>
#define TFT_BL -1
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

Adafruit_ADS1115 ads2;

#define PCA9538_ADDR 0x73
#define PCA9538_INPUT_REG 0x00
#define PCA9538_OUTPUT_REG 0x01
#define PCA9538_POLARITY_REG 0x02
#define PCA9538_CONFIG_REG 0x03

#define FC     22
#define RX_PIN 48 
#define TX_PIN 2

#define GPIO5 0x10
#define GPIO6 0x20
#define GPIO7 0x40
#define GPIO8 0x80

#define NUM_INPUT_PINS 4

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"


lv_obj_t *spinner;

#include "credentials.h"

#define sensorFrameSize  19
#define sensorWaitingTime 1500

#include "credentials.h"

struct DeviceState {
    int pin;              // GPIO pin
    int firebase_state; 
    int tempState;      // Previous device state (replaces LED variables)
    uint16_t coil;        // Coil address for Modbus communication
    lv_obj_t *uiButton;
    lv_obj_t *uiLable;
    lv_obj_t *uiState;   // UI button to control the device
    const char *path;     // Firebase JSON path
};
std::vector<DeviceState> devices;
// Devices array

DeviceState devices[] = {
    {GPIO8, 0, 0, 0x00001, ui_ButtonONOFF1, "pompa_1/state"},
    {GPIO7, 0, 0, 0x00002, ui_ButtonONOFF2, "pompa_2/state"},
    {GPIO6, 0, 0, 0x00003, ui_ButtonONOFF3, "pompa_3/state"},
    {GPIO5, 0, 0, 0x00004, ui_ButtonONOFF4, "exhaust_fan_1/state"}
};


String uid, path, pathMonitoring, pathNutrient, pathControlling;
float temperatureC, RH, valSoil;
int   ec;
float tp,ph;

struct SensorData {
  float ph;
  int ec;
  float tp;
};

void setPinMode(uint8_t pin, uint8_t mode) {
  uint8_t config = readRegister(PCA9538_CONFIG_REG);
  if (mode == INPUT) {
     config |= pin;
   } else {
     config &= ~pin;
   }
   writeRegister(PCA9538_CONFIG_REG, config);
}
void writeOutput(uint8_t pin, uint8_t value) {
  uint8_t output = readRegister(PCA9538_OUTPUT_REG);
  if (value == LOW) {
    output &= ~pin;
  } else {
    output |= pin;
  }
  writeRegister(PCA9538_OUTPUT_REG, output);
}
uint8_t readInput() {
   return readRegister(PCA9538_INPUT_REG);
}
uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(PCA9538_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(PCA9538_ADDR, 1);
  return Wire.read();
}
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(PCA9538_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void preTransmission()
{
  digitalWrite(FC, 1);
}

void postTransmission()
{
  digitalWrite(FC, 0);
}

#if defined(DISPLAY_DEV_KIT)
Arduino_GFX *lcd = create_default_Arduino_GFX();
#else
Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    4 /* DE */, 5 /* VSYNC */, 6 /* HSYNC */, 7 /* PCLK */,
    1 /* R0 */, 41 /* R1 */, 40 /* R2 */, 38 /* R3 */, 45 /* R4 */,
    47 /* G0 */, 21 /* G1 */, 14 /* G2 */, 9 /* G3 */, 3 /* G4 */, 3 /* G5 */,
    8 /* B0 */, 18 /* B1 */, 17 /* B2 */, 16 /* B3 */, 15 /* B4 */
);
Arduino_RPi_DPI_RGBPanel *lcd = new Arduino_RPi_DPI_RGBPanel(
    bus,
    800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */);
#endif

#include "touch.h"

#ifdef USE_UI
/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10];      //5,7inch: lv_color_t disp_draw_buf[800*480/10]            4.3inch: lv_color_t disp_draw_buf[480*272/10]
//static lv_color_t disp_draw_buf;
static lv_disp_drv_t disp_drv;

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
  lcd->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
  lcd->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif
  lv_disp_flush_ready(disp);
}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
      // Serial.print( "Data x :" );
      // Serial.println( touch_last_x );

      // Serial.print( "Data y :" );
      // Serial.println( touch_last_y );
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
  delay(15);
}
#endif

uint8_t result;
enum FetchStates {
    FETCH,
    SEND
};
enum FetchState {
    IDLE,
    FETCH_INIT,
    FETCH_WAIT,
    FETCH_PROCESS,
    UPDATE_DEVICE,
    FETCH_DONE
};
FetchState fetchState = FETCH_INIT;

enum SensorReadState {
    IDLE2,
    INIT_SENSOR_READ,
    WAIT_FOR_RESPONSE,
    READ_SENSOR_DATA,
    READ_SENSOR_DATA_CONT,
    PROCESS_SENSOR_DATA,
    SAVE_SENSOR_DATA,
    SAVE_SENSOR_DATA2,
    SAVE_SENSOR_DATA3,
    CHECK_DATA,
    SAVE_FIREBASE,
    READ_COMPLETE
};

SensorReadState sensorReadState = INIT_SENSOR_READ;

bool isWiFiConnecting = false; // Track Wi-Fi connection state
bool startConnection = false;
unsigned long wifiAttemptStartTime = 0;
const unsigned long wifiTimeout = 5000; 

void connectWifi(lv_event_t * e) {
    reconnectWiFi(isWiFiConnecting);
}

void updateWiFiButtonState(bool enable, lv_color_t color, const char *labelText) {
    lv_obj_t * button = ui_ButtonWifi; // Assuming `ui_ButtonWifi` is your button object
    if (enable) {
        lv_obj_clear_state(button, LV_STATE_DISABLED);
    } else {
        lv_obj_add_state(button, LV_STATE_DISABLED);
    }
    lv_obj_set_style_bg_color(button, color, LV_PART_MAIN); // Update button color
    lv_label_set_text(ui_LabelWifi1, labelText); // Assuming `ui_LabelWifi1` is the label object
}


void updateDeviceButtonState(bool state, int index) {
    if (state) {
      lv_obj_add_state(devices[index].uiButton, LV_STATE_CHECKED);
      lv_label_set_text(devices[index].uiLable, "OFF");
      lv_label_set_text(devices[index].uiState, "State: ON");
    } else {
      lv_obj_clear_state(devices[index].uiButton, LV_STATE_CHECKED);
      lv_label_set_text(devices[index].uiLable, "ON");
      lv_label_set_text(devices[index].uiState, "State: OFF");
    }
}


void OnOffDevice(bool is_on, int index) {
    int x;
    if (is_on) {
        Serial.printf("%s is ON\n", devices[index].path);
        updateDeviceButtonState(true, index);
        x = 1;
    } else {
        Serial.printf("%s is OFF\n", devices[index].path);
        updateDeviceButtonState(false, index);
        x = 0;
    }
    sensorReadState = IDLE2;
    fetchState = IDLE;
    writeOutput(devices[index].pin, x);
    updateFirebaseDeviceState(index, x);
    result = node.writeSingleCoil(devices[index].coil, x);
    fetchState = FETCH_INIT;
    sensorReadState = INIT_SENSOR_READ;
}

void OnOffPompa1(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, 0);
}

void OnOffPompa2(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    Serial.println(is_on);
    OnOffDevice(is_on, 1);
}

void OnOffPompa3(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, 2);
}

void OnOffExh(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, 3);
}

void controlDevice(DeviceState &device ) {
    sensorReadState = IDLE2;
    writeOutput(device.pin, device.firebase_state);
    result = node.writeSingleCoil(device.coil, device.firebase_state);
    Serial.printf("Controlling device on GPIO %d: %d\n", device.pin, device.firebase_state);
    sensorReadState = INIT_SENSOR_READ;
}


bool isProcessing =false;
int startTime;
int targetEC, mixTime;
int ml = 10;

void calculateAB(lv_event_t * e)
{
    const char * text = lv_textarea_get_text(ui_TextAreaMixTime);
    int inputValue = atoi(text);
    int result = inputValue * ml;
    
    char resultStr[16]; // Ensure enough space for the integer
    dtostrf(result, 6, 0, resultStr);
   
    lv_label_set_text_fmt(ui_doseA, resultStr);
    lv_label_set_text_fmt(ui_doseB, resultStr);
}

void startManualNutrient(lv_event_t * e) {
    const char * text = lv_textarea_get_text(ui_TextAreaECTarget);
    const char * text2 = lv_textarea_get_text(ui_TextAreaMixTime);
    targetEC = atoi(text);
    mixTime = atoi(text2);
    if(targetEC<=ec||targetEC<=0||mixTime<=0){
      lv_label_set_text(ui_LabelTime, "Invalid input");
      updateStartButtonState(false);
      return;
    }
    if (!isProcessing){
        isProcessing = true;
        Serial.println("on");
        updateStartButtonState(true);
        OnOffDevice(true, 2);
        startTime = millis();    
    }else{
        isProcessing = false;
        updateStartButtonState(false);
        lv_label_set_text(ui_LabelTime, "Stopped");
        Serial.println("off");
        OnOffDevice(false, 2);
    }
}



void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(1000);
  
  node.begin(1, Serial1);                          
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
  // Perform Calibration
  // calibratepH();
  // calibrateEc();
  
#if defined(Display_50)
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);
#endif
  lcd->begin();
  lcd->fillScreen(BLACK);
  lcd->setTextSize(2);
  delay(200);
  
#ifdef USE_UI
  lv_init();
  delay(100);
  touch_init();
  screenWidth = lcd->width();
  screenHeight = lcd->height();
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * screenHeight / 10);
  //  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, 480 * 272 / 10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
#endif
  
#ifdef TFT_BL
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
#endif

#ifdef USE_UI
  ui_init();
#else
  lcd->fillScreen(BLUE);
  delay(800);
#endif
  devices.push_back({GPIO8, 0, -1, 0x00001, ui_ButtonONOFF1,ui_LabelON1 ,ui_LabelStateOFFPompa1 ,"pompa_1/state"});
  devices.push_back({GPIO7, 0, -1, 0x00002, ui_ButtonONOFF2,ui_LabelON2 ,ui_LabelStateOFFPompa2 , "pompa_2/state"});
  devices.push_back({GPIO6, 0, -1, 0x00003, ui_ButtonONOFF3,ui_LabelON3 ,ui_LabelStateOFFPompa3 , "pompa_3/state"});
  devices.push_back({GPIO5, 0, -1, 0x00004, ui_ButtonONOFF4,ui_LabelON4 ,ui_LabelStateOFFExh , "exhaust_fan_1/state"});
  // Serial.println( "Setup done" );
  Wire.begin(SDA, SCL);

  if (!ads2.begin(0x49)) {
    Serial.println("Failed to initialize ADS 1 .");
  }

  ads2.setGain(GAIN_ONE);
  setPinMode(GPIO5, OUTPUT);
  setPinMode(GPIO6, OUTPUT);
  setPinMode(GPIO7, OUTPUT);
  setPinMode(GPIO8, OUTPUT);

  writeOutput(devices[0].pin, 0);
  writeOutput(devices[1].pin, 0);
  writeOutput(devices[2].pin, 0);
  writeOutput(devices[3].pin, 0);
}

char tempStr[10],tempStr2[10], tempStr3[10], tempStr4[10], tempStr5[10]; 

void loop() {
    observeWifi();
    
    get_status();

    readRhTempNonBlocking();
    readSensorNonBlocking();

    observeNutrient();

#ifdef USE_UI
    lv_label_set_text(ui_temp, tempStr); 
    lv_label_set_text(ui_humidity, tempStr2);
    // lv_label_set_text_fmt(ui_Soil_Moisture, tempStr3);
    lv_label_set_text_fmt(ui_ecValue, tempStr4);
    lv_label_set_text_fmt(ui_phValue, tempStr5);
    lv_timer_handler();
    // lv_task_handler();
    delay(5);
#endif
}
