const float ADC_MAX_VALUE = 65535.0; // Adjust this according to your ADC's max value
const float CURRENT_MIN = 4.0; // Minimum current in mA
const float CURRENT_MAX = 20.0; // Maximum current in mA

enum ReadState {
    READ_ADC0,
    READ_ADC1,
    READ_ADC2,
    READ_CONVERT,
    CHECK_DATA2,
    READ_DONE
};

ReadState readState = READ_ADC0;
int16_t adc0_2 = 0;
int16_t adc1_2 = 0;
float current_mA = 0.0;
static unsigned long lastReadTime = 0;
const unsigned long readInterval = 500;
float temperatureC2, RH2;

void readRhTempNonBlocking() {
        switch (readState) {
            case READ_ADC0:
                if (millis() - lastReadTime >= readInterval) {
                    lastReadTime = millis();
                    adc0_2 = ads2.readADC_SingleEnded(0);
                    readState = READ_ADC1;
                }
                break;

            case READ_ADC1:
                if (millis() - lastReadTime >= readInterval) {
                    lastReadTime = millis();
                    adc1_2 = ads2.readADC_SingleEnded(1);
                    readState = READ_CONVERT;
                }
                break;

            case READ_CONVERT:
                current_mA = convertADCToCurrent(adc1_2);
                temperatureC2 = convertCurrentToTemperature(current_mA);
                RH2 = convertADCToRH(adc0_2);
                readState = CHECK_DATA2;
                break;

            case CHECK_DATA2:
                if(temperatureC2!=temperatureC || RH2!=RH){
                    temperatureC=temperatureC2;
                    RH=RH2;
                    dtostrf(temperatureC, 6, 1, tempStr);
                    dtostrf(RH, 6, 1, tempStr2);
                    readState = READ_DONE;
                }else {
                    readState = READ_ADC0;
                }
                break;

            case READ_DONE:
                if (WiFi.status() == WL_CONNECTED) {
                    sent_datarhtemp();
                }  
                readState = READ_ADC0;
                break;
        }
    

}

float convertADCToRH(int16_t adcValue) {
    const float V_REF = 5.0; // Reference voltage in volts (adjust if necessary)
    const float V_MAX = 5.0; // Maximum output voltage of the sensor for 100% RH (adjust if necessary)

    float V_out = (float)adcValue / ADC_MAX_VALUE * V_REF;
    float RH = (V_out / V_MAX) * 100.0;

    return round(RH * 10) / 10.0;
}

float convertCurrentToTemperature(float current_mA) {
    float temperature = (current_mA - 4.0) * (120.0 / 16.0) - 40.0; // Calculate temperature
    return round(temperature * 10) / 10.0; // Round to 1 decimal
}

float convertADCToCurrent(int16_t adcValue) {
    float current_mA = ((float)adcValue / ADC_MAX_VALUE) * 40.96;
    return current_mA;
}

int sensorValue(int x, int y) {
  int t = 0;
  t = x * 256;
  t = t + y;

  return t;
}

bool readGPIOState(uint8_t gpio) {
    uint8_t inputState = readInput(); // Read the current state of all GPIOs
    return (inputState & gpio) != 0;  // Check if the specified GPIO bit is set
}


#define SENSOR_WAIT_TIME 2000  // Maximum wait time for response in milliseconds
#define SENSOR_FRAME_SIZE 19   // Size of the data frame from the sensor



