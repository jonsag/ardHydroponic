
/*
void updateTS()
{                                          // ThingSpeak channel update function
    String cmd = "AT+CIPSTART=\"TCP\",\""; // a serial command to instruct the WiFi chip
    cmd += IP;                             // adding the string containing the IP for ThingSpeak
    cmd += "\",80";                        // the port to communicate with ThingSpeak through
    Serial.println(cmd);                   // establishing connection with ThingSpeak
    delay(2000);                           // time delay
}

void updateThingSpeak()
{
    updateTS(); // calling on function to update the ThingSpeak channel with new data
}
*/

void startThingSpeakCmd(void)
{ // start communication with thingSpeak
  espSerial.flush(); // clears the buffer before starting to write
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += thingSpeakIP; // Endereco IP de api.thingspeak.com
  cmd += "\",80";
  espSerial.println(cmd);
  Serial.print("Sent ==> Start cmd: ");
  Serial.println(cmd);

  if(espSerial.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
}

String sendThingSpeakGetCmd(String getStr)
{ // send a GET cmd to ThingSpeak
  String cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.println(cmd);
  Serial.print("Sent ==> length cmd: ");
  Serial.println(cmd);

  if(espSerial.find((char *)">"))
  {
    espSerial.print(getStr);
    Serial.print("Sent ==> getStr: ");
    Serial.println(getStr);
    delay(500); // time to process the GET, without this delay it displays busy in the next command

    String messageBody = "";
    while (espSerial.available()) 
    {
      String line = espSerial.readStringUntil('\n');
      if (line.length() == 1) 
      { //actual content starts after empty line (that has length 1)
        messageBody = espSerial.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody received: ");
    Serial.println(messageBody);
    return messageBody;
  }
  else
  {
    espSerial.println("AT+CIPCLOSE");     // alert user
    Serial.println("ESP8266 CIPSEND ERROR: RESENDING"); //Resend...
    spare = spare + 1;
    error=1;
    return "error";
  } 
}

void writeThingSpeak(void)
{ // connect to thingSpeak

  startThingSpeakCmd();

  // prepare the GET string
  String getStr = "GET /update?api_key=";
  getStr += thingSpeakWriteKey;
  getStr +="&field1=";
  getStr += String(temperatureSum);
  getStr +="&field2=";
  getStr += String(pHValue);
  getStr +="&field3=";
  getStr += String(TDSValue);
 
  getStr += "\r\n\r\n";

  sendThingSpeakGetCmd(getStr); 
}

void EspHardwareReset(void)
{ // reset ESP
  Serial.println("Resetting......."); 
  digitalWrite(ESP_HARDWARE_RESET, LOW); 
  delay(500);
  digitalWrite(ESP_HARDWARE_RESET, HIGH);
  delay(8000); // time needed to start reading 
  Serial.println("RESET"); 
}

