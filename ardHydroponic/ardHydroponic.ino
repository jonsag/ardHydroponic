/***********
   One Wire, DS18B20
 ***********/
#include <OneWire.h>
const int DS18S20_Pin = A15; // one wire pin
OneWire ds(DS18S20_Pin); // Creating a OneWire object

float TemperatureSum; // The average of a samples taken from one temp test will be stored in this variable
byte data[12]; // Variable to temporary hold readings
byte addr[8]; // Variable to temporary hold the memory adress of the readings

/**********
   STD
 **********/
#include <stdlib.h>

/**********
   LCD
 **********/
#include <LiquidCrystal_I2C.h> // Library for LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Change to (0x27,20,4) for 20x4 LCD.

/**********
   Pumps
 **********/
const int Mosfet_1 = A11; // Pump för PH+
const int Mosfet_2 = A12; // Pump för PH-
const int Mosfet_3 = A13; // Pump för Näringslösning A
const int Mosfet_4 = A14; // Pump för näringslösning B

const int nutrientsPT = 500; // pump time for nutrient pumps
const int PHPPT = 500; // pump time for PH+ pump
const int PHMPT = 500; // pump time for PH- pump

/**********
   EC sensor
 **********/
const int ECPin = A1; // Assigning analog port 1 reference pin
const int ECGround = A2; // Assigning analog port 2 as ground level
const int ECPower = A3; // Assigning analog port 3 as power pin

int R1 = 1000; // Declaring the internal resistance to variable R1
int Ra = 25; // Declaring the powering pin resistance to variable Ra
float EC = 0; // Declaring variable for EC-value
float EC25 = 0; // Declaring variable for the equivialent EC-value at temp 25 celcius
float K = 1.44; // trail measured coefficient
float TemperatureCoef = 0.019; // Temperature coefficient for water that is estimated by trials.
float raw = 0; // The raw data from a EC-sensor reading is declared to this variable
float Vin = 5; // The internal voltage supply from Arduino Uno to a analog pin
float Vdrop = 0; // The voltage drop measured from a EC-reading will be store here
float Rc = 0; // The voltage of the water solvent

/**********
   PH sensor
 **********/
const int pHpin = A0; // Declaring analog port 0 to the pH-sensor probe

unsigned long int avgValue; //Store the average value of the sensor feedback
float phValue; // Storing the calculated pH reading in assinged to this variable
int buf[10], temp; // Temporary variable used to sort the 10 pH reading samples

/**********
   Buttons
 **********/
const int maintButton = 00; // ersätt alla 00 med ingångsnummer *************************************************************************************************************************
const int cleanPHMButton = 00;
const int cleanPHPButton = 00;
const int cleanSLAButton = 00;
const int cleanSLBButton = 00;

int maintenance;
int cleanPHM;
int cleanPHP;
int cleanSLA;
int cleanSLB;

/**********
   Misc
 **********/
const int iterationTime = 10000; // the time before we run another read/pump looop

/**********
   WiFi
 **********/
//#define SSID "A WiFi network" // The name of the WiFI network to connect to is entered here
//#define PASS "password" // The password of the WiFI network to connect to is entered here

/**********
   ThingSpeak
 **********/
//#define IP "184.106.153.149"// The ip-adress for thingspeak.com
//String msg = "GET /update?key=94IADK04DP5YY184"; //A GET parameter associated with the personal thingspeak channel
//____________________________________

void setup() {
  Serial.begin(9600); // Setting the baudrate

  /**********
     LCD
   **********/
  lcd.init();
  lcd.backlight();

  /**********
     In/Outputs
   **********/
  pinMode(Mosfet_1, OUTPUT); // Setting pin modes for the relay board controlling the pump feeding pH down buffer solution
  pinMode(Mosfet_2, OUTPUT); // Setting pin modes for the relay board controlling the pump feeding nutrient solution
  pinMode(Mosfet_3, OUTPUT); // Setting pin modes for the relay board controlling the pump feeding nutrient solution
  pinMode(Mosfet_4, OUTPUT); // Setting pin modes for the relay board controlling the pump feeding nutrient solution
  pinMode(ECPin, INPUT); // Setting pin mode for the input pin for the EC sensor probe
  pinMode(ECPower, OUTPUT); // Setting pin mode for sourcing current
  pinMode(ECGround, OUTPUT); // Setting pin mode for sinking current

  pinMode(maintButton, INPUT);
  pinMode(cleanPHMButton, INPUT);
  pinMode(cleanPHPButton, INPUT);
  pinMode(cleanSLAButton, INPUT);
  pinMode(cleanSLBButton, INPUT);

  /**********
     EC sensor
   **********/
  digitalWrite(ECGround, LOW); // Setting ground level for the EC sensor probe
  R1 = (R1 + Ra); // Taking into account Powering Pin Resitance

  /***********
     WiFi
   ***********/
  //Serial.println("AT"); //Hayes command call for attention
  //delay(5000); // 5000 ms delay
  // connectWiFi(); //Calling on function to connect to WiFI
}

