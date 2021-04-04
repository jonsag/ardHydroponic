
void startThingSpeakCmd(void)
{                  // start communication with thingSpeak
  Serial1.flush(); // clears the buffer before starting to write

  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += thingSpeakIP; // Endereco IP de api.thingspeak.com
  cmd += "\",80";
  Serial1.println(cmd);

  Serial.print("Sent ==> Start cmd: ");
  Serial.println(cmd);

  if (Serial1.find("Error"))
  {
    Serial.println("AT+CIPSTART error");
    return;
  }
}

String sendThingSpeakGetCmd(String getStr)
{ // send a GET cmd to ThingSpeak
  String cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial1.println(cmd);
  Serial.print("Sent ==> length cmd: ");
  Serial.println(cmd);

  if (Serial1.find((char *)">"))
  {
    Serial1.print(getStr);
    Serial.print("Sent ==> getStr: ");
    Serial.println(getStr);
    delay(500); // time to process the GET, without this delay it displays busy in the next command

    String messageBody = "";
    while (Serial1.available())
    {
      String line = Serial1.readStringUntil('\n');
      if (line.length() == 1)
      { //actual content starts after empty line (that has length 1)
        messageBody = Serial1.readStringUntil('\n');
      }
    }
    Serial.print("MessageBody received: ");
    Serial.println(messageBody);
    return messageBody;
  }
  else
  {
    Serial1.println("AT+CIPCLOSE");                     // alert user
    Serial.println("ESP8266 CIPSEND ERROR: RESENDING"); //Resend...
    spare = spare + 1;
    error = 1;
    return "error";
  }
}

void writeThingSpeak(void)
{ // connect to thingSpeak

  startThingSpeakCmd();

  // prepare the GET string
  String getStr = "GET /update?api_key=";
  getStr += thingSpeakWriteKey;
  getStr += "&field1=";
  getStr += String(temperatureSum);
  getStr += "&field2=";
  getStr += String(pHValue);
  getStr += "&field3=";
  getStr += String(TDSValue);

  getStr += "\r\n\r\n";

  sendThingSpeakGetCmd(getStr);
}

void EspHardwareReset(void)
{ // reset ESP
  Serial.println("Resetting...");
  digitalWrite(espHardwareReset, LOW);
  delay(500);
  digitalWrite(espHardwareReset, HIGH);
  delay(8000); // time needed to start reading
  Serial.println("RESET!");
}

void sendATCommand(String command)
{
  Serial1.flush(); // clears the buffer before starting to write

  command += "\r\n\r\n";
  Serial1.println(command);

  Serial.print("Sent ==> Command: ");
  Serial.println(command);

  delay(500);
  while (Serial1.available())
  {
    String inData = Serial1.readStringUntil('\n');
    Serial.println("Got response from ESP8266: " + inData);
  }
}