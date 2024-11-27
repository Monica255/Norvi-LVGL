#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <ModbusMaster.h>

#define USE_UI//if you want to use the ui export from Squareline, please do not annotate this line.

#define SDA 19
#define SCL 20

#if defined USE_UI
#include <lvgl.h>
#include "ui.h"
#endif

#include <Arduino_GFX_Library.h>
#define TFT_BL -1
#define GFX_BL DF_GFX_BL // default backlight pin, you may replace DF_GFX_BL to actual backlight pin

// Define the I2C address for the ADS1115
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

#define GPIO1 0x01
#define GPIO2 0x02
#define GPIO3 0x04
#define GPIO4 0x08

#define NUM_INPUT_PINS 4

// Library Firebase ESP32
#include <WiFi.h>
#include <FirebaseESP32.h>

// Library Sensor DHT
#include <DHT.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#include "credentials.h"

FirebaseData fbdo;
FirebaseJson json;
FirebaseAuth auth;
FirebaseConfig config;

String uid, path, pathPompa1, pathPompa2, pathPompa3, pathExh, pathMonitoring, pathNutrient;

float temperatureC, RH, ph;
int valSoil, ec;
int statePompa1, statePompa2, statePompa3, stateExh;

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

#define Display_50

ModbusMaster node;
int LED1;
int LED2;
int LED3;
int LED4;

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

/*******************************************************************************
 * Screen Driver Configuration  end
*******************************************************************************/


/*******************************************************************************
   Please config the touch panel in touch.h
 ******************************************************************************/
#include "touch.h"

#ifdef USE_UI
/* Change to your screen resolution */
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf[800 * 480 / 10];      //5,7inch: lv_color_t disp_draw_buf[800*480/10]            4.3inch: lv_color_t disp_draw_buf[480*272/10]
//static lv_color_t disp_draw_buf;
static lv_disp_drv_t disp_drv;

/* Display flushing */
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

void OnOffPompa1(lv_event_t * e)
{
    lv_obj_t *button = lv_event_get_target(e);

    // Check if the button is in the checked state
    bool is_on = lv_obj_has_state(button, LV_STATE_CHECKED);

    if (is_on) {
        Serial.println("Pompa 1 is ON\n");
        LED1=1;
        updateFirebaseState(pathPompa1,1);
    } else {
        Serial.println("Pompa 1 is OFF\n");
        LED1=0;
        updateFirebaseState(pathPompa1,0);
    }
  writeOutput(GPIO5, LED1);
  result = node.writeSingleCoil(0x00001, LED1);
}

void controlPompa1(int state) {
    // Call writeOutput for GPIO5
    writeOutput(GPIO5, state);
    LED1 = state; 
    result = node.writeSingleCoil(0x00001, LED1);
    Serial.println("Controlling pompa 1");
    Serial.println(state);

    if (state) {
        lv_obj_add_state(ui_ButtonONOFF1, LV_STATE_CHECKED); // Turn the button ON
    } else {
        lv_obj_clear_state(ui_ButtonONOFF1, LV_STATE_CHECKED); // Turn the button OFF
    }
}



void OnOffPompa2(lv_event_t * e)
{
	lv_obj_t *button = lv_event_get_target(e);

    // Check if the button is in the checked state
    bool is_on = lv_obj_has_state(button, LV_STATE_CHECKED);

    if (is_on) {
        Serial.println("Pompa 2 is ON\n");
        LED2=1;
        updateFirebaseState(pathPompa2,1);
    } else {
        Serial.println("Pompa 2 is OFF\n");
        LED2=0;
        updateFirebaseState(pathPompa2,0);
    }
  writeOutput(GPIO6, LED2);
  result = node.writeSingleCoil(0x00001, LED2);
}

void controlPompa2(int state) {
    // Call writeOutput for GPIO5
    writeOutput(GPIO5, state);
    LED2 = state; 
    result = node.writeSingleCoil(0x00001, LED2);
    Serial.println("Controlling pompa 3");
    Serial.println(state);

    if (state) {
        lv_obj_add_state(ui_ButtonONOFF2, LV_STATE_CHECKED); // Turn the button ON
    } else {
        lv_obj_clear_state(ui_ButtonONOFF2, LV_STATE_CHECKED); // Turn the button OFF
    }
}

