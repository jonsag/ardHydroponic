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
  TemperatureSum = tempRead / 16;      // converting from hex

  return TemperatureSum;
}

float readpHValue()
{
  Serial.println("Reading pH value...");

  for (int i = 0; i < 10; i++)
  {                             // get 10 sample value from the sensor for smooth the value
    buf[i] = analogRead(pHpin); // read pH probe
    delay(10);                  // 10 ms delay
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

float readECLevel()
{
  Serial.println("Reading EC value...");

  digitalWrite(ECPower, HIGH); // setting the power pin for EC sensor to high
  ECRaw = analogRead(ECPin);
  ECRaw = analogRead(ECPin);  // first reading will be inconclusive due to low charge in probe
  digitalWrite(ECPower, LOW); // setting the power pin for EC sensor to low

  // convert voltage to EC
  Vdrop = (Vin * ECRaw) / 1024.0;    // the voltage drop measured
  Rc = (Vdrop * R1) / (Vin - Vdrop); // the resistance of the water solvent
  Rc = Rc - Ra;                      // accounting for Digital Pin Resistance
  EC = 1000 / (Rc * K);              // the calculate EC value

  EC25 = EC / (1 + TemperatureCoef * (TemperatureSum - 25.0)); // compensating For the temperature in the water solvent//

  return EC25;
}

void readSensors()
{
  TemperatureSum = readWaterTemp();

  Serial.println("TankTemp: " + String(TemperatureSum));
  if (TemperatureSum != oldTemperatureSum)
  {
    printTemp();
  }

  /**********
  * Read PH value
  **********/
  phValue = readpHValue();

  if (phValue < 4.62)
  { // if the pH value to low
    startpHPlus();
    pHPlusStartMillis = currentMillis;
  }
  else if (phValue > 4.63)
  { // if the pH is too high
    startpHMinus();
    pHMinusStartMillis = currentMillis;
  }

  Serial.println("PH: " + String(phValue));

  if (phValue != oldpHValue)
  {
    printpHValue();
  }

  /**********
  * Read EC level
  **********/
  EC25 = readECLevel();

  if (EC25 < 3.0)
  { // EC level too low
    startNutrA();
    startNutrB();
    nutrAStartMillis = currentMillis;
  }

  Serial.println("EC: " + String(EC25));
  if (EC25 != oldEC25)
  {
    printECValue();
  }
}