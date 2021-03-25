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

float readpHValue()
{
  Serial.println("Reading pH value...");

  for (int i = 0; i < 10; i++)
  {                                   // get 10 sample value from the sensor for smooth the value
    buf[i] = analogRead(pHSensorPin); // read pH probe
    delay(10);                        // 10 ms delay
  }
  for (int i = 0; i < 9; i++)
  { // sort the 10 analog readings from small to large
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }

  avgValue = 0; // temporary value for the pH readings

  for (int i = 2; i < 8; i++)
  { // take value of the 6 center samples
    avgValue += buf[i];
  }

  avgValue = avgValue / 6;                  // take average value of the 6 center samples
  phValue = (avgValue * 5.0) / 1024;        // convert the analog readings into volt
  phValue = 3.157895 * phValue + 0.9152632; // convert the millivolt into pH value. Floats are coefficients from sensor calibration

  return phValue;
}

/*
float readECLevel()
{
  Serial.println("Reading EC value...");

  ECRaw = analogRead(ECPin);
  ECRaw = analogRead(ECPin);  // first reading will be inconclusive due to low charge in probe
  digitalWrite(ECPower, LOW); // setting the power pin for EC sensor to low

  // convert voltage to EC
  Vdrop = (Vin * ECRaw) / 1024.0;    // the voltage drop measured
  Rc = (Vdrop * R1) / (Vin - Vdrop); // the resistance of the water solvent
  Rc = Rc - Ra;                      // accounting for Digital Pin Resistance
  EC = 1000 / (Rc * K);              // the calculate EC value

  EC25 = EC / (1 + TemperatureCoef * (temperatureSum - 25.0)); // compensating For the temperature in the water solvent//

  return EC25;
}
*/

float readTDSValue(float tmpKValue, float tmpTdsFactor)
{
  Serial.println("Reading TDS value...");
#ifdef myTds
  voltage = analogRead(ECSensorPin) / adcRange * aref;
  //ecValue = (133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * vars[10];
  ecValue25 =((133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * tmpKValue) / (1.0 + 0.02 * (temperatureSum - 25.0)); //temperature compensation
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
#else
  gravityTds.setTemperature(temperatureSum); // grab the temperature from sensor and execute temperature compensation
  gravityTds.update();                       // calculation done here from gravity library
  TDSValue = gravityTds.getTdsValue();       // then get the TDS value
#endif

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
  phValue = readpHValue();

  Serial.print("pH: ");
  Serial.println(phValue);

  if (phValue != oldpHValue)
  {
    printpHValue();
    oldpHValue = phValue;
  }

  if (phValue < vars[7])
  { // if the pH value to low
    startpHPlus();
    pHPlusStartMillis = currentMillis;
  }
  else if (phValue > vars[8])
  { // if the pH is too high
    startpHMinus();
    pHMinusStartMillis = currentMillis;
  }

  Serial.println();

  /**********
  * Read EC/TDS level
  **********/
  /*
  EC25 = readECLevel();

  if (EC25 < ECLow)
  { // EC level too low
    startNutrA();
    startNutrB();
    nutrAStartMillis = currentMillis;
  }

  Serial.print("EC: ");
  Serial.println(EC25);
  
  if (EC25 != oldEC25)
  {
    printECValue();
    oldEC25 = EC25;
  }
  */

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
    nutrAStartMillis = currentMillis;
  }

  Serial.println();
}

void settingsCheckIfRead() {
    if (varNumber == 10 || varNumber == 11)
  { // setting variables connected to TDS reading
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
}