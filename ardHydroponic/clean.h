void flushpHMinus()
{
  Serial.print("Flushing PH- hose");
  printToLCD(0, 0, "Flushing hose for   ");
  printToLCD(0, 1, "PH-                 ");
  printToLCD(0, 2, "for ");
  printToLCD(4, 2, String(cleanTime / 1000));
  printToLCD(6, 2, " seconds     ");

  digitalWrite(pHPlusPump, HIGH);
  delay(cleanTime);
  digitalWrite(pHPlusPump, LOW);

  Serial.println("Cleaning finished");
  printToLCD(0, 0, "Cleaning          ");
  printToLCD(0, 1, "finished          ");
  printToLCD(0, 2, "                  ");
}

void flushpHPlus()
{
  Serial.print("Flushing PH+ hose");
  printToLCD(0, 0, "Flushing hose for   ");
  printToLCD(0, 1, "PH+                 ");
  printToLCD(0, 2, "for ");
  printToLCD(4, 2, String(cleanTime / 1000));
  printToLCD(6, 2, " seconds     ");

  digitalWrite(pHMinusPump, HIGH);
  delay(cleanTime);
  digitalWrite(pHMinusPump, LOW);

  Serial.println("Cleaning finished");
  printToLCD(0, 0, "Cleaning          ");
  printToLCD(0, 1, "finished          ");
  printToLCD(0, 2, "                  ");
}

void flushNutrA()
{
  Serial.print("Flushing nutrient A hose");
  printToLCD(0, 0, "Flushing hose for   ");
  printToLCD(0, 1, "nutrient A          ");
  printToLCD(0, 2, "for ");
  printToLCD(4, 2, String(cleanTime / 1000));
  printToLCD(6, 2, " seconds     ");

  digitalWrite(nutrAPump, HIGH);
  delay(cleanTime);
  digitalWrite(nutrAPump, LOW);

  Serial.println("Cleaning finished");
  printToLCD(0, 0, "Cleaning          ");
  printToLCD(0, 1, "finished          ");
  printToLCD(0, 2, "                  ");
}

void flushNutrB()
{
  Serial.print("Flushing nutrient B hose");
  printToLCD(0, 0, "Flushing hose for   ");
  printToLCD(0, 1, "nutrient B          ");
  printToLCD(0, 2, "for ");
  printToLCD(4, 2, String(cleanTime / 1000));
  printToLCD(6, 2, " seconds     ");

  digitalWrite(nutrBPump, HIGH);
  delay(cleanTime);
  digitalWrite(nutrBPump, LOW);

  Serial.println("Cleaning finished");
  printToLCD(0, 0, "Cleaning          ");
  printToLCD(0, 1, "finished          ");
  printToLCD(0, 2, "                  ");
}
