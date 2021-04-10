#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "secrets.h"

#include "ThingSpeak.h"

boolean debug = 1;

const char* ssid = STASSID;
const char* password = STAPSK;
WiFiClient  client;

unsigned long myChannelNumber = channelID;
const char * myWriteAPIKey = apiKey;

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 0; //28800;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//unsigned long epochTime = timeClient.getEpochTime();
//struct tm *ptm = gmtime ((time_t *)&epochTime);

//String SendHTML(float temperatureSum, float pHValue, float tdsValueString, String TimeWeb, String DateWeb, unsigned long uploadedEpoch);
//void handle_OnConnect();
//void handle_NotFound();

String formattedTime;
String Date;
int Day;
int Month;// Use this file to store all of the private credentials
          // and connection details

#define SECRET_SSID "MySSID"    // replace MySSID with your WiFi network name
#define SECRET_PASS "MyPassword"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 000000     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "XYZ"   // replace XYZ with your channel write API Key
int Year;

int incomingByte = 0;
String message = "";

float temperatureSum = 0.0;
float pHValue = 0.0;
float tdsValue = 0.0;

unsigned long uploadedEpoch;
//String uploadedTime;

boolean uploadSuccess = 0;

ESP8266WebServer server(80);

void setup(void) {

  Serial.setTimeout(10);
  Serial.begin(115200);

  /*
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (debug) Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (debug) Serial.print(".");
  }

  if (debug) Serial.println(WiFi.status());
  if (debug) Serial.println("");
  if (debug) Serial.print("Connected to ");
  if (debug) Serial.println(ssid);
  if (debug) Serial.print("IP address: ");
  if (debug) Serial.println(WiFi.localIP());
*/

  /*
    if (MDNS.begin("esp8266")) {
      if (debug) Serial.println("MDNS responder started");
    }
  */

WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);  // Initialize ThingSpeak

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  timeClient.begin();

  

  if (debug) Serial.println("HTTP server started");
}

void loop(void) {
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(500);     
    } 
    Serial.println("\nConnected.");
  }
  
  server.handleClient();
  //MDNS.update();

  message = "";
  //incomingByte = 0;

  while (Serial.available())
  {
    // read the incoming byte:
    message = Serial.readString();

    decodeMessage(message);

  }

}

void handle_OnConnect() {

  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();

  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;

  Date = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

  server.send(200, "text/html", SendHTML(temperatureSum, pHValue, tdsValue, formattedTime, Date, epochTime, uploadedEpoch, uploadSuccess));
}

void handle_NotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

String SendHTML(float temperatureSum, float pHValue, float tdsValueString, String TimeWeb, String DateWeb, unsigned long epochTime, unsigned long uploadedEpoch, boolean uploadSuccess) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 Global Server</title>\n";

  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "</p>\n";
  ptr += "<h1>espHydroponic</h1>\n";

  ptr += "<p>Date: ";
  ptr += (String)DateWeb;
  ptr += "\n";
  ptr += "<br>Time: ";
  ptr += (String)TimeWeb;
  ptr += " UTC\n";

  if (debug) {
    ptr += "<br>Epoch: ";
    ptr += epochTime;
  }
  ptr += "</p>\n";

  ptr += "<p>Temp: ";
  ptr += temperatureSum;
  ptr += "&#176;C\n";
  ptr += "<br>pH: ";
  ptr += pHValue;
  ptr += "\n";
  ptr += "<br>TDS: ";
  ptr += (int)tdsValue;
  ptr += " ppm</p>\n";

  ptr += "<p>Collected ";
  ptr += epochTime - uploadedEpoch;
  ptr += " seconds ago\n";

  if (debug) {
    ptr += "<br>Collected epoch: ";
    ptr += uploadedEpoch;
    ptr += "\n";
  }

  ptr += "<br>Upload ";
  if (uploadSuccess) {
    ptr += "successful";
  } else {
    ptr += "failed";
  }
  ptr += "</p>\n";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}

void decodeMessage(String message) {
  if (debug) Serial.println();
  if (debug) Serial.print("Message as String: ");
  if (debug) Serial.print(message);

  boolean valid = 1;

  if (message.indexOf("Temp:") >= 0 && message.indexOf("pH:") >= 0 && message.indexOf("TDS:") >= 0 ) {

    if (debug) Serial.println("Message has data");

    int str_len = message.length() + 1; // length (with one extra character for the null terminator)
    char char_array[str_len]; // prepare the character array (the buffer)

    message.toCharArray(char_array, str_len); // copy it over to array buffer

    if (debug) Serial.print("Message as char array: ");
    if (debug) Serial.print(char_array);

    int i;
    char delimiter[] = ",";
    char *p;
    //char string[128];
    //String test = "first|Second|third";
    String words[3];

    //test.toCharArray(string, sizeof(string));
    i = 0;
    p = strtok(char_array, delimiter);
    while (p && i < 3)
    {
      words[i] = p;
      p = strtok(NULL, delimiter);
      ++i;
    }

    for (i = 0; i < 3; ++i)
    {
      if (words[i].indexOf("Temp:") >= 0) {
        if (debug) Serial.println("Found temperature");
        words[i].remove(0, 5);
        temperatureSum = words[i].toFloat();
        if (debug) Serial.print("Temp: ");
        if (temperatureSum) {
          if (debug) Serial.println(temperatureSum);
        } else {
          valid = 0;
          if (debug) Serial.println("NA");// Use this file to store all of the private credentials
          // and connection details

#define SECRET_SSID "MySSID"    // replace MySSID with your WiFi network name
#define SECRET_PASS "MyPassword"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 000000     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "XYZ"   // replace XYZ with your channel write API Key
        }
      } else if (words[i].indexOf("pH:") >= 0) {
        if (debug) Serial.println("Found pH");
        words[i].remove(0, 3);
        pHValue = words[i].toFloat();
        if (debug) Serial.print("pH: ");
        if (pHValue) {
          if (debug) Serial.println(pHValue);
        } else {
          valid = 0;
          if (debug) Serial.println("NA");
        }
      } else if (words[i].indexOf("TDS:") >= 0) {
        if (debug) Serial.println("Found TDS");
        words[i].remove(0, 4);
        tdsValue = words[i].toFloat();
        if (debug) Serial.print("TDS: ");
        if (tdsValue) {
          if (debug) Serial.println(tdsValue);
        } else {
          valid = 0;
          if (debug) Serial.println("NA");
        }
      }
    }


    if (valid) {
      if (debug) Serial.println("Uploading data...");
      ThingSpeak.setField(1, temperatureSum);
      ThingSpeak.setField(2, pHValue);
      ThingSpeak.setField(3, tdsValue);

      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // write to the ThingSpeak channel
      
      if (x == 200) {
        if (debug) Serial.println("Channel update successful.");
        uploadSuccess = 1;
      }
      else {
        if (debug) Serial.println("Problem updating channel. HTTP error code " + String(x));
        uploadSuccess = 0;
      }
      timeClient.update();
      //uploadedTime = timeClient.getFormattedTime();
      uploadedEpoch = timeClient.getEpochTime();

    } else {
      if (debug) Serial.println("Did not contain valid data");
    }

  } else {
    if (debug) Serial.println("Message does not have valid data");
  }

  if (debug) Serial.println();
}
