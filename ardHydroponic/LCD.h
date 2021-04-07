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
    break;
  case 4:
    if (debug)
      Serial.println("Settings");
    printToLCD(6, 0, "Settings      ");
    break;
  case 5:
    if (debug)
      Serial.println("Serial cmd");
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

/*
void printECValue()
{
  if (debug) Serial.println("LCD -> Printing EC value");

  dtostrf(EC25, 2, 2, dtostrfBuffer);
  printToLCD(4, 3, dtostrfBuffer);
}
*/

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

  /*
  printToLCD(0, 3, "EC:");
  printECValue();
  */

  printToLCD(0, 3, "TDS:");
  printTDSValue();
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

  printToLCD(0, 2, String(outputNumber));
  printToLCD(0, 3, outputNames[outputNumber]);
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
#ifdef esp01
    Serial.println("Communicate with ESP module");
    Serial.println("----------");
    Serial.println("Test AT startup: AT");
    Serial.println("Restart module: AT+RST");
    Serial.println("View firmware info: AT+GMR");
    Serial.println("Check WiFi mode: AT+CWMODE=?");
    Serial.println("Print SSID of connected access point: AT+CWJAP?");
    Serial.println("List available access points: AT+CWLAP");
    Serial.println("Disconnect from access point: AT+CWQAP");
    Serial.println("Set WiFi mode to station: AT+CWMODE=1");
    Serial.print("Connect to your access point: ");
    Serial.print("AT+CWJAP=\""); // construct the connect command
    Serial.print(SSID);
    Serial.print("\",\"");
    Serial.print(PASS);
    Serial.println("\"");
    Serial.println("Check IP: AT+CIFSR");
    Serial.println("----------");
    Serial.println();
    printToLCD(0, 1, "Communicate with ESP");
    printToLCD(0, 2, "Use serial monitor  ");
#endif
    break;
  case 1:
    Serial.println("Clear EEPROM");
    printToLCD(0, 1, "Clear EEPROM        ");
    printToLCD(0, 2, "                    ");
    break;
  case 2:
    Serial.println("Reset ESP module");
    printToLCD(0, 1, "Reset ESP module    ");
    printToLCD(0, 2, "                    ");
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

  /*
  int strLen = message.length() + 1;      // length (with one extra character for the null terminator)
  char charArray[strLen];                 // prepare the character array (the buffer)
  message.toCharArray(charArray, strLen); // copy it over
*/

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