#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <BlynkSimpleEsp8266.h>

#include "secrets.h"

#include "ThingSpeak.h"

boolean debug = 1;

/**********
   WiFi
 **********/
const char *ssid = STASSID;
const char *password = STAPSK;
WiFiClient client;

unsigned long myChannelNumber = channelID;
const char *myWriteAPIKey = apiKey;

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 0; //28800;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//unsigned long epochTime = timeClient.getEpochTime();
//struct tm *ptm = gmtime ((time_t *)&epochTime);

//String SendHTML(float temperatureSum, float pHValue, float tdsValueString, String TimeWeb, String DateWeb, unsigned long uploadedEpoch);
//void handle_OnConnect();
//void handle_NotFound();

/**********
   Times
 **********/
String formattedTime;
String Date;
int Day;
int Month;
int Year;

/**********
   Message
 **********/
String message;

/**********
   Values
 **********/
float temperatureSum = 0.0;
float pHValue = 0.0;
float tdsValue = 0.0;

/**********
   Web server
 **********/
ESP8266WebServer server(80);

/**********
   Outputs
 **********/
const byte relay = 2;
boolean relayState = HIGH;

/**********
   Blynk
 **********/
char *blynkAuth = blynkToken;
int valueV3;
boolean lastValueV3 = HIGH;

BLYNK_WRITE(V3)
{
  valueV3 = param.asInt(); // Get value as integer
  if (valueV3)
  {
    relayState = HIGH;
  }
  else
  {
    relayState = LOW;
  }
  digitalWrite(relay, relayState);
}

/**********
   Misc
 **********/
boolean uploadSuccess = 0;

unsigned long uploadedEpoch;

void setup(void)
{

  Serial.setTimeout(10);
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client); // Initialize ThingSpeak

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.on("/toggleRelay", handle_toggleRelay);
  server.begin();

  timeClient.begin();

  if (debug)
    Serial.println("HTTP server started");

  pinMode(relay, OUTPUT);
  digitalWrite(relay, relayState);

  Serial.print("Starting blynk and attempting to connect to SSID: ");
  Serial.print(STASSID);
  Serial.println("...");

  Blynk.begin(blynkAuth, ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {

    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop(void)
{
  if (WiFi.status() != WL_CONNECTED)
  { // connect or reconnect to WiFi
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(STASSID);
    WiFi.begin(ssid, password); // connect to WPA/WPA2 network
    while (WiFi.status() != WL_CONNECTED)
    {

      Serial.print(".");
      delay(500);
    }
    Serial.println("\nConnected.");
  }

  Blynk.run();

  server.handleClient();
  //MDNS.update();

  message = "";

  while (Serial.available())
  {
    // read the incoming byte:
    message = Serial.readString();

    decodeMessage(message);
  }
}

void handle_OnConnect()
{

  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
  String formattedTime = timeClient.getFormattedTime();

  struct tm *ptm = gmtime((time_t *)&epochTime);
  while (Serial1.available())
  {
    Serial.write(Serial1.read());
  }
  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon + 1;
  int currentYear = ptm->tm_year + 1900;

  Date = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);

  server.send(200, "text/html", SendHTML(temperatureSum, pHValue, tdsValue, formattedTime, Date, epochTime, uploadedEpoch, uploadSuccess, relayState));
}

void handle_NotFound()
{
  String message404 = "File Not Found\n\n";
  message404 += "URI: ";
  message404 += server.uri();
  message404 += "\nMethod: ";
  message404 += (server.method() == HTTP_GET) ? "GET" : "POST";
  message404 += "\nArguments: ";
  message404 += server.args();
  message404 += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message404 += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message404);
}

void handle_toggleRelay()
{
  if (relayState)
  {
    relayState = LOW;
  }
  else
  {
    relayState = HIGH;
  }

  digitalWrite(relay, relayState);
  Blynk.virtualWrite(V3, relayState);

  String togglePage = "<!DOCTYPE html>\n<html>\n";
  togglePage += "<head><meta name = \"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; // head
  togglePage += "<title>ESP8266 espHydroponic</title>\n";
  togglePage += "</head>\n";

  togglePage += "<body>\n"; // body
  togglePage += "<div id=\"webpage\">\n";

  togglePage += "<h1>espHydroponic</h1>\n";

  if (relayState)
  {
    togglePage += "<p>Pumps enabled</p>";
  }
  else
  {
    togglePage += "<p>Pumps disabled</p>";
  }

  togglePage += "<br>\n<button onclick = \"goBack()\">Go Back </button>\n";
  togglePage += "<script>\n";
  togglePage += "function goBack() {\n";
  togglePage += "window.history.back();\n";
  togglePage += "}\n";
  togglePage += "</script>\n";

  togglePage += "<p>Don't forget to refresh page once there</p>\n";

  togglePage += "</div>\n";
  togglePage += "</body>\n";
  togglePage += "</html>\n";

  server.send(200, "text / html", togglePage);
  //handle_OnConnect();
}

