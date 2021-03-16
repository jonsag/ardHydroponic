# ardHydroponic

An Arduino Mega managing a hydroponic plant bed.

## Libraries

Don't use the LiquidCrystal_I2C library from Arduino IDE's library manager.  

Instead use the one from [https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library).  

Install TDS library from [https://github.com/DFRobot/GravityTDS](https://github.com/DFRobot/GravityTDS).  

## Misc

### Pettson's setup

EC/TDS sensor:  
Manufacturer: Qiter  
ASIN: B08RJ5F7QP  
Manufacturers reference: Qiterw75r30cnsb  
[https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244](https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244)  

pH sensor:  
Manufacturer: VBESTLIFE  
ASIN : B081QK9TX2  
Manufacturers reference : VBESTLIFE29748130zt  
[https://wiki.dfrobot.com/Gravity__Analog_pH_Sensor_Meter_Kit_V2_SKU_SEN0161-V2](https://wiki.dfrobot.com/Gravity__Analog_pH_Sensor_Meter_Kit_V2_SKU_SEN0161-V2)  

Available calibration fluids:  
pH: 4.00 and 7.00  
EC: 200 usiemens/cm  

### cu

Get serial output  

>$ cu -l /dev/ttyUSB0 -s 9600

Exit with ~. (tilde dot)  