void OnOffPompa3(lv_event_t * e)
{
	lv_obj_t *button = lv_event_get_target(e);

    // Check if the button is in the checked state
    bool is_on = lv_obj_has_state(button, LV_STATE_CHECKED);

    if (is_on) {
        Serial.println("Pompa 3 is ON\n");
        LED3=1;
        updateFirebaseState(pathPompa3,1);
    } else {
        Serial.println("Pompa 3 is OFF\n");
        LED3=0;
        updateFirebaseState(pathPompa3,0);
    }
  writeOutput(GPIO7, LED3);
  result = node.writeSingleCoil(0x00001, LED3);
}

void controlPompa3(int state) {
    // Call writeOutput for GPIO5
    writeOutput(GPIO5, state);
    writeOutput(GPIO6, state);
    writeOutput(GPIO7, state);
    writeOutput(GPIO8, state);
    LED3 = state; 
    result = node.writeSingleCoil(0x00001, LED3);
    Serial.println("Controlling pompa 3");
    Serial.println(state);

    if (state) {
        lv_obj_add_state(ui_ButtonONOFF3, LV_STATE_CHECKED); // Turn the button ON
    } else {
        lv_obj_clear_state(ui_ButtonONOFF3, LV_STATE_CHECKED); // Turn the button OFF
    }
}

void OnOffExh(lv_event_t * e)
{
	// Your code here
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
  
#if defined(Display_50) || defined(Display_70)
  //IO Port Pins
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);
#elif defined(Display_43)
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  pinMode(35, OUTPUT);
  digitalWrite(35, LOW);
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(0, OUTPUT);//TOUCH-CS
#endif
  // Init Display
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
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
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
  ui_init();//ui from Squareline or GUI Guider
#else
  lcd->fillScreen(RED);
  delay(800);
  lcd->fillScreen(BLUE);
  delay(800);
  lcd->fillScreen(YELLOW);
  delay(800);
  lcd->fillScreen(GREEN);
  delay(800);
#endif
  Serial.println( "Setup done" );
  Wire.begin(SDA, SCL);

  setPinMode(GPIO1, INPUT);
  setPinMode(GPIO2, INPUT);
  setPinMode(GPIO3, INPUT);
  setPinMode(GPIO4, INPUT);

  // Initialize the ADS1115
  if (!ads2.begin(0x49)) {
    Serial.println("Failed to initialize ADS 1 .");
    // while (1);
  }

  // Set the gain for ADS1115
  ads2.setGain(GAIN_ONE);

  setPinMode(GPIO5, OUTPUT);
  setPinMode(GPIO6, OUTPUT);
  setPinMode(GPIO7, OUTPUT);
  setPinMode(GPIO8, OUTPUT);

  // Perform Calibration
  // calibratepH();
  // calibrateEc();

}

const float ADC_MAX_VALUE = 65535.0; // Adjust this according to your ADC's max value
const float CURRENT_MIN = 4.0; // Minimum current in mA
const float CURRENT_MAX = 20.0; // Maximum current in mA

float convertADCToRH(int16_t adcValue) {
    const float V_REF = 5.0; // Reference voltage in volts (adjust if necessary)
    const float V_MAX = 5.0; // Maximum output voltage of the sensor for 100% RH (adjust if necessary)

    float V_out = (float)adcValue / ADC_MAX_VALUE * V_REF;
    float RH = (V_out / V_MAX) * 100.0;

    return RH;
}

float convertCurrentToTemperature(float current_mA) {
    float temperature = (current_mA-4.0) * (120.0 / 16.0) - 40.0; // based on your temperature range
    return temperature;
}

float convertADCToCurrent(int16_t adcValue) {
    float current_mA = ((float)adcValue / ADC_MAX_VALUE) * 40.96;
    return current_mA;
}

#define sensorFrameSize  19
#define sensorWaitingTime 1000

