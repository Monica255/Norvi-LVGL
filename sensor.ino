const float ADC_MAX_VALUE = 65535.0; // Adjust this according to your ADC's max value
const float CURRENT_MIN = 4.0; // Minimum current in mA
const float CURRENT_MAX = 20.0; // Maximum current in mA

enum ReadState {
    READ_ADC0,
    READ_ADC1,
    READ_ADC2,
    READ_CONVERT,
    READ_DONE
};

ReadState readState = READ_ADC0;
int16_t adc0_2 = 0;
int16_t adc1_2 = 0;
int16_t adc2_2 = 0;
float current_mA = 0.0;

void readRhTempNonBlocking() {
    static unsigned long lastReadTime = 0;
    static unsigned long lastReadTime2 = 0;
    static unsigned long lastReadTime3 = 0;
    const unsigned long readInterval = 1000; // Adjust as necessary for ADC sampling time

    switch (readState) {
        case READ_ADC0:
            if (millis() - lastReadTime >= readInterval) {
                lastReadTime = millis();
                adc0_2 = ads2.readADC_SingleEnded(0);
                readState = READ_ADC1;
            }
            break;

        case READ_ADC1:
            if (millis() - lastReadTime2 >= readInterval) {
                lastReadTime2 = millis();
                adc1_2 = ads2.readADC_SingleEnded(1); 
                readState = READ_CONVERT;
            }
            break;

        case READ_ADC2:
            if (millis() - lastReadTime2 >= readInterval) {
                lastReadTime2 = millis();
                adc2_2 = ads2.readADC_SingleEnded(2); 
                readState = READ_CONVERT;
            }
            break;

        case READ_CONVERT:
            current_mA = convertADCToCurrent(adc1_2);
            temperatureC = convertCurrentToTemperature(current_mA);
            RH = convertADCToRH(adc0_2);
            valSoil = convertADCToRH(adc2_2);

            dtostrf(temperatureC, 6, 2, tempStr);
            dtostrf(RH, 6, 2, tempStr2);
            dtostrf(valSoil, 6, 2, tempStr3);
            readState = READ_DONE;
            break;

        case READ_DONE:
            sent_datarhtemp();
            readState = READ_ADC0;
            // Reading completed, reset or handle data as needed
            break;
    }
}



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

// SensorData readSensor(byte* command, size_t commandSize) {
//   while (Serial1.available()) {
//       Serial1.read();  // Clear any junk data from the buffer
//   }
  
//   Serial1.write(command, commandSize);

//   unsigned long resptime = millis();
//   while ((Serial1.available() < sensorFrameSize) && ((millis() - resptime) < sensorWaitingTime)) {
//     delay(1);
//   }
  
//   String response = "";
//   int bytesRead = 0;
//   while (Serial1.available() && bytesRead < sensorFrameSize) {
//     byteResponse[bytesRead++] = Serial1.read();
//   }

//   String responseString;
//   for (int j = 0; j < sensorFrameSize; j++) {
//     responseString += byteResponse[j] < 0x10 ? " 0" : " ";
//     responseString += String(byteResponse[j], HEX);
//     responseString.toUpperCase();
//   }
//   Serial.println(responseString);

//   SensorData data;
//   data.ph = sensorValue(byteResponse[11], byteResponse[12]) * 0.01;
//   data.ec = sensorValue(byteResponse[13], byteResponse[14]);
//   data.temperature = sensorValue(byteResponse[15], byteResponse[16]) * 0.1;

//   return data;
// } 

#define SENSOR_WAIT_TIME 5000  // Maximum wait time for response in milliseconds
#define SENSOR_FRAME_SIZE 19   // Size of the data frame from the sensor

//unsigned long lastReadTime = 0; // Last time data was requested
unsigned long sensorStartTime = 0; // Time when sensor read started
byte command[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; // Example command
byte byteResponse[SENSOR_FRAME_SIZE];
int bytesRead = 0;
#define READ_INTERVAL 500 
int ec2,ph2;

void readSensorNonBlocking() {
     static String responseString = "";
    switch (sensorReadState) {
        case INIT_SENSOR_READ:
            if (millis() - sensorStartTime >= READ_INTERVAL) {
                Serial.println("init sensor");
                while (Serial1.available()) {
                    Serial1.read();  // Clear any junk data from the buffer
                }
                Serial1.write(command, sizeof(command)); // Send the command
                sensorStartTime = millis(); // Start the timer
                sensorReadState = WAIT_FOR_RESPONSE;
            }
            
            break;

        case WAIT_FOR_RESPONSE:
            Serial.println("waiting sensor data");
            if (millis() - sensorStartTime >= SENSOR_WAIT_TIME) {
                Serial.println("Sensor response timeout.");
                sensorReadState = READ_COMPLETE;  // Move to complete state
            } else if (Serial1.available()) {
                sensorReadState = READ_SENSOR_DATA; // Move to read data state when data is available
            }
            break;

        case READ_SENSOR_DATA:
            Serial.println("read sensor data (first half)");
            // Read half of the frame size
            while (Serial1.available() && bytesRead < SENSOR_FRAME_SIZE / 2) {
                byteResponse[bytesRead++] = Serial1.read();
            }

            // Check if the first half is read
            if (bytesRead >= SENSOR_FRAME_SIZE / 2) {
                sensorReadState = READ_SENSOR_DATA_CONT; // Move to second-half read state
            }
            break;

        case READ_SENSOR_DATA_CONT:
            Serial.println("read sensor data (second half)");
            // Read the remaining half of the frame size
            while (Serial1.available() && bytesRead < SENSOR_FRAME_SIZE) {
                byteResponse[bytesRead++] = Serial1.read();
            }

            // Check if the full frame is read
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

        case SAVE_SENSOR_DATA:

            ec2 = sensorValue(byteResponse[13], byteResponse[14]); 
            sensorReadState = SAVE_SENSOR_DATA2;

        case SAVE_SENSOR_DATA2:
            ph2 = sensorValue(byteResponse[11], byteResponse[12]) * 0.01; 
            sensorReadState = CHECK_DATA;
        case CHECK_DATA:
            bytesRead = 0;
            if(ec2!=ec || ph2!=ph){
                ec=ec2;
                ph=ph2;
                sensorReadState = SAVE_FIREBASE;
            }else {
                sensorReadState = READ_COMPLETE;
            }

        case SAVE_FIREBASE:
            sent_dataecph();
            sensorReadState = READ_COMPLETE;
        case READ_COMPLETE:
            Serial.println("completed");
            sensorReadState = INIT_SENSOR_READ;
            break;
    }
}


