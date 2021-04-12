
int intLength(long value)
{
  int length;
  if (value > 9999999)
    length = 8;
  else if (value > 999999)
    length = 7;
  else if (value > 99999)
    length = 6;
  else if (value > 9999)
    length = 5;
  else if (value > 999)
    length = 4;
  else if (value > 99)
    length = 3;
  else if (value > 9)
    length = 2;
  else
    length = 1;

  return length;
}

void checkMode()
{
  if (mode != oldMode)
  {
    if (oldMode == 3 || oldMode == 4 || oldMode == 5)
    {
clearLCD();
    }
    switch (mode)
    {
    case 0:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Normal mode");
      if (oldMode == 3 || oldMode == 4 || oldMode == 5)
      {
        printNormal();
      }
      else
      {
        printMode();
      }
      break;
    case 1:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Reading mode");
      printMode();
      break;
    case 2:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Uploading mode");
      printMode();
      break;
    case 3:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Maintenance mode");
      printMaintenance();
      break;
    case 4:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Settings mode");
      printSettings();
      break;
    case 5:
      if (debug) Serial.println();
      if (debug) Serial.println("-> Special maintenance mode");
      printSpecialMaint();
      break;
    }
    oldMode = mode;
  }
}

void resetSystem() {
  if (debug) Serial.println("Resetting system...");
  delay(500);
  digitalWrite(resetPin, LOW);
  printToLCD(0, 2, "Reset failed        ");
}

/*
dtostrf(floatvar, StringLengthIncDecimalPoint, numVarsAfterDecimal, charbuf);
where
floatvar	float variable
StringLengthIncDecimalPoint	This is the length of the string that will be created
numVarsAfterDecimal	The number of digits after the deimal point to print
charbuf	the array to store the results

char dtostrfbuffer[5];
dtostrf(temp, 1, 1, dtostrfbuffer)
valLength = valLength + strlen(dtostrfbuffer);
*/