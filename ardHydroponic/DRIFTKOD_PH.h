/*
 # This sample code is used to test the pH meter V1.0.
 # Editor : YouYou
 # Ver    : 1.0
 # Product: analog pH meter
 # SKU    : SEN0161
*/
#define sensorPin A0 //pH meter Analog output to Arduino Analog Input 0
#define offset 0.00  //Ställbart värde för avdrift/kompensation
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define arrayLength 40 //times of collection

int pHArray[arrayLength]; //Store the average value of the sensor feedback
int pHArrayIndex = 0;

void setup(void)
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("pH meter experiment!"); //Test the serial monitor
}

void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue;
  static float voltage;

  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(sensorPin);
    if (pHArrayIndex == arrayLength)
    {
      pHArrayIndex = 0;
    }
    voltage = averageArray(pHArray, arrayLength) * 5.0 / 1024;
    pHValue = 3.5 * voltage + offset;
    samplingTime = millis();
  }

  if (millis() - printTime > printInterval) //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    Serial.print("Voltage:");
    Serial.print(voltage, 2);
    Serial.print("    pH value: ");
    Serial.println(pHValue, 2);
    digitalWrite(LED, digitalRead(LED) ^ 1);
    printTime = millis();
  }
}

double averageArray(int *arr, int number)
{
  int i;
  int max, min;
  double avg;
  long amount = 0;

  if (number <= 0)
  {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }

  if (number < 5)
  { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++)
    {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  }
  else
  {
    if (arr[0] < arr[1])
    {
      min = arr[0];
      max = arr[1];
    }
    else
    {
      min = arr[1];
      max = arr[0];
    }

    for (i = 2; i < number; i++)
    {
      if (arr[i] < min)
      {
        amount += min; //arr<min
        min = arr[i];
      }
      else
      {
        if (arr[i] > max)
        {
          amount += max; //arr>max
          max = arr[i];
        }
        else
        {
          amount += arr[i]; //min<=arr<=max
        }
      } //if
    }   //for
    avg = (double)amount / (number - 2);
  } //if
  return avg;
}