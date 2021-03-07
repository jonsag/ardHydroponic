/**********
 * Include files
 **********/
#include "config.h"
#include "read.h"
#include "LCD.h"
#include "clean.h"

void setup()
{
  /***********
   Serial
 ***********/
  Serial.begin(serialBaudRate); // serial baudrate

  /*******************************
      Print start information
    *******************************/
  Serial.println(programName); // print information
  Serial.println(date);
  Serial.print("by ");
  Serial.println(author);
  Serial.println(email);
  Serial.println();

  /**********
     LCD
   **********/
  lcd.init();
  lcd.backlight();

  /**********
     In/Outputs
   **********/
  pinMode(PhPlusPump, OUTPUT);
  pinMode(PhMinusPump, OUTPUT);
  pinMode(nutrAPump, OUTPUT);
  pinMode(nutrBPump, OUTPUT);

  pinMode(ECPin, INPUT);     // EC sensor probe
  pinMode(ECPower, OUTPUT);  // sourcing current
  pinMode(ECGround, OUTPUT); // sinking current

  pinMode(maintButton, INPUT);
  pinMode(cleanPhMinusButton, INPUT);
  pinMode(cleanPhPlusButton, INPUT);
  pinMode(cleanNutrAButton, INPUT);
  pinMode(cleanNutrBButton, INPUT);

  /**********
     EC sensor
   **********/
  digitalWrite(ECGround, LOW); // ground level for the EC sensor probe
  R1 = (R1 + Ra);              // taking into account powering pin resistance

  /***********
     WiFi
   ***********/
  //Serial.println("AT"); // Hayes command call for attention
  //delay(5000); // 5000 ms delay
  // connectWiFi(); // Calling on function to connect to WiFI
}

void loop()
{
  /**********
     Read buttons
   **********/
  maintenance = digitalRead(maintButton);
  cleanPhMinus = digitalRead(cleanPhMinusButton);
  cleanPhPlus = digitalRead(cleanPhPlusButton);
  cleanNutrA = digitalRead(cleanNutrAButton);
  cleanNutrB = digitalRead(cleanNutrBButton);

  if (!maintenance)
  { // normal mode

    /**********
       Water temperature
     **********/
    TemperatureSum = readWaterTemp();

    Serial.println("TankTemp: " + String(TemperatureSum));
    //lcd.setCursor(0, 0);
    //lcd.print("TankTemp: ");
    //lcd.print(TemperatureSum);    // temperature in Celsius
    //lcd.print((char)223);      // ° character
    //lcd.print("C");    // temperature in Celsius

    /**********
       Read PH value
     **********/
    phValue = readPhValue();

    Serial.println("PH: " + String(phValue));
    lcd.setCursor(5, 0);
    lcd.print("PH: ");
    lcd.print(phValue); // print PH value

    /**********
       Read EC level
     **********/
    EC25 = readECLevel();

    Serial.println("EC: " + String(EC25));
    lcd.setCursor(5, 2);
    lcd.print("EC: ");
    lcd.print(EC25); // print EC value

    /**********
       ThingSpeak
     **********/
    // updateTS(); //Calling on function to update the ThingSpeak channel with new data

    /**********
       Run pumps
     **********/
    //if (EC25<1.4 && phValue>6.6) { // if the nutrient level unsufficient, and the pH value to high

    /**********
       Nutrient pumps
     **********/
    if (EC25 < 3.0)
    {                                // if the nutrient level unsufficient
      digitalWrite(nutrAPump, HIGH); // dosing nutrition A
      digitalWrite(nutrBPump, HIGH); // dosing nutrition B

      Serial.println("Nutrientpumps ON");
      printToLCD(1, 3, "Nutrientpumps  ON  ");

      delay(nutrientsPumpTime); // running nutrient pumps

      digitalWrite(nutrAPump, LOW); // cutting power to pump
      digitalWrite(nutrBPump, LOW); // cutting power to pump

      Serial.println("Nutrientpumps OFF");
      printToLCD(1, 3, "Nutrientpumps  OFF  ");
    }

    /**********
       PH pumps
     **********/
    if (phValue < 4.62)
    {                                 // if the pH value to low
      digitalWrite(PhPlusPump, HIGH); // dosing PH+

      Serial.println("Dosingpump PH+ ON");
      printToLCD(1, 1, "Dosingpump PH+ ON   ");

      delay(PhPlusPumpTime); // running pump

      digitalWrite(PhPlusPump, LOW); // cutting power to pump

      Serial.println("Dosingpump PH+ OFF");
      printToLCD(1, 1, "Dosingpump PH+ OFF  ");
    }
    else if (phValue > 4.63)
    {                                  // if the pH is high
      digitalWrite(PhMinusPump, HIGH); // dosing PH-

      Serial.println("Dosingpump PH- ON");
      printToLCD(1, 1, "Dosingpump PH- ON   ");

      delay(PhMinusPumpTime); // running pump

      digitalWrite(PhMinusPump, LOW); // cutting power to pump
      Serial.println("Dosingpump PH- OFF  ");
      printToLCD(1, 1, "Dosingpump PH- OFF");
    }

    delay(iterationTime); // wait before starting next loop iteration
  }
  else
  {
    // skriv på skärmen att vi är i underhållsläge ********************************************************************************************************************************
    if (cleanPhMinus)
    {
      cleaningPhMinus();
    }
    if (cleanPhPlus)
    {
      cleaningPhPlus();
    }
    if (cleanNutrA)
    {
      cleaningNutrA();
    }
    if (cleanNutrB)
    {
      cleaningNutrB();
    }
  }
}

//______ThingSpeak channel update function___________
//void updateTS(){
//String cmd = "AT+CIPSTART=\"TCP\",\""; // A serial command to instruct the WiFi chip
// cmd += IP; //Adding the string containing the IP for ThingSpeak
// cmd += "\",80"; // The port to communicate with ThingSpeak through
// Serial.println(cmd); //Establishing connection with ThingSpeak
// delay(2000); // time delay

