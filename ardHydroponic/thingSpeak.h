
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
