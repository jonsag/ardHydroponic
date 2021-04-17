float readWaterTemp()
{
  if (debug)
    Serial.println("Reading water temp...");

  if (!ds.search(addr))
  { // no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  ds.reset();        // reset the 1-wire bus
  ds.select(addr);   // selecting the address of the device to operate
  ds.write(0x44, 1); // write a byte, and leave power applied to the 1 wire bus.
  //byte present = ds.reset();
  ds.reset();
  ds.select(addr); // selecting the address of the device to operate
  ds.write(0xBE);  // write to the temperature sensors RAM at this address

  for (int i = 0; i < 9; i++)
  {                      // we need 9 bytes
    data[i] = ds.read(); // Reading the nine bytes stored in the temperature sensors RAM
  }

  ds.reset_search(); // resetting the OneWire device search

  byte MSB = data[1];                  // storing the temp reading
  byte LSB = data[0];                  // storing the temp reading
  float tempRead = ((MSB << 8) | LSB); // using two's compliment
  temperatureSum = tempRead / 16;      // converting from hex

  return temperatureSum;
}

int getAvgValue(int sensorPin)
{
  for (i = 0; i < noOfReadings; i++)
  {                                 // get 10 sample value from the sensor for smooth the value
    buf[i] = analogRead(sensorPin); // read pH probe
    delay(millisBetweenReadings);   // delay
  }

  if (debug)
    Serial.println("Readings: ");
  for (i = 0; i < noOfReadings; i++)
  {
    if (debug)
      Serial.println(buf[i]);
  }
  if (debug)
    Serial.println();

  for (i = 0; i < noOfReadings; i++)
  { // sort the analog readings from small to large
    for (j = i + 1; j < noOfReadings; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  if (debug)
    Serial.println("Sorted readings: ");
  for (i = 0; i < noOfReadings; i++)
  {
    if (debug)
      Serial.println(buf[i]);
  }
  if (debug)
    Serial.println();

  avgValue = 0; // temporary value for the pH readings

  for (int i = noOfReadings / 5; i < noOfReadings - noOfReadings / 5; i++)
  { // take value of the noOfPHReadings - 2 center samples
    avgValue += buf[i];
  }

  if (debug)
    Serial.println("Added values: ");
  if (debug)
    Serial.println(avgValue);
  if (debug)
    Serial.println();

  avgValue = avgValue / (noOfReadings - noOfReadings / 5 * 2);

  if (debug)
    Serial.println("Average value: ");
  if (debug)
    Serial.println(avgValue);
  if (debug)
    Serial.println();

  return avgValue;
}

float readpHValue(float neutralPH, float acidPH, float neutralVoltage, float acidVoltage, float voltageOffset)
{
  if (debug)
    Serial.println("Reading pH value...");

  pHVoltage = getAvgValue(pHSensorPin) / adcRange * aref * 1000;

  slope = (neutralPH - acidPH) / ((neutralVoltage - voltageOffset) / 3.0 - (acidVoltage - voltageOffset) / 3.0);
  //slope = (7.0     - 4.0   ) / ((this->_neutralVoltage - 1500.0) / 3.0 - (this->_acidVoltage - 1500.0) / 3.0);

  intercept = neutralPH - slope * (neutralVoltage - voltageOffset) / 3.0;
  //intercept = 7.0     - slope * (this->_neutralVoltage - 1500.0) / 3.0;

  pHValue = slope * (pHVoltage - voltageOffset) / 3.0 + intercept; //y = k*x + b
  //pHValue = slope * (voltage - 1500.0       ) / 3.0 + intercept;

  if (debug)
    Serial.print("Neutral pH: ");
  if (debug)
    Serial.println(neutralPH);
  if (debug)
    Serial.print("Acid pH: ");
  if (debug)
    Serial.println(acidPH);
  if (debug)
    Serial.print("Neutral voltage: ");
  if (debug)
    Serial.println(neutralVoltage);
  if (debug)
    Serial.print("Acid voltage: ");
  if (debug)
    Serial.println(acidVoltage);
  if (debug)
    Serial.print("Voltage offset: ");
  if (debug)
    Serial.println(voltageOffset);
  if (debug)
    Serial.print("adc range: ");
  if (debug)
    Serial.println(adcRange);
  if (debug)
    Serial.print("aref: ");
  if (debug)
    Serial.println(aref);
  if (debug)
    Serial.print("pH voltage: ");
  if (debug)
    Serial.println(pHVoltage);
  if (debug)
    Serial.print("slope: ");
  if (debug)
    Serial.println(slope);
  if (debug)
    Serial.print("intercept: ");
  if (debug)
    Serial.println(intercept);
  if (debug)
    Serial.print("pH value: ");
  if (debug)
    Serial.println(pHValue);

  return pHValue;
}

float readTDSValue(float tmpKValue, float tmpTdsFactor)
{
  if (debug)
    Serial.println("Reading TDS value...");

  voltage = getAvgValue(ECSensorPin) / adcRange * aref;
  //ecValue = (133.42 *  voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * vars[10];
  ecValue25 = ((133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * tmpKValue) / (1.0 + 0.02 * (temperatureSum - 25.0)); //temperature compensation
  TDSValue = ecValue25 * tmpTdsFactor;

  if (debug)
    Serial.print("adc range: ");
  if (debug)
    Serial.println(adcRange);
  if (debug)
    Serial.print("aref: ");
  if (debug)
    Serial.println(aref);
  if (debug)
    Serial.print("Voltage: ");
  if (debug)
    Serial.println(voltage);
  if (debug)
    Serial.print("ec25: ");
  if (debug)
    Serial.println(ecValue25);
  if (debug)
    Serial.print("TDS value: ");
  if (debug)
    Serial.println(TDSValue);

  return TDSValue;
}

void readSensors()
{
  temperatureSum = readWaterTemp();

  if (debug)
    Serial.print("Tank temp: ");
  if (debug)
    Serial.println(temperatureSum);

  if (temperatureSum != oldTemperatureSum)
  {
    printTemp();
    oldTemperatureSum = temperatureSum;
  }
  if (debug)
    Serial.println();

  /**********
  * Read PH value
  **********/
  pHValue = readpHValue(vars[12], vars[13], vars[14], vars[15], vars[16]);

  if (debug)
    Serial.print("pH: ");
  if (debug)
    Serial.println(pHValue);

  if (pHValue != oldpHValue)
  {
    printPHValue();
    oldpHValue = pHValue;
  }

  if (pHValue < vars[7])
  { // if the pH value to low
    startpHPlus();
    printToLCD(12, 2, "Low ");
    pHPlusStartMillis = currentMillis;
  }
  else if (pHValue > vars[8])
  { // if the pH is too high
    startpHMinus();
    printToLCD(12, 2, "High");
    pHMinusStartMillis = currentMillis;
  }
  else
  {
    printToLCD(12, 2, "    ");
  }

  if (debug)
    Serial.println();

  /**********
  * Read EC/TDS level
  **********/
  TDSValue = readTDSValue(vars[10], vars[11]);

  if (debug)
    Serial.print("TDS: ");
  if (debug)
    Serial.print(TDSValue, 0);
  if (debug)
    Serial.println(" ppm");

  if (TDSValue != oldTDSValue)
  {
    printTDSValue();
    oldTDSValue = TDSValue;
  }

  if (TDSValue < vars[9])
  { // EC level too low
    startNutrA();
    startNutrB();
    printToLCD(12, 3, "Low");
    nutrAStartMillis = currentMillis;
  }
  else
  {
    printToLCD(12, 3, "   ");
  }

  if (info == 1)
  {
    Serial.print("Temp:");
    Serial.print(temperatureSum);
    Serial.print(",pH:");
    Serial.print(pHValue);
    Serial.print(",TDS:");
    Serial.println(TDSValue);
  }
  else if (info == 2)
  {
    Serial.print("Temp:");
    Serial.println(temperatureSum);
    Serial.print("pH:");
    Serial.println(pHValue);
    Serial.print("TDS:");
    Serial.println(TDSValue);
  }

  newData = 1;

  if (debug)
    Serial.println();
}

void settingsCheckIfRead()
{
  if (varNumber == 10 || varNumber == 11)
  { // setting variables connected to TDS reading

    temperatureSum = readWaterTemp();

    printToLCD(0, 3, "TDS: ");

    switch (varNumber)
    {
    case 10:
      TDSValue = readTDSValue(tempValue, vars[11]);
      break;
    case 11:
      TDSValue = readTDSValue(vars[10], tempValue);
      break;
    }
    printTDSValue();
  }
  else
  {
    printToLCD(0, 3, "          ");
  }

  if (varNumber >= 12 && varNumber <= 16)
  { // setting variables connected to pH reading

    printToLCD(0, 2, "pH: ");

    switch (varNumber)
    {
    case 12:
      pHValue = readpHValue(tempValue, vars[13], vars[14], vars[15], vars[16]);
      break;
    case 13:
      pHValue = readpHValue(vars[12], tempValue, vars[14], vars[15], vars[16]);
      break;
    case 14:
      tempValue = analogRead(pHSensorPin) / adcRange * aref * 1000;
      pHValue = readpHValue(vars[12], vars[13], tempValue, vars[15], vars[16]);
      break;
    case 15:
      tempValue = analogRead(pHSensorPin) / adcRange * aref * 1000;
      pHValue = readpHValue(vars[12], vars[13], vars[14], tempValue, vars[16]);
      break;
    case 16:
      pHValue = readpHValue(vars[12], vars[13], vars[14], vars[15], tempValue);
      break;
    }
    printPHValue();
  }
  else
  {
    printToLCD(0, 2, "          ");
  }
}