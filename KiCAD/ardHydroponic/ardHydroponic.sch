EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L My_Arduino:Arduino_Mega2560 XA1
U 1 1 6045E64B
P 5800 3650
F 0 "XA1" H 5800 1269 60  0000 C CNN
F 1 "Arduino_Mega2560" H 5800 1163 60  0000 C CNN
F 2 "My_Arduino:Arduino_Mega2560_Shield_large" H 6500 6400 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 6500 6400 60  0001 C CNN
	1    5800 3650
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:3-pin_IRF5320_MOSFET_module_header J1
U 1 1 60463EB6
P 9500 1850
F 0 "J1" H 9703 1855 50  0000 L CNN
F 1 "3-pin_IRF5320_MOSFET_module_header" H 9500 1650 50  0001 C CNN
F 2 "My_Headers:3-pin_IRF5320_MOSFET_module_header_large" H 9500 1550 50  0001 C CNN
F 3 "~" H 9500 1850 50  0001 C CNN
	1    9500 1850
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:3-pin_IRF5320_MOSFET_module_header J2
U 1 1 604642B1
P 9500 2550
F 0 "J2" H 9703 2555 50  0000 L CNN
F 1 "3-pin_IRF5320_MOSFET_module_header" H 9500 2350 50  0001 C CNN
F 2 "My_Headers:3-pin_IRF5320_MOSFET_module_header_large" H 9500 2250 50  0001 C CNN
F 3 "~" H 9500 2550 50  0001 C CNN
	1    9500 2550
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:3-pin_IRF5320_MOSFET_module_header J3
U 1 1 604646F1
P 9550 3500
F 0 "J3" H 9753 3505 50  0000 L CNN
F 1 "3-pin_IRF5320_MOSFET_module_header" H 9550 3300 50  0001 C CNN
F 2 "My_Headers:3-pin_IRF5320_MOSFET_module_header_large" H 9550 3200 50  0001 C CNN
F 3 "~" H 9550 3500 50  0001 C CNN
	1    9550 3500
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:3-pin_IRF5320_MOSFET_module_header J4
U 1 1 60464B76
P 9550 4300
F 0 "J4" H 9753 4305 50  0000 L CNN
F 1 "3-pin_IRF5320_MOSFET_module_header" H 9550 4100 50  0001 C CNN
F 2 "My_Headers:3-pin_IRF5320_MOSFET_module_header_large" H 9550 4000 50  0001 C CNN
F 3 "~" H 9550 4300 50  0001 C CNN
	1    9550 4300
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U1
U 1 1 60465402
P 9450 5350
F 0 "U1" H 9220 5396 50  0000 R CNN
F 1 "DS18B20" H 9220 5305 50  0000 R CNN
F 2 "My_Headers:3_pin_Dallas_1-wire_header_larger_pads" H 8450 5100 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 9300 5600 50  0001 C CNN
	1    9450 5350
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:4-pin_I2C_LCD_header J?
U 1 1 604681B1
P 4650 6900
F 0 "J?" H 4878 6896 50  0000 L CNN
F 1 "4-pin_I2C_LCD_header" H 4878 6805 50  0000 L CNN
F 2 "" H 4850 6500 50  0001 C CNN
F 3 "~" H 4650 6900 50  0001 C CNN
	1    4650 6900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
