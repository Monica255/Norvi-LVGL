unsigned char byteRequest[8] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03, 0x05, 0xCB}; // Adjusting the starting address and count
unsigned char byteResponseConfig[8] = {};

String sendCommand(byte* command, size_t commandSize) {
  while (Serial1.available()) {
      Serial1.read();  // Clear any junk data from the buffer
  }

  Serial1.write(command, commandSize); // Send the command
  delay(8000); // Short delay for processing
  
  String response = "";
  while (Serial1.available()) {
    byte byteRead = Serial1.read();
    response += byteRead < 0x10 ? " 0" : " ";  // Add leading space for single digits
    response += String(byteRead, HEX);  // Convert byte to hex and append to the response
  }

  response.toUpperCase();  // Ensure the response is in uppercase
  return response;
}

void calibratepH() {
  // Step 1: Select pH Calibration Channel
  String x;

  byte selectChannelCommand[] = {0x01, 0x06, 0x00, 0x6F, 0x00, 0x00, 0xB9, 0xD7};
  do{
    x= sendCommand(selectChannelCommand, sizeof(selectChannelCommand));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  }while(x != "0106006F0000B9D7");
   
  byte ph4Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x01, 0x98, 0x16};
  do {
    x = sendCommand(ph4Command, sizeof(ph4Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  } while (x != "0106006900019816");

  byte ph6Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x02, 0xD8, 0x17};
  do {
    x = sendCommand(ph6Command, sizeof(ph6Command));
    x.replace(" ", ""); // Remove spaces from response
    Serial.println("Received (formatted): " + x);
  } while (x != "010600690002D817");

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
  byte commandBytes[8];
  
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
  
  String response;

  // byte ph6Command[] = {0x01, 0x06, 0x00, 0x69, 0x00, 0x03, 0x19, 0xD7};
  // do {
  //   response = sendCommand(ph6Command, sizeof(ph6Command));
  //   response.replace(" ", "");
  //   Serial.println("Received (formatted): " + response);
  // } while (response != "01060069000319D7");
  // Serial.println("Calibrated to pH 6.86 successfully.");


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
