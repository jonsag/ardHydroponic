void printToLCD(int col, int row, String text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
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

  dtostrf(TemperatureSum, 1, 1, dtostrfBuffer);
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

void printECValue()
{
  Serial.println("LCD -> Printing EC value");

  dtostrf(EC25, 2, 2, dtostrfBuffer);
  printToLCD(4, 3, dtostrfBuffer);
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

  printToLCD(0, 3, "EC:");
  printECValue();
}

void printSelectedPump() {
  printToLCD(0, 2, pumpNames[pumpNumber]);
}

void printMaintenance()
{
  lcd.clear();
  printToLCD(0, 0, "Mode:");
  printMode();
  printSelectedPump();
}

void printSettings()
{
  lcd.clear();
  printToLCD(0, 0, "Mode:");
  printMode();
}
