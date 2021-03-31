float readWaterTemp()
{
  Serial.println("Reading water temp...");

  if (!ds.search(addr))
  { // no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  ds.reset();        // reset the 1-wire bus
  ds.select(addr);   // selecting the address of the device to operate
  ds.write(0x44, 1); // write a byte, and leave power applied to the 1 wire bus.
  byte present = ds.reset();
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

  /*
  Serial.println("Readings: ");
  for (i = 0; i < noOfReadings; i++)
  {
    Serial.println(buf[i]);
  }
  Serial.println();
  */

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

  /*
  Serial.println("Sorted readings: ");
  for (i = 0; i < noOfReadings; i++)
  {
    Serial.println(buf[i]);
  }
  Serial.println();
  */

  avgValue = 0; // temporary value for the pH readings

  for (int i = 2; i < noOfReadings - 2; i++)
  { // take value of the noOfPHReadings - 2 center samples
    avgValue += buf[i];
  }

  /*
  Serial.println("Added values: ");
  Serial.println(avgValue);
  Serial.println();
  */

  avgValue = avgValue / (noOfReadings - 4);

  /*
  Serial.println("Average value: ");
  Serial.println(avgValue);
  Serial.println();
  */

  return avgValue;
}

float readpHValue(float neutralPH, float acidPH, float neutralVoltage, float acidVoltage, float voltageOffset)
{
  Serial.println("Reading pH value...");

  pHVoltage = getAvgValue(pHSensorPin) / adcRange * aref * 1000;

  slope = (neutralPH - acidPH) / ((neutralVoltage - voltageOffset) / 3.0 - (acidVoltage - voltageOffset) / 3.0);
  //slope = (7.0     - 4.0   ) / ((this->_neutralVoltage - 1500.0) / 3.0 - (this->_acidVoltage - 1500.0) / 3.0);

  intercept = neutralPH - slope * (neutralVoltage - voltageOffset) / 3.0;
  //intercept = 7.0     - slope * (this->_neutralVoltage - 1500.0) / 3.0;

  pHValue = slope * (pHVoltage - voltageOffset) / 3.0 + intercept; //y = k*x + b
  //pHValue = slope * (voltage - 1500.0       ) / 3.0 + intercept;

  Serial.print("Neutral pH: ");
  Serial.println(neutralPH);
  Serial.print("Acid pH: ");
  Serial.println(acidPH);
  Serial.print("Neutral voltage: ");
  Serial.println(neutralVoltage);
  Serial.print("Acid voltage: ");
  Serial.println(acidVoltage);
  Serial.print("Voltage offset: ");
  Serial.println(voltageOffset);
  Serial.print("adc range: ");
  Serial.println(adcRange);
  Serial.print("aref: ");
  Serial.println(aref);
  Serial.print("pH voltage: ");
  Serial.println(pHVoltage);
  Serial.print("slope: ");
  Serial.println(slope);
  Serial.print("intercept: ");
  Serial.println(intercept);
  Serial.print("pH value: ");
  Serial.println(pHValue);

  return pHValue;
}

float readTDSValue(float tmpKValue, float tmpTdsFactor)
{
  Serial.println("Reading TDS value...");

  voltage = getAvgValue(ECSensorPin) / adcRange * aref;
  //ecValue = (133.42 *  voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * vars[10];
  ecValue25 = ((133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * tmpKValue) / (1.0 + 0.02 * (temperatureSum - 25.0)); //temperature compensation
  TDSValue = ecValue25 * tmpTdsFactor;

  Serial.print("adc range: ");
  Serial.println(adcRange);
  Serial.print("aref: ");
  Serial.println(aref);
  Serial.print("Voltage: ");
  Serial.println(voltage);
  Serial.print("ec25: ");
  Serial.println(ecValue25);
  Serial.print("TDS value: ");
  Serial.println(TDSValue);

  return TDSValue;
}

void readSensors()
{
  temperatureSum = readWaterTemp();

  Serial.print("Tank temp: ");
  Serial.println(temperatureSum);

  if (temperatureSum != oldTemperatureSum)
  {
    printTemp();
    oldTemperatureSum = temperatureSum;
  }
  Serial.println();

  /**********
  * Read PH value
  **********/
  pHValue = readpHValue(vars[12], vars[13], vars[14], vars[15], vars[16]);

  Serial.print("pH: ");
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

  Serial.println();

  /**********
  * Read EC/TDS level
  **********/
  TDSValue = readTDSValue(vars[10], vars[11]);

  Serial.print("TDS: ");
  Serial.print(TDSValue, 0);
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

#ifdef logging
  Serial.println("Writing to thingSpeak...");
  writeThingSpeak();
#endif

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