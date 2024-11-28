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

#include "credentials.h"

struct DeviceState {
    int pin;              // GPIO pin
    int firebase_state;            // Current device state
    int device_state;        // Previous device state (replaces LED variables)
    uint16_t coil;        // Coil address for Modbus communication
    lv_obj_t *uiButton;   // UI button to control the device
    const char *path;     // Firebase JSON path
};

// Devices array
DeviceState devices[] = {
    {GPIO8, 0, 0, 0x00001, ui_ButtonONOFF1, "pompa_1/state"},
    {GPIO7, 0, 0, 0x00002, ui_ButtonONOFF2, "pompa_2/state"},
    {GPIO6, 0, 0, 0x00003, ui_ButtonONOFF3, "pompa_3/state"},
    {GPIO5, 0, 0, 0x00004, ui_ButtonONOFF4, "exhaust_fan_1/state"}
};
>>>>>>> f1b4f93 (clean code + rebase add gitignore)

String uid, path, pathMonitoring, pathNutrient, pathControlling;

float temperatureC, RH, ph;
int valSoil, ec;

struct SensorData {
  float ph;
  int ec;
  float temperature;
};

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}


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
      Serial.print( "Data x :" );
      Serial.println( touch_last_x );

      Serial.print( "Data y :" );
      Serial.println( touch_last_y );
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
void OnOffDevice(bool is_on, DeviceState &device) {
    if (is_on) {
        Serial.printf("%s is ON\n", device.path);
        device.device_state = 1;
    } else {
        Serial.printf("%s is OFF\n", device.path);
        device.device_state = 0;
    }
    updateFirebaseState(device.path, device.device_state);

    writeOutput(device.pin, device.device_state);
    result = node.writeSingleCoil(device.coil, device.device_state);
}

void OnOffPompa1(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, devices[0]);
}

void OnOffPompa2(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, devices[1]);
}

void OnOffPompa3(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, devices[2]);
}

void OnOffExh(lv_event_t *e) {
    bool is_on = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);
    OnOffDevice(is_on, devices[3]);
}


void controlDevice(DeviceState &device ) {
    writeOutput(device.pin, device.firebase_state);
    device.device_state = device.firebase_state; 
    result = node.writeSingleCoil(device.coil, device.device_state);

    Serial.printf("Controlling device on GPIO %d: %d\n", device.pin, device.firebase_state);

    if (device.firebase_state) {
        lv_obj_add_state(device.uiButton, LV_STATE_CHECKED); // Turn the button ON
    } else {
        lv_obj_clear_state(device.uiButton, LV_STATE_CHECKED); // Turn the button OFF
    }
}


void calculateAB(lv_event_t * e)
{
	 Serial.println("button clicked");
}

void startManualNutrient(lv_event_t * e)
{
	// Your code here
}

void startAutoNutrient(lv_event_t * e)
{
	// Your code here
}


void setup()
{
  
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(1000);
  initWiFi();
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
  Serial.println( "Setup done" );
  Wire.begin(SDA, SCL);

  if (!ads2.begin(0x49)) {
    Serial.println("Failed to initialize ADS 1 .");
  }
  ads2.setGain(GAIN_ONE);
  setPinMode(GPIO5, OUTPUT);
  setPinMode(GPIO6, OUTPUT);
  setPinMode(GPIO7, OUTPUT);
  setPinMode(GPIO8, OUTPUT);
}
unsigned char byteRequest[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; 
void loop() {
    start_calibratation();
    if(!Firebase.ready()){
      initFirebase();
      readFirebase();
      Serial.println("Firebase now ready");
    }

    // // get_connection();
    get_status();
    sent_data();

    // Read analog values from ADS1115
    int16_t adc0_2 = ads2.readADC_SingleEnded(0);
    int16_t adc1_2 = ads2.readADC_SingleEnded(1);
    // int16_t adc2_2 = ads2.readADC_SingleEnded(2);
    // int16_t adc3_2 = ads2.readADC_SingleEnded(3);

    char tempStr[10],tempStr2[10], tempStr3[10], tempStr4[10]; 
  
    float current_mA = convertADCToCurrent(adc1_2);
    temperatureC = convertCurrentToTemperature(current_mA);
    RH = convertADCToRH(adc0_2); 

    SensorData sensorData = readSensor(byteRequest, sizeof(byteRequest));
    ec = sensorData.ec;
    ph = sensorData.ph;

    dtostrf(temperatureC, 6, 2, tempStr);
    dtostrf(RH, 6, 2, tempStr2);
    dtostrf(ec, 6, 0, tempStr3); 
    dtostrf(ph, 6, 2, tempStr4); 

#ifdef USE_UI
    lv_label_set_text(ui_temp, tempStr); 
    lv_label_set_text(ui_humidity, tempStr2);
    lv_label_set_text_fmt(ui_ecValue, tempStr3);
    lv_label_set_text_fmt(ui_phValue, tempStr4);
    lv_timer_handler();
    //lv_task_handler();
    delay(300);
#endif
}
