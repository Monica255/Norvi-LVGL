const float ADC_MAX_VALUE = 65535.0; // Adjust this according to your ADC's max value
const float CURRENT_MIN = 4.0; // Minimum current in mA
const float CURRENT_MAX = 20.0; // Maximum current in mA

unsigned char byteResponse[sensorFrameSize] = {};



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

SensorData readSensor(byte* command, size_t commandSize) {
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

  SensorData data;
  data.ph = sensorValue(byteResponse[11], byteResponse[12]) * 0.01;
  data.ec = sensorValue(byteResponse[13], byteResponse[14]);
  data.temperature = sensorValue(byteResponse[15], byteResponse[16]) * 0.1;

  return data;
}