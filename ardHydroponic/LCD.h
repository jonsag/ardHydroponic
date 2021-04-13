
void clearLCD()
{
  lcd.clear();
}

void printToLCD(int col, int row, String text)
{
  lcd.setCursor(col, row);
  lcd.print(text);
}

void printMode()
{
  if (debug)
    Serial.print("LCD -> Printing mode: ");
  switch (mode)
  {
  case 0:
    if (debug)
      Serial.println("Running...");
    printToLCD(6, 0, "Running...    ");
    break;
  case 1:
    if (debug)
      Serial.println("Reading...");
    printToLCD(6, 0, "Reading...    ");
    break;
  case 2:
    if (debug)
      Serial.println("Uploading...");
    printToLCD(6, 0, "Uploading...  ");
    break;
  case 3:
    if (debug)
      Serial.println("Maintenance");
    printToLCD(6, 0, "Maintenance   ");
    printToLCD(0, 1, "Start/Stop devices  ");
    break;
  case 4:
    if (debug)
      Serial.println("Settings");
    printToLCD(6, 0, "Settings      ");
    break;
  case 5:
    if (debug)
      Serial.println("Special");
    printToLCD(6, 0, "Special       ");
    break;
  }
  if (debug)
    Serial.println();
}

void printTemp()
{
  if (debug)
    Serial.println("LCD -> Printing temp");

  dtostrf(temperatureSum, 1, 1, dtostrfBuffer);
  printToLCD(6, 1, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(6 + strLength, 1, String((char)223));
  printToLCD(6 + strLength + 1, 1, "C");
}

void printPHValue()
{
  if (debug)
    Serial.println("LCD -> Printing pH value");

  dtostrf(pHValue, 2, 2, dtostrfBuffer);
  printToLCD(4, 2, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(4 + strLength, 2, "   ");
}

void printTDSValue()
{
  if (debug)
    Serial.println("LCD -> Printing TDS value");

  dtostrf(TDSValue, 2, 0, dtostrfBuffer);
  printToLCD(5, 3, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(5 + strLength, 3, "   ");
}

void printNormal()
{
  if (debug)
    Serial.println("LCD -> Normal mode");

  //lcd.clear();

  printToLCD(0, 0, "Mode:");
  printMode();

  printToLCD(0, 1, "Temp:");
  printTemp();

  printToLCD(0, 2, "pH:");
  printPHValue();

  printToLCD(0, 3, "TDS:");
  printTDSValue();
}

void maintPrintOutputStatus()
{
  boolean status = 0;

  switch (outputNumber)
  {
  case 0:
    if (digitalRead(pHPlusPump))
    {
      status = 1;
    }
    break;
  case 1:
    if (digitalRead(pHMinusPump))
    {
      status = 1;
    }
    break;
  case 2:
    if (digitalRead(nutrAPump))
    {
      status = 1;
    }
    break;
  case 3:
    if (digitalRead(nutrBPump))
    {
      status = 1;
    }
    break;
  case 4:
    if (digitalRead(stirrer))
    {
      status = 1;
    }
    break;
  }

  if (status)
  {
    printToLCD(0, 3, "Running");
  }
  else
  {
    printToLCD(0, 3, "Stopped");
  }
}

void printSelectedOutput()
{
  if (debug)
    Serial.println("LCD -> Printing selected output");
  if (debug)
    Serial.print(outputNumber);
  if (debug)
    Serial.print(": ");
  if (debug)
    Serial.print(outputNames[outputNumber]);
  if (debug)
    Serial.println(" selected");

  printToLCD(0, 2, outputNames[outputNumber]);
  maintPrintOutputStatus();
}

void printSelectedVar()
{
  if (debug)
    Serial.println("LCD -> Printing selected variable");
  if (debug)
    Serial.print(varNumber);
  if (debug)
    Serial.print(": ");
  if (debug)
    Serial.print(varNames[varNumber]);
  if (debug)
    Serial.print("\tOld value: ");
  if (debug)
    Serial.print(vars[varNumber]);
  if (debug)
    Serial.print("\t+-: ");
  if (debug)
    Serial.print(incs[varNumber]);
  if (debug)
    Serial.print("\tNew value: ");
  if (debug)
    Serial.print(tempValue);
  if (debug)
    Serial.println();

  printToLCD(0, 1, varNames[varNumber]);

  if (varNumber <= 6 || varNumber == 9)
  {
    dtostrf(vars[varNumber], 2, 0, dtostrfBuffer);
  }
  else
  {
    dtostrf(vars[varNumber], 2, 2, dtostrfBuffer);
  }
  printToLCD(12, 2, dtostrfBuffer);
  strLength = strlen(dtostrfBuffer);
  for (i = 12 + strLength; i < 20; i++)
  {
    printToLCD(i, 2, " ");
  }

  if (varNumber <= 6 || varNumber == 9)
  {
    dtostrf(tempValue, 2, 0, dtostrfBuffer);
  }
  else
  {
    dtostrf(tempValue, 2, 2, dtostrfBuffer);
  }
  printToLCD(12, 3, dtostrfBuffer);
  strLength = strlen(dtostrfBuffer);
  for (i = 12 + strLength; i < 20; i++)
  {
    printToLCD(i, 3, " ");
  }
}

void printMaintenance()
{
  clearLCD();
  printToLCD(0, 0, "Mode:");
  printMode();
  printSelectedOutput();
}

void printSettings()
{
  clearLCD();
  printToLCD(0, 0, "Mode:");
  printMode();
}

void printSpecialMaintMode()
{
  switch (specialMaintMode)
  {
  case 0:
    Serial.println("Communicate with ESP module");
    Serial.println("----------");
    Serial.println("Send test data: Temp:12.34,pH:5.67,TDS:890.12");
    Serial.println("Print IP: i");
    Serial.println("Print MAC: m");
    Serial.println("Toggle debug: d");
    Serial.println("----------");
    while (Serial1.available())
    {
      Serial1.read(); // clears buffer
    }
    printToLCD(0, 1, "Communicate with ESP");
    printToLCD(0, 2, "Use serial monitor  ");
    break;
  case 1:
    if (debug)
      Serial.println("Clear EEPROM");
    printToLCD(0, 1, "Clear EEPROM        ");
    printToLCD(0, 2, "                    ");
    break;
  case 2:
    if (debug)
      Serial.println("Reset ESP module");
    printToLCD(0, 1, "Reset ESP module    ");
    printToLCD(0, 2, "                    ");
    break;
  case 3:
    if (debug)
      Serial.println("Reset system");
    printToLCD(0, 1, "Reset system        ");
    printToLCD(0, 2, "                    ");
    break;
  case 4:
    if (debug)
      Serial.println("Toggle serial debug");
    printToLCD(0, 1, "Toggle serial debug ");
    if (debug)
    {
      printToLCD(0, 2, "Debug enabled       ");
    }
    else
    {
      printToLCD(0, 2, "Debug disabled      ");
    }
    break;
  }
}
void printSpecialMaint()
{
  clearLCD();
  printToLCD(0, 0, "Mode:");
  printMode();
  printSpecialMaintMode();
}

void bootScreen(String message)
{
  clearLCD();

  switch (bootScreenLineNo)
  {
  case 0:
    bootScreenLine0 = message;
    bootScreenLine1 = "";
    bootScreenLine2 = "";
    bootScreenLine3 = "";
    break;
  case 1:
    bootScreenLine1 = message;
    break;
  case 2:
    bootScreenLine2 = message;
    break;
  case 3:
    bootScreenLine3 = message;
    break;
  default:
    bootScreenLine0 = bootScreenLine1;
    bootScreenLine1 = bootScreenLine2;
    bootScreenLine2 = bootScreenLine3;
    bootScreenLine3 = message;
    bootScreenLineNo = 3;
  }

  printToLCD(0, 0, bootScreenLine0);
  printToLCD(0, 1, bootScreenLine1);
  printToLCD(0, 2, bootScreenLine2);
  printToLCD(0, 3, bootScreenLine3);

  if (debug)
    Serial.println();

  bootScreenLineNo++;
}