unsigned long sensorStartTime = 0; // Time when sensor read started
byte command[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; // Example command
byte byteResponse[SENSOR_FRAME_SIZE];
int bytesRead = 0;
#define READ_INTERVAL 1300 
int ec2,ph2,tp2;

void readSensor() {
  byte command[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; // Example command
  byte byteResponse[SENSOR_FRAME_SIZE];

  while (Serial1.available()) {
      Serial1.read();  // Clear any junk data from the buffer
  }
  
  Serial1.write(command, sizeof(command));

  unsigned long resptime = millis();
  while ((Serial1.available() < SENSOR_FRAME_SIZE) && ((millis() - resptime) < SENSOR_WAIT_TIME)) {
    delay(1);
  }
  
  String response = "";
  int bytesRead = 0;
  while (Serial1.available() && bytesRead < SENSOR_FRAME_SIZE) {
    byteResponse[bytesRead++] = Serial1.read();
  }

  String responseString;
  for (int j = 0; j < sensorFrameSize; j++) {
    responseString += byteResponse[j] < 0x10 ? " 0" : " ";
    responseString += String(byteResponse[j], HEX);
    responseString.toUpperCase();
  }
  Serial.println(responseString);

  SensorData data;
  ph = sensorValue(byteResponse[11], byteResponse[12]) * 0.01;
  ec = sensorValue(byteResponse[13], byteResponse[14]);
  tp = sensorValue(byteResponse[15], byteResponse[16]) * 0.1;
  dtostrf(tp, 6, 0, tempStr3);
  dtostrf(ec, 6, 0, tempStr4);
  dtostrf(ph, 6, 0, tempStr5);
} 

void readSensorNonBlocking() {
    static String responseString = "";
    switch (sensorReadState) {
        case INIT_SENSOR_READ:
            if (millis() - sensorStartTime >= READ_INTERVAL) {
                // Serial.println("Read sensor data");
                while (Serial1.available()) {
                    Serial1.read();  
                }
                Serial1.write(command, sizeof(command)); // Send the command
                sensorStartTime = millis(); // Start the timer
                sensorReadState = WAIT_FOR_RESPONSE;
            }
            
            break;

        case WAIT_FOR_RESPONSE:
            // Serial.println("waiting sensor data");
            if (millis() - sensorStartTime >= SENSOR_WAIT_TIME) {
                Serial.println("Sensor response timeout.");
                sensorReadState = READ_COMPLETE;  // Move to complete state
            } else if (Serial1.available()) {
                sensorReadState = READ_SENSOR_DATA; // Move to read data state when data is available
            }
            break;

        case READ_SENSOR_DATA:
            // Serial.println("read sensor data");
            while (Serial1.available() && bytesRead < SENSOR_FRAME_SIZE / 2) {
                byteResponse[bytesRead++] = Serial1.read();
            }
            if (bytesRead >= SENSOR_FRAME_SIZE / 2) {
                sensorReadState = READ_SENSOR_DATA_CONT; // Move to second-half read state
            }
            break;

        case READ_SENSOR_DATA_CONT:
            
            while (Serial1.available() && bytesRead < SENSOR_FRAME_SIZE) {
                byteResponse[bytesRead++] = Serial1.read();
            }

            if (bytesRead == SENSOR_FRAME_SIZE) {
                sensorReadState = PROCESS_SENSOR_DATA; // Move to processing state
            }
            break;

        case PROCESS_SENSOR_DATA:
            responseString = "";
            for (int i = 0; i < SENSOR_FRAME_SIZE; i++) {
                responseString += byteResponse[i] < 0x10 ? " 0" : " ";
                responseString += String(byteResponse[i], HEX);
            }
            Serial.println(responseString); // Print response for debugging
            sensorReadState = SAVE_SENSOR_DATA; // Move to completed state
            break;
        case SAVE_SENSOR_DATA:
            ec2 = sensorValue(byteResponse[13], byteResponse[14]); 
            sensorReadState = SAVE_SENSOR_DATA2;
            break;
        case SAVE_SENSOR_DATA2:
            ph2 = sensorValue(byteResponse[11], byteResponse[12]) * 0.01; 
            sensorReadState = SAVE_SENSOR_DATA3;
            break;
        case SAVE_SENSOR_DATA3:
            tp2 = sensorValue(byteResponse[15], byteResponse[16]) * 0.1; 
            sensorReadState = CHECK_DATA;
            break;
        case CHECK_DATA:
            bytesRead = 0;
            if(ec2!=ec || ph2!=ph || tp2!= tp){
                ec=ec2;
                ph=ph2;
                tp=tp2;
                dtostrf(tp, 6, 0, tempStr3);
                dtostrf(ec, 6, 0, tempStr4);
                dtostrf(ph, 6, 0, tempStr5);
                sensorReadState = SAVE_FIREBASE;
            }else {
                sensorReadState = READ_COMPLETE;
            }
            break;
        case SAVE_FIREBASE:
            if (WiFi.status() == WL_CONNECTED) {
                sent_dataecph();
            }
            sensorReadState = READ_COMPLETE;
            break;
        case READ_COMPLETE:
            sensorReadState = INIT_SENSOR_READ;
            break;
    }
}


