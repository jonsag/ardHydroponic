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
  Serial.println();
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

void printPHValue()
{
  Serial.println("LCD -> Printing pH value");

  dtostrf(pHValue, 2, 2, dtostrfBuffer);
  printToLCD(4, 2, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(4 + strLength, 2, "   ");
}

/*
void printECValue()
{
  Serial.println("LCD -> Printing EC value");

  dtostrf(EC25, 2, 2, dtostrfBuffer);
  printToLCD(4, 3, dtostrfBuffer);
}
*/

void printTDSValue()
{
  Serial.println("LCD -> Printing TDS value");

  dtostrf(TDSValue, 2, 0, dtostrfBuffer);
  printToLCD(5, 3, dtostrfBuffer);

  strLength = strlen(dtostrfBuffer);
  printToLCD(5 + strLength, 3, "   ");
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
  Serial.println("LCD -> Printing selected output");
  Serial.print(outputNumber);
  Serial.print(": ");
  Serial.print(outputNames[outputNumber]);
  Serial.println(" selected");

  printToLCD(0, 2, String(outputNumber));
  printToLCD(0, 3, outputNames[outputNumber]);
}

void printSelectedVar()
{
  Serial.println("LCD -> Printing selected variable");
  Serial.print(varNumber);
  Serial.print(": ");
  Serial.print(varNames[varNumber]);
  Serial.print("\tOld value: ");
  Serial.print(vars[varNumber]);
  Serial.print("\t+-: ");
  Serial.print(incs[varNumber]);
  Serial.print("\tNew value: ");
  Serial.print(tempValue);
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

  Serial.println();

  bootScreenLineNo++;
}