
void esp01StartThingSpeakCmd(void)
{                  // start communication with thingSpeak
  Serial1.flush(); // clears the buffer before starting to write

  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += thingSpeakIP; // Endereco IP de api.thingspeak.com
  cmd += "\",80";
  Serial1.println(cmd);

  if (debug)
    Serial.print("Sent ==> Start cmd: ");
  if (debug)
    Serial.println(cmd);

  if (Serial1.find("Error"))
  {
    if (debug)
      Serial.println("AT+CIPSTART error");
    return;
  }
}

String esp01SendThingSpeakGetCmd(String getStr)
{ // send a GET cmd to ThingSpeak
  String cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial1.println(cmd);
  if (debug)
    Serial.print("Sent ==> length cmd: ");
  if (debug)
    Serial.println(cmd);

  if (Serial1.find((char *)">"))
  {
    Serial1.print(getStr);
    if (debug)
      Serial.print("Sent ==> getStr: ");
    if (debug)
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
    if (debug)
      Serial.print("MessageBody received: ");
    if (debug)
      Serial.println(messageBody);
    return messageBody;
  }
  else
  {
    Serial1.println("AT+CIPCLOSE"); // alert user
    if (debug)
      Serial.println("ESP8266 CIPSEND ERROR: RESENDING"); //Resend...
    spare = spare + 1;
    error = 1;
    return "error";
  }
}

void writeThingSpeak(void)
{ // connect to thingSpeak

#ifdef esp01
  esp01StartThingSpeakCmd();

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

  esp01SendThingSpeakGetCmd(getStr);
#endif
}

void esp01SendATCommand(String command)
{
  Serial1.flush(); // clears the buffer before starting to write

  command += "\r\n\r\n";
  Serial1.println(command);

  if (debug)
    Serial.print("Sent ==> Command: ");
  if (debug)
    Serial.println(command);

  String messageBody = "";
  while (Serial1.available())
  {
    String line = Serial1.readStringUntil('\n');
    if (line.length() == 1)
    { //actual content starts after empty line (that has length 1)
      messageBody = Serial1.readStringUntil('\n');
    }
  }
  if (debug)
    Serial.print("MessageBody received: ");
  if (debug)
    Serial.println(messageBody);

  /*  
  while (Serial1.available())
  {
    if (debug) Serial.print(Serial1.read());
    //String inData = Serial1.readStringUntil('\n');
    //if (debug) Serial.println("Got response from ESP8266: " + inData);
  }
  */
}