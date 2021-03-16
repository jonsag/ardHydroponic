void clearLCD()
{
#ifdef LCD
  lcd.clear();
#endif
}

void printToLCD(int col, int row, String text)
{
#ifdef LCD
  lcd.setCursor(col, row);
  lcd.print(text);
#endif
}

void printMode()
{
  Serial.print("LCD -> Printing mode: ");
  switch (mode)
  {
  case 0:
    Serial.println("Running...");
    printToLCD(6, 0, "Running...  ");
    break;
  case 1:
    Serial.println("Reading...");
    printToLCD(6, 0, "Reading...  ");
    break;
  case 2:
    Serial.println("Pumping...");
    printToLCD(6, 0, "Pumping...  ");
    break;
  case 3:
    Serial.println("Maintenance");
    printToLCD(6, 0, "Maintenance ");
    break;
  case 4:
    Serial.println("Settings");
    printToLCD(6, 0, "Settings    ");
    break;
  }
}

void printTemp()
{
  Serial.println("LCD -> Printing temp");

  dtostrf(temperatureSum, 1, 1, dtostrfBuffer);
  printToLCD(6, 1, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(6 + strLength, 1, String((char)223));
  printToLCD(6 + strLength + 1, 1, "C");
}

void printpHValue()
{
  Serial.println("LCD -> Printing pH value");

  dtostrf(phValue, 2, 2, dtostrfBuffer);
  printToLCD(4, 2, dtostrfBuffer);
}

/*
void printECValue()
{
  Serial.println("LCD -> Printing EC value");

  dtostrf(EC25, 2, 2, dtostrfBuffer);
  printToLCD(4, 3, dtostrfBuffer);
}
*/

void printTdsValue() {
  Serial.println("LCD -> Printing tds value");

  dtostrf(tdsValue, 2, 2, dtostrfBuffer);
  printToLCD(5, 3, dtostrfBuffer);
}

void printNormal()
{
  Serial.println("LCD -> Normal mode");

  //lcd.clear();

  printToLCD(0, 0, "Mode:");
  printMode();

  printToLCD(0, 1, "Temp:");
  printTemp();

  printToLCD(0, 2, "pH:");
  printpHValue();

/*
  printToLCD(0, 3, "EC:");
  printECValue();
  */

 printToLCD(0, 3, "tds:");
  printTdsValue();
}

void printSelectedPump()
{
  Serial.print(pumpNames[pumpNumber]);
  Serial.println(" selected");
  printToLCD(0, 2, "Pump");
  printToLCD(5, 2, String(pumpNumber));
  printToLCD(0, 3, pumpNames[pumpNumber]);
}

void printMaintenance()
{
  clearLCD();
  printToLCD(0, 0, "Mode:");
  printMode();
  printSelectedPump();
}

void printSettings()
{
  clearLCD();
  printToLCD(0, 0, "Mode:");
  printMode();
}