void loop() {
  /**********
     Read buttons
   **********/
  maintenance = digitalRead(maintButton);
  cleanPHM = digitalRead(cleanPHMButton);
  cleanPHP = digitalRead(cleanPHPButton);
  cleanSLA = digitalRead(cleanSLAButton);
  cleanSLB = digitalRead(cleanSLBButton);

  if (!maintenance) { // normal mode

    /**********
       Water temperature
     **********/
    if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
    }
    ds.reset(); // Reset the 1-wire bus
    ds.select(addr); // Selecting the adress of the device to operate
    ds.write(0x44, 1); // Write a byte, and leave power applied to the 1 wire bus.
    byte present = ds.reset();
    ds.select(addr); // Selecting the adress of the device to operate
    ds.write(0xBE); // write to the temperature sensors RAM at this adress

    for (int i = 0; i < 9; i++) { // we need 9 bytes
      data[i] = ds.read(); // Reading the nine bytes stored in the temperature sensors RAM
    }

    ds.reset_search(); // resetting the OneWire device search

    byte MSB = data[1]; // storing the temp reading
    byte LSB = data[0]; // storing the temp reading
    float tempRead = ((MSB << 8) | LSB); // using two's compliment
    TemperatureSum = tempRead / 16; // converting from hexa

    Serial.println("TankTemp: " + String(TemperatureSum));
    //lcd.setCursor(0, 0);
    //lcd.print("TankTemp: ");
    //lcd.print(TemperatureSum);    // print the temperature in Celsius
    //lcd.print((char)223);      // print ° character
    //lcd.print("C");    // print the temperature in Celsius

    /**********
       Read PH value
     **********/
    for (int i = 0; i < 10; i++) { // Get 10 sample value from the sensor for smooth the value
      buf[i] = analogRead(pHpin); // Taking ten analog readings from the pH probe
      delay(10); // 10 ms delay
    }
    for (int i = 0; i < 9; i++) {// sort the 10 analog readings from small to large
      for (int j = i + 1; j < 10; j++) {
        if (buf[i] > buf[j]) {
          temp = buf[i];
          buf[i] = buf[j];
          buf[j] = temp;
        }
      }
    }

    avgValue = 0; // a temporary parameter for the pH readings
    for (int i = 2; i < 8; i++) { // take value of the 6 center samples
      avgValue += buf[i];
    }
    avgValue = avgValue / 6; // take avrage value of the 6 center samples
    phValue = (avgValue * 5.0) / 1024; // convert the analog readings into volt
    phValue = 3.157895 * phValue + 0.9152632; // convert the millivolt into pH value. Floats are coeffiocients from sensor calibration

    Serial.println("PH: " + String(phValue));
    lcd.setCursor(5, 0);
    lcd.print("PH: ");
    lcd.print(phValue); // print PH value

    /**********
       Read EC level
     **********/
    digitalWrite(ECPower, HIGH); // Setting the power pin for EC sensor to high
    raw = analogRead(ECPin);
    raw = analogRead(ECPin); // First reading will be inconclusive due to low charge in probe
    digitalWrite(ECPower, LOW); // Setting the power pin for EC sensor to low

    Serial.println("EC: " + String(EC25));
    lcd.setCursor(5, 2);
    lcd.print("EC: ");
    lcd.print(EC25); // print EC value

    // Convert voltage to EC
    Vdrop = (Vin * raw) / 1024.0; // The voltage drop measured
    Rc = (Vdrop * R1) / (Vin - Vdrop); // The resistance of the water solvent
    Rc = Rc - Ra; // acounting for Digital Pin Resitance
    EC = 1000 / (Rc * K); // The calculate EC value

    // Compensating For the temperature in the water solvent//
    EC25 = EC / (1 + TemperatureCoef * (TemperatureSum - 25.0));

    /**********
       ThingSpeak
     **********/
    // updateTS(); //Calling on funtion to update the ThingSpeak channel with new data

    /**********
       Run pumps
     **********/
    //if (EC25<1.4 && phValue>6.6) { //if the nutrient level unsufficient, and the pH value to high

    /**********
       Nutrient pumps
     **********/
    if (EC25 < 3.0) { // if the nutrient level unsufficient
      digitalWrite(Mosfet_3, HIGH) ; // Doserar näringslösning A
      digitalWrite(Mosfet_4, HIGH) ; // Doserar näringslösning B

      Serial.println("Nutrientpumps ON");
      printToLCD(1, 3, "Nutrientpumps  ON  ");

      delay(nutrientsPT); // Running nutrient pumps

      digitalWrite(Mosfet_3, LOW) ; // Cutting power to pump
      digitalWrite(Mosfet_4, LOW) ; // Cutting power to pump

      Serial.println("Nutrientpumps OFF");
      printToLCD(1, 3, "Nutrientpumps  OFF  ");
    }

    /**********
       PH pumps
     **********/
    if (phValue < 4.62) { // if the pH value to low
      digitalWrite(Mosfet_1, HIGH) ; // Doserar PH+

      Serial.println("Dosingpump PH+ ON");
      printToLCD(1, 1, "Dosingpump PH+ ON   ");

      delay(PHPPT); // Running pump

      digitalWrite(Mosfet_1, LOW) ; //Cutting power to pump

      Serial.println("Dosingpump PH+ OFF");
      printToLCD(1, 1, "Dosingpump PH+ OFF  ");
    }
    else if (phValue > 4.63) { // if the pH is high
      digitalWrite(Mosfet_2, HIGH) ; // Doserar PH-

      Serial.println("Dosingpump PH- ON");
      printToLCD(1, 1, "Dosingpump PH- ON   ");

      delay(PHMPT); // Running pump

      digitalWrite(Mosfet_2, LOW) ; //Cutting power to pump
      Serial.println("Dosingpump PH- OFF  ");
      printToLCD(1, 1, "Dosingpump PH- OFF");
    }

    delay(iterationTime); // Wait before starting next loop iteration

  } else {
    // skriv på skärmen att vi är i underhållsläge ********************************************************************************************************************************
    if (cleanPHM) {
      renspolning_PH_Minus();
    }
    if (cleanPHP) {
      renspolning_PH_Plus();
    }
    if (cleanSLA) {
      renspolning_Slang_A();
    }
    if (cleanSLB) {
      renspolning_Slang_B();
    }
  }
}