String SendHTML(float temperatureSum, float pHValue, float tdsValueString, String TimeWeb, String DateWeb, unsigned long epochTime, unsigned long uploadedEpoch, boolean uploadSuccess, boolean relayState)
{
  String mainPage = "<!DOCTYPE html>\n<html>\n";
  mainPage += "<head><meta name = \"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n"; // head
  mainPage += "<title>ESP8266 espHydroponic</title>\n";
  mainPage += "</head>\n";

  mainPage += "<body>\n"; // body
  mainPage += "<div id=\"webpage\">\n";

  mainPage += "<h1>espHydroponic</h1>\n"; // header

  mainPage += "<p>Date: "; // time and date
  mainPage += (String)DateWeb;
  mainPage += "\n";
  mainPage += "<br>Time: ";
  mainPage += (String)TimeWeb;
  mainPage += " UTC\n";

  if (debug)
  {
    mainPage += "<br>Epoch: ";
    mainPage += epochTime;
    Blynk.virtualWrite(V2, tdsValue);
  }
  mainPage += "</p>\n";

  mainPage += "<p>Temp: "; // values
  mainPage += temperatureSum;
  mainPage += "&#176;C\n";
  mainPage += "<br>pH: ";
  mainPage += pHValue;
  mainPage += "\n";
  mainPage += "<br>TDS: ";
  mainPage += (int)tdsValue;
  mainPage += " ppm</p>\n";

  mainPage += "<p>Collected "; // how old are values
  mainPage += epochTime - uploadedEpoch;
  mainPage += " seconds ago\n";

  if (debug)
  {
    mainPage += "<br>Collected epoch: ";
    mainPage += uploadedEpoch;
    mainPage += "</p>\n";
  }

  mainPage += "<p>Upload "; // uploaded
  if (uploadSuccess)
  {
    mainPage += "successful";
  }
  else
  {
    mainPage += "failed";
  }
  mainPage += "</p>\n";

  mainPage += "<p>Pumps are "; // uploaded
  if (relayState)
  {
    mainPage += "enabled\n";
    mainPage += "<br><a href=\"/toggleRelay\">Disable pumps</a>\n";
  }
  else
  {
    mainPage += "disabled";
    mainPage += "<br><a href=\"/toggleRelay\">Enable pumps</a>\n";
  }
  mainPage += "</p>\n";

  mainPage += "<p><FORM>\n";
  mainPage += "<INPUT TYPE=\"button\" onClick=\"history.go(0)\" VALUE=\"Refresh page\">\n";
  mainPage += "</FORM></p>\n";

  mainPage += "</div>\n";
  mainPage += "</body>\n";
  mainPage += "</html>\n";
  return mainPage;
}

void decodeMessage(String message)
{
  message.trim();

  if (debug)
    Serial.println();
  if (debug)
    Serial.print("Message as String: ");
  if (debug)
    Serial.print(message);
  if (debug)
    Serial.println();
  if (debug)
    Serial.print("String length: ");
  if (debug)
    Serial.println(message.length());

  boolean validData = 1;

  if (message.indexOf("Temp:") >= 0 && message.indexOf("pH:") >= 0 && message.indexOf("TDS:") >= 0)
  {

    if (debug)
      Serial.println("Message has data");
    int str_len = message.length() + 1; // length (with one extra character for the null terminator)
    char char_array[str_len];           // prepare the character array (the buffer)

    message.toCharArray(char_array, str_len); // copy it over to array buffer

    if (debug)
      Serial.print("Message as char array: ");
    if (debug)
      Serial.print(char_array);
    if (debug)
      Serial.println();

    int i;
    char delimiter[] = ",";
    char *p;
    String words[3];

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
      if (words[i].indexOf("Temp:") >= 0)
      {
        if (debug)
          Serial.println("Found temperature");
        words[i].remove(0, 5);
        temperatureSum = words[i].toFloat();
        if (debug)
          Serial.print("Temp: ");
        if (temperatureSum)
        {
          if (debug)
            Serial.println(temperatureSum);
        }
        else
        {
          validData = 0;
          if (debug)
            Serial.println("NA");
        }
      }
      else if (words[i].indexOf("pH:") >= 0)
      {
        if (debug)
          Serial.println("Found pH");
        words[i].remove(0, 3);
        pHValue = words[i].toFloat();
        if (debug)
          Serial.print("pH: ");
        if (pHValue)
        {
          if (debug)
            Serial.println(pHValue);
        }
        else
        {
          validData = 0;
          if (debug)
            Serial.println("NA");
        }
      }
      else if (words[i].indexOf("TDS:") >= 0)
      {
        if (debug)
          Serial.println("Found TDS");
        words[i].remove(0, 4);
        tdsValue = words[i].toFloat();
        if (debug)
          Serial.print("TDS: ");
        if (tdsValue)
        {
          if (debug)
            Serial.println(tdsValue);
        }
        else
        {
          validData = 0;
          if (debug)
            Serial.println("NA");
        }
      }
    }

    if (validData)
    {
      if (debug)
        Serial.println("Uploading data...");
      ThingSpeak.setField(1, temperatureSum);
      ThingSpeak.setField(2, pHValue);
      ThingSpeak.setField(3, tdsValue);

      int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // write to the ThingSpeak channel

      if (x == 200)
      {
        if (debug)
          Serial.println("Channel update successful.");
        uploadSuccess = 1;
      }
      else
      {
        if (debug)
          Serial.println("Problem updating channel. HTTP error code " + String(x));
        uploadSuccess = 0;
      }

      timeClient.update();
      //uploadedTime = timeClient.getFormattedTime();
      uploadedEpoch = timeClient.getEpochTime();

      Blynk.virtualWrite(V0, temperatureSum);
      Blynk.virtualWrite(V1, pHValue);
      Blynk.virtualWrite(V2, tdsValue);
    }
    else
    {
      if (debug)
        Serial.println("Did not contain valid data");
    }
  }
  else if (message == "i")
  {
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    if (debug)
      Serial.println("Message is not valid");
  }

  if (debug)
    Serial.println();
}
