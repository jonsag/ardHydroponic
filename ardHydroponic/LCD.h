void printToLCD(int col, int row, String text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void printMode()
{
  switch (mode)
  {
  case 0:
    printToLCD(6, 0, "Normal       ");
    break;
  case 1:
    printToLCD(6, 0, "Reading...   ");
    break;
  case 2:
    printToLCD(6, 0, "Pumping...   ");
    break;
  case 3:
    printToLCD(6, 0, "Maintenance  ");
    break;
  }
}

void printHeaders()
{
  lcd.clear();
  printToLCD(0, 0, "Mode:");
  printMode();

  printToLCD(0, 1, "Temp:");
  printToLCD(0, 2, "Ph:");
  printToLCD(0, 3, "EC:");
}

void printTemp()
{
  dtostrf(TemperatureSum, 1, 1, dtostrfBuffer);
  printToLCD(6, 1, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(6 + strLength, 1, String((char)223));
  printToLCD(6 + strLength + 1, 1, "C");
}

void printPhValue()
{
  dtostrf(phValue, 1, 1, dtostrfBuffer);
  printToLCD(4, 2, dtostrfBuffer);
}

void printECValue()
{
  dtostrf(EC25, 1, 1, dtostrfBuffer);
  printToLCD(4, 3, dtostrfBuffer);
}

void printMaintenance()
{
lcd.clear();
  printToLCD(0, 0, "Mode:");
  printMode();  
}