//______ThingSpeak channel update function___________
//void updateTS(){
//String cmd = "AT+CIPSTART=\"TCP\",\""; // A serial command to intruct the WiFi chip
// cmd += IP; //Adding the string containing the IP for ThingSpeak
// cmd += "\",80"; // The port to communicate with ThingSpeak through
// Serial.println(cmd); //Establishing connection with ThingSpeak
// delay(2000); // time delay

void renspolning_PH_Minus() {
  Serial.println("Spolar slang PH- under 30 sekunder");
  digitalWrite(Mosfet_1, HIGH) ; //Spolar slangen för PH-
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med PH-          ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(30000); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(Mosfet_1, LOW) ; //stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void renspolning_PH_Plus() {
  Serial.println("Spolar slang PH+ under 30 sekunder");
  digitalWrite(Mosfet_2, HIGH) ; //Spolar slangen för PH+
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med PH+          ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(30000); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(Mosfet_2, LOW) ; //stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void renspolning_Slang_A() {
  Serial.println("Spolar slang A under 30 sekunder");
  digitalWrite(Mosfet_3, HIGH) ; //Spolar slangen nutrion: A
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med nutrion: A   ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(30000); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(Mosfet_3, LOW) ; //stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void renspolning_Slang_B() {
  Serial.println("Spolar slang B under 30 sekunder");
  digitalWrite(Mosfet_4, HIGH) ; //Spolar slangen nutrion: B
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med nutrion: B   ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(30000); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(Mosfet_4, LOW) ; //stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void printToLCD(int col, int row, String text) {
  lcd.setCursor(col, row);
  lcd.print(text);
}
