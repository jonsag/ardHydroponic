void cleaningPhMinus()
{
  Serial.println("Spolar slang PH- under 30 sekunder");
  digitalWrite(PhPlusPump, HIGH); // spolar slangen för PH-
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med PH-          ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(cleanTime); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(PhPlusPump, LOW); // stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void cleaningPhPlus()
{
  Serial.println("Spolar slang PH+ under 30 sekunder");
  digitalWrite(PhMinusPump, HIGH); // spolar slangen för PH+
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med PH+          ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(cleanTime); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(PhMinusPump, LOW); // stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void cleaningNutrA()
{
  Serial.println("Spolar slang A under 30 sekunder");
  digitalWrite(nutrAPump, HIGH); // spolar slangen nutrion: A
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med nutrion: A   ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(cleanTime); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(nutrAPump, LOW); // stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}

void cleaningNutrB()
{
  Serial.println("Spolar slang B under 30 sekunder");
  digitalWrite(nutrBPump, HIGH); // spolar slangen nutrion: B
  printToLCD(0, 0, "   Spolar slangen   ");
  printToLCD(0, 1, "   med nutrion: B   ");
  printToLCD(0, 2, "    i 30 sekunder   ");

  delay(cleanTime); // Running pump

  Serial.println("Spolning av slang är klar!");
  digitalWrite(nutrBPump, LOW); // stänger av pumpen
  printToLCD(0, 0, "    Spolning av   ");
  printToLCD(0, 1, "    slang klar!   ");
  printToLCD(0, 2, "                  ");
}