//0X01 0X06 0X00 0X30 0X00 0X02 0X08 0X04
// unsigned char byteRequest[8] = {0x01, 0x03, 0x06, 0x00, 0x00, 0x03, 0x08, 0x04};
unsigned char byteRequest[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; // Adjusting the starting address and count
unsigned char byteResponseConfig[8] = {};
unsigned char byteResponse[sensorFrameSize] = {};
String run = "";

void calibratepH() {
  // Step 1: Select pH Calibration Channel
  String x;
  //01 06 00 6F 00 00 B9 D7
  byte selectChannelCommand[] = {0x01, 0x06, 0x00, 0x6F, 0x00, 0x00, 0xB9, 0xD7};
  do{
    x= sendCommand(selectChannelCommand, sizeof(selectChannelCommand));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  }while(x != "0106006F0000B9D7");
   
  // Step 2: Calibrate with pH 4.00
  // 01 06 00 69 00 01 98 16
  byte ph4Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x01, 0x98, 0x16};
  do {
    x = sendCommand(ph4Command, sizeof(ph4Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  } while (x != "0106006900019816");

  // Step 3: Calibrate with pH 6.68
  //01 06 00 69 00 02 D8 17
  byte ph6Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x02, 0xD8, 0x17};
  do {
    x = sendCommand(ph6Command, sizeof(ph6Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  } while (x != "010600690002D817");

  // Step 4: Calibrate with pH 9.18
  // 01 06 00 69 00 03 19 D7
  byte ph9Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x03, 0x19, 0xD7};
  do {
    x = sendCommand(ph9Command, sizeof(ph9Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  } while (x != "01060069000319D7");
}

void calibrateEc() {
  String x;
  byte selectChannelCommandEC[] = {0x01, 0x06, 0x00, 0x6F, 0x00, 0x01, 0x78, 0x17};
  // do{
    x= sendCommand(selectChannelCommandEC, sizeof(selectChannelCommandEC));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  // }while(x != "0106006F00017817");
   
  // 01 06 00 5E 00 01 29 D8
  byte ec2Command[] = {0x01, 0x06, 0x00, 0x5E, 0x00, 0x01, 0x29, 0xD8};
  // do {
    x = sendCommand(ec2Command, sizeof(ec2Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  // } while (x != "0106005E000129D8");

  //01 06 00 5F 03 DC B8 B1
  byte ec3Command[] = {0x01, 0x06, 0x00, 0x5F, 0x03, 0xDC, 0xB8, 0xB1};
  // do {
    x = sendCommand(ec3Command, sizeof(ec3Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  // } while (x != "0106005F03DCB8B1");

  //010600542B1EA168
  // byte ec4Command[] = {0x01, 0x06, 0x00, 0x54, 0x2B, 0x1E, 0xA1, 0x68};

  // 01 06 00 54 07 D0 CB B6
  byte ec4Command[] = {0x01, 0x06, 0x00, 0x54, 0x07, 0xD0, 0xCB, 0xB6};
  // do {
    x = sendCommand(ec4Command, sizeof(ec4Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  // } while (x != "0106005F03DCB8B1");
  
}

void calibrateEc2(String command) {
  String x;
  String y=command;
  // const size_t commandLength = command.length() / 3; // Assuming the format is "XX XX XX"
  byte commandBytes[8];
  
  // Parse the command string
  for (size_t i = 0; i < 8; ++i) {
      String byteString = command.substring(i * 3, i * 3 + 2); // Extract 2 characters for each byte
      commandBytes[i] = strtol(byteString.c_str(), NULL, 16); // Convert hex string to byte
  }

  y.replace(" ", "");
  do {
      x = sendCommand(commandBytes, 8);
      x.replace(" ", ""); // Remove spaces from response
      Serial.println("Received (formatted): " + x);
  } while (x != String(y));
}

void calibrateChannel() {
  byte selectChannelCommand[] = {0x01, 0x06, 0x00, 0x6F, 0x00, 0x00, 0xB9, 0xD7};
  String response;
  do {
    response = sendCommand(selectChannelCommand, sizeof(selectChannelCommand));
    response.replace(" ", "");
    Serial.println("Received (formatted): " + response);
  } while (response != "0106006F0000B9D7");
  Serial.println("Channel selected successfully.");
}

void calibratepH4() {
  byte ph4Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x01, 0x98, 0x16};
  String response;
  do {
    response = sendCommand(ph4Command, sizeof(ph4Command));
    response.replace(" ", "");
    Serial.println("Received (formatted): " + response);
  } while (response != "0106006900019816");
  Serial.println("Calibrated to pH 4.00 successfully.");
}

void calibratepH6_86() {
  // byte ph6Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x03, 0x19, 0xD7};
  String response;
  // do {
  //   response = sendCommand(ph6Command, sizeof(ph6Command));
  //   response.replace(" ", "");
  //   Serial.println("Received (formatted): " + response);
  // } while (response != "01060069000319D7");
  // Serial.println("Calibrated to pH 6.86 successfully.");

  // Step 3: Calibrate with pH 6.68
  //01 06 00 69 00 02 D8 17
  byte ph6Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x02, 0xD8, 0x17};
  do {
    response = sendCommand(ph6Command, sizeof(ph6Command));
    response.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + response);
  } while (response != "010600690002D817");
  Serial.println("Calibrated to pH 6.68 successfully.");
}

void calibratepH9_18() {
  byte ph9Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x03, 0x19, 0xD7};
  String response;
  do {
    response = sendCommand(ph9Command, sizeof(ph9Command));
    response.replace(" ", "");
    Serial.println("Received (formatted): " + response);
  } while (response != "01060069000319D7");
  Serial.println("Calibrated to pH 9.18 successfully.");
}

int sensorValue(int x, int y) {
  int t = 0;
  t = x * 256;
  t = t + y;

  return t;
}

String sendCommand(byte* command, size_t commandSize) {
  while (Serial1.available()) {
      Serial1.read();  // Clear any junk data from the buffer
  }

  Serial1.write(command, commandSize); // Send the command
  delay(8000); // Short delay for processing
  
  String response = "";
  
  // Wait until the response is fully available
  while (Serial1.available()) {
    byte byteRead = Serial1.read();
    response += byteRead < 0x10 ? " 0" : " ";  // Add leading space for single digits
    response += String(byteRead, HEX);  // Convert byte to hex and append to the response
  }

  response.toUpperCase();  // Ensure the response is in uppercase
  
  return response;
}


SensorData readSensor(byte* command, size_t commandSize) {
  // Flush the serial buffer before sending a new request
  while (Serial1.available()) {
      Serial1.read();  // Clear any junk data from the buffer
  }
  
  Serial1.write(command, commandSize);

  unsigned long resptime = millis();
  while ((Serial1.available() < sensorFrameSize) && ((millis() - resptime) < sensorWaitingTime)) {
    delay(1);
  }
  
  String response = "";

  int bytesRead = 0;
  while (Serial1.available() && bytesRead < sensorFrameSize) {
    byteResponse[bytesRead++] = Serial1.read();
  }

  String responseString;
  for (int j = 0; j < sensorFrameSize; j++) {
    responseString += byteResponse[j] < 0x10 ? " 0" : " ";
    responseString += String(byteResponse[j], HEX);
    responseString.toUpperCase();
  }
  Serial.println(responseString);
  // Extract sensor values
  SensorData data;
  data.ph = sensorValue(byteResponse[11], byteResponse[12]) * 0.01;         // pH with 2 decimal places
  data.ec = sensorValue(byteResponse[13], byteResponse[14]);                // EC after temperature compensation
  data.temperature = sensorValue(byteResponse[15], byteResponse[16]) * 0.1; // Temperature with 1 decimal place

  // Print values
  // Serial.println("pH: " + String(data.ph));
  // Serial.println("EC: " + String(data.ec) + " uS/cm");
  // Serial.println("Temperature: " + String(data.temperature) + " °C");

  return data;
}
//FE 06 00 37 00 01 ED CB can send this command if 485 is connected to only one device.
//01 03 00 00 00 20 44 12 
void reset(){
  byte reset1[] = {0xFE, 0x06, 0x00, 0x37, 0x00, 0x01, 0xED, 0xCB};
  String response;
  
  response = sendCommand(reset1, sizeof(reset1));
  Serial.println("Received " + response);
  
}

void reset2(){
  byte reset[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x20, 0x44, 0x12};
  String response;
  
  response = sendCommand(reset, sizeof(reset));
  Serial.println("Received " + response);
}




float target_ec;
float calc_A;
float calc_B;
String status;
float times;


void loop() {
    // uint8_t input = readInput();
    // bool inputValues[NUM_INPUT_PINS];
    // for (int i = 0; i < NUM_INPUT_PINS; i++) {
    //     inputValues[i] = bitRead(input, i);
    //     // Serial.println(inputValues[i]);
    // }
    // Serial.println();

    // Read analog values from ADS1115
    int16_t adc0_2 = ads2.readADC_SingleEnded(0);
    int16_t adc1_2 = ads2.readADC_SingleEnded(1);
    // int16_t adc2_2 = ads2.readADC_SingleEnded(2);
    // int16_t adc3_2 = ads2.readADC_SingleEnded(3);

    char tempStr[10],tempStr2[10], tempStr3[10], tempStr4[10]; 
  
    float current_mA = convertADCToCurrent(adc1_2);
    temperatureC = convertCurrentToTemperature(current_mA);
    RH = convertADCToRH(adc0_2); 

    // SensorData sensorData = readSensor(byteRequest, sizeof(byteRequest));
    // ec = sensorData.ec;
    // ph = sensorData.ph;

    // dtostrf(temperatureC, 6, 2, tempStr);
    // dtostrf(RH, 6, 2, tempStr2);
    // dtostrf(ec, 6, 0, tempStr3); 
    // dtostrf(ph, 6, 2, tempStr4);
    // delay(1000); 

#ifdef USE_UI
    lv_label_set_text(ui_temp, tempStr); 
    lv_label_set_text(ui_humidity, tempStr2);
    lv_label_set_text_fmt(ui_ecValue, tempStr3);
    lv_label_set_text_fmt(ui_phValue, tempStr4);
    
    // Assuming you have labels with names label_input1, label_input2, label_input3, and label_input4
    // lv_label_set_text_fmt(ui_Dvalue1, "%d", inputValues[0]);
    // lv_label_set_text_fmt(ui_Dvalue2, "%d", inputValues[1]);
    // lv_label_set_text_fmt(ui_Dvalue3, "%d", inputValues[2]);
    // lv_label_set_text_fmt(ui_Dvalue4, "%d", inputValues[3]);

    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      input.trim(); 

      if (input == "1") {
        calibrateChannel();
      } else if (input == "2") {
        calibratepH4();
      } else if (input == "3") {
        calibratepH6_86();
      } else if (input == "4") {
        calibratepH9_18();
      } else if (input == "5") {
        run = "run";
        Serial.println("Start running");
      }else if (input == "6") {
        calibrateEc();
      }else if (input == "7") {
        // Serial.println("Input hex");
        // String input2 = Serial.readStringUntil('\n');
        // input2.trim(); 
        // calibrateEc2(input2);
      }else if (input == "8") {
        Serial.println("Start reset1");
        reset();
      }else if (input == "9") {
        Serial.println("Start reset");
        reset2();
      }
      else {
        Serial.println("Invalid input. Please enter 1, 2, 3, or 4.");
      }
      
    }

    // Serial.println("looping");
    if(!Firebase.ready()){
      initFirebase();
      readFirebase();
      Serial.println("Firebase now ready");
    }

    // if (ts.touched()) {
    //     Serial.println("Touch detected!");
    //     Serial.println(touch_last_x);
    //     Serial.println(touch_last_y);
    // } else {
    //     Serial.println("No touch detected.");
    // }

    
    // // GET CONNECTION STATE
    // // get_connection();
    get_status();
    sent_data();

    writeOutput(GPIO5, 1);
    writeOutput(GPIO6, 1);
    writeOutput(GPIO7, 1);
    writeOutput(GPIO8, 1);

    lv_timer_handler();
    lv_task_handler();
    delay(500);
#endif
}
