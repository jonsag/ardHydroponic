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
P 4200 3350
F 0 "XA1" H 4200 969 60  0000 C CNN
F 1 "Arduino_Mega2560" H 4200 863 60  0000 C CNN
F 2 "My_Arduino:Arduino_Mega2560_Shield__no_ICSP_no_mount-holes_large" H 4900 6100 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 4900 6100 60  0001 C CNN
	1    4200 3350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U1
U 1 1 60465402
P 1050 4750
F 0 "U1" H 820 4796 50  0000 R CNN
F 1 "DS18B20" H 820 4705 50  0000 R CNN
F 2 "My_Parts:3-pole_DS18B20_screw_terminal" H 50  4500 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 900 5000 50  0001 C CNN
	1    1050 4750
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U5
U 1 1 6046FFFD
P 9550 1200
F 0 "U5" H 10278 1171 50  0000 L CNN
F 1 "pH+ pump" H 10278 1080 50  0000 L CNN
F 2 "" H 9725 1425 50  0001 C CNN
F 3 "" H 9725 1425 50  0001 C CNN
	1    9550 1200
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U6
U 1 1 60471911
P 9550 2150
F 0 "U6" H 10278 2121 50  0000 L CNN
F 1 "pH- pump" H 10278 2030 50  0000 L CNN
F 2 "" H 9725 2375 50  0001 C CNN
F 3 "" H 9725 2375 50  0001 C CNN
	1    9550 2150
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U7
U 1 1 60471FF1
P 9550 3100
F 0 "U7" H 10278 3071 50  0000 L CNN
F 1 "nutr A pump" H 10278 2980 50  0000 L CNN
F 2 "" H 9725 3325 50  0001 C CNN
F 3 "" H 9725 3325 50  0001 C CNN
	1    9550 3100
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U8
U 1 1 604749DB
P 9550 4050
F 0 "U8" H 10278 4021 50  0000 L CNN
F 1 "nutr B pump" H 10278 3930 50  0000 L CNN
F 2 "" H 9725 4275 50  0001 C CNN
F 3 "" H 9725 4275 50  0001 C CNN
	1    9550 4050
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:4-pin_I2C_LCD_header J1
U 1 1 60475C3F
P 1200 1900
F 0 "J1" H 1428 1896 50  0000 L CNN
F 1 "LCD display" H 1428 1805 50  0000 L CNN
F 2 "My_Headers:4-pin_I2C_LCD_header_larger" H 1400 1500 50  0001 C CNN
F 3 "~" H 1200 1900 50  0001 C CNN
	1    1200 1900
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 60556DA2
P 9150 800
F 0 "#PWR0101" H 9150 650 50  0001 C CNN
F 1 "+5V" H 9165 973 50  0000 C CNN
F 2 "" H 9150 800 50  0001 C CNN
F 3 "" H 9150 800 50  0001 C CNN
	1    9150 800 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9550 1300 9150 1300
Wire Wire Line
	9150 1300 9150 800 
Wire Wire Line
	9550 2250 9150 2250
Wire Wire Line
	9150 2250 9150 1300
Connection ~ 9150 1300
Wire Wire Line
	9550 3200 9150 3200
Wire Wire Line
	9150 3200 9150 2250
Connection ~ 9150 2250
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U9
U 1 1 60559B77
P 9550 5000
F 0 "U9" H 10278 4971 50  0000 L CNN
F 1 "stirrer" H 10278 4880 50  0000 L CNN
F 2 "" H 9725 5225 50  0001 C CNN
F 3 "" H 9725 5225 50  0001 C CNN
	1    9550 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9550 4150 9150 4150
Wire Wire Line
	9150 4150 9150 3200
Connection ~ 9150 3200
Wire Wire Line
	9550 5100 9150 5100
Wire Wire Line
	9150 5100 9150 4150
Connection ~ 9150 4150
Wire Wire Line
	9550 5200 9250 5200
Wire Wire Line
	9250 4250 9550 4250
Wire Wire Line
	9250 4250 9250 5200
Wire Wire Line
	9250 4250 9250 3300
Wire Wire Line
	9250 3300 9550 3300
Connection ~ 9250 4250
Wire Wire Line
	9250 3300 9250 2350
Wire Wire Line
	9250 2350 9550 2350
Connection ~ 9250 3300
Wire Wire Line
	9250 2350 9250 1400
Wire Wire Line
	9250 1400 9550 1400
Connection ~ 9250 2350
Wire Wire Line
	9550 1200 7600 1200
Wire Wire Line
	9550 2150 9050 2150
Wire Wire Line
	9050 2150 9050 1300
Wire Wire Line
	9550 3100 8950 3100
Wire Wire Line
	8950 3100 8950 1400
Wire Wire Line
	8850 1500 8850 4050
Wire Wire Line
	8850 4050 9550 4050
Wire Wire Line
	8750 5000 9550 5000
$Comp
L power:GND #PWR0102
U 1 1 605B2E05
P 9250 5300
F 0 "#PWR0102" H 9250 5050 50  0001 C CNN
F 1 "GND" H 9255 5127 50  0000 C CNN
F 2 "" H 9250 5300 50  0001 C CNN
F 3 "" H 9250 5300 50  0001 C CNN
	1    9250 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 5300 9250 5200
Connection ~ 9250 5200
$Comp
L power:+5V #PWR0103
U 1 1 605CA37C
P 8450 800
F 0 "#PWR0103" H 8450 650 50  0001 C CNN
F 1 "+5V" H 8465 973 50  0000 C CNN
F 2 "" H 8450 800 50  0001 C CNN
F 3 "" H 8450 800 50  0001 C CNN
	1    8450 800 
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 60662502
P 8000 2400
F 0 "SW1" H 8000 2685 50  0000 C CNN
F 1 "button1" H 8000 2594 50  0000 C CNN
F 2 "" H 8000 2600 50  0001 C CNN
F 3 "~" H 8000 2600 50  0001 C CNN
	1    8000 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 6066C4F1
P 8000 2700
F 0 "R2" V 7793 2700 50  0000 C CNN
F 1 "10k" V 7884 2700 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 7930 2700 50  0001 C CNN
F 3 "~" H 8000 2700 50  0001 C CNN
	1    8000 2700
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 6066EB9E
P 8000 3150
F 0 "SW2" H 8000 3435 50  0000 C CNN
F 1 "button2" H 8000 3344 50  0000 C CNN
F 2 "" H 8000 3350 50  0001 C CNN
F 3 "~" H 8000 3350 50  0001 C CNN
	1    8000 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 6066EBA4
P 8000 3450
F 0 "R3" V 7793 3450 50  0000 C CNN
F 1 "10k" V 7884 3450 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 7930 3450 50  0001 C CNN
F 3 "~" H 8000 3450 50  0001 C CNN
	1    8000 3450
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW3
U 1 1 6066F98B
P 8000 3900
F 0 "SW3" H 8000 4185 50  0000 C CNN
F 1 "button3" H 8000 4094 50  0000 C CNN
F 2 "" H 8000 4100 50  0001 C CNN
F 3 "~" H 8000 4100 50  0001 C CNN
	1    8000 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 6066F991
P 8000 4200
F 0 "R4" V 7793 4200 50  0000 C CNN
F 1 "10k" V 7884 4200 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 7930 4200 50  0001 C CNN
F 3 "~" H 8000 4200 50  0001 C CNN
	1    8000 4200
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW4
U 1 1 606707FC
P 8000 4650
F 0 "SW4" H 8000 4935 50  0000 C CNN
F 1 "button4" H 8000 4844 50  0000 C CNN
F 2 "" H 8000 4850 50  0001 C CNN
F 3 "~" H 8000 4850 50  0001 C CNN
	1    8000 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 60670802
P 8000 4950
F 0 "R5" V 7793 4950 50  0000 C CNN
F 1 "10k" V 7884 4950 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 7930 4950 50  0001 C CNN
F 3 "~" H 8000 4950 50  0001 C CNN
	1    8000 4950
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW5
U 1 1 60671685
P 8000 5400
F 0 "SW5" H 8000 5685 50  0000 C CNN
F 1 "button5" H 8000 5594 50  0000 C CNN
F 2 "" H 8000 5600 50  0001 C CNN
F 3 "~" H 8000 5600 50  0001 C CNN
	1    8000 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5400 8450 5400
Wire Wire Line
	8450 2400 8200 2400
Wire Wire Line
	8200 3150 8450 3150
Connection ~ 8450 3150
Wire Wire Line
	8450 3150 8450 2400
Wire Wire Line
	8200 3900 8450 3900
Connection ~ 8450 3900
Wire Wire Line
	8450 3900 8450 3150
Wire Wire Line
	8450 5400 8450 4650
Wire Wire Line
	8200 4650 8450 4650
Connection ~ 8450 4650
Wire Wire Line
	8450 4650 8450 3900
$Comp
L Device:R R6
U 1 1 6067168B
P 8000 5700
F 0 "R6" V 7793 5700 50  0000 C CNN
F 1 "10k" V 7884 5700 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 7930 5700 50  0001 C CNN
F 3 "~" H 8000 5700 50  0001 C CNN
	1    8000 5700
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 5400 7600 5400
Wire Wire Line
	7600 5400 7600 5700
Wire Wire Line
	7600 5700 7850 5700
Wire Wire Line
	7800 4650 7600 4650
Wire Wire Line
	7600 4650 7600 4950
Wire Wire Line
	7600 4950 7850 4950
Wire Wire Line
	7800 3900 7600 3900
Wire Wire Line
	7600 3900 7600 4200
Wire Wire Line
	7600 4200 7850 4200
Wire Wire Line
	7800 3150 7600 3150
Wire Wire Line
	7600 3150 7600 3450
Wire Wire Line
	7600 3450 7850 3450
Wire Wire Line
	7800 2400 7600 2400
Wire Wire Line
	7600 2400 7600 2700
Wire Wire Line
	7600 2700 7850 2700
Wire Wire Line
	8150 5700 8350 5700
Wire Wire Line
	8350 5700 8350 4950
Wire Wire Line
	8350 2700 8150 2700
Wire Wire Line
	8150 3450 8350 3450
Connection ~ 8350 3450
Wire Wire Line
	8350 3450 8350 2700
Wire Wire Line
	8150 4200 8350 4200
Connection ~ 8350 4200
Wire Wire Line
	8350 4200 8350 3450
Wire Wire Line
	8150 4950 8350 4950
Connection ~ 8350 4950
Wire Wire Line
	8350 4950 8350 4200
$Comp
L power:GND #PWR0104
U 1 1 606C1AC9
P 8350 5850
F 0 "#PWR0104" H 8350 5600 50  0001 C CNN
F 1 "GND" H 8355 5677 50  0000 C CNN
F 2 "" H 8350 5850 50  0001 C CNN
F 3 "" H 8350 5850 50  0001 C CNN
	1    8350 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5850 8350 5700
Connection ~ 8350 5700
Wire Wire Line
	8450 2400 8450 800 
Connection ~ 8450 2400
$Comp
L Device:R R1
U 1 1 6070C8C3
P 1600 4550
F 0 "R1" V 1393 4550 50  0000 C CNN
F 1 "4.7k" V 1484 4550 50  0000 C CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 1530 4550 50  0001 C CNN
F 3 "~" H 1600 4550 50  0001 C CNN
	1    1600 4550
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 2000 2900 2000
Wire Wire Line
	1400 2100 2900 2100
Wire Wire Line
	1400 1800 1600 1800
Wire Wire Line
	1600 1800 1600 800 
$Comp
L power:+5V #PWR0107
U 1 1 607442DE
P 1600 800
F 0 "#PWR0107" H 1600 650 50  0001 C CNN
F 1 "+5V" H 1615 973 50  0000 C CNN
F 2 "" H 1600 800 50  0001 C CNN
F 3 "" H 1600 800 50  0001 C CNN
	1    1600 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60744827
P 1050 5300
F 0 "#PWR0108" H 1050 5050 50  0001 C CNN
F 1 "GND" H 1055 5127 50  0000 C CNN
F 2 "" H 1050 5300 50  0001 C CNN
F 3 "" H 1050 5300 50  0001 C CNN
	1    1050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1900 1500 1900
Wire Wire Line
	1500 1900 1500 3150
$Comp
L power:+5V #PWR0109
U 1 1 607528B2
P 2250 4600
F 0 "#PWR0109" H 2250 4450 50  0001 C CNN
F 1 "+5V" H 2265 4773 50  0000 C CNN
F 2 "" H 2250 4600 50  0001 C CNN
F 3 "" H 2250 4600 50  0001 C CNN
	1    2250 4600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 60752EDB
P 2600 5850
F 0 "#PWR0110" H 2600 5600 50  0001 C CNN
F 1 "GND" H 2605 5677 50  0000 C CNN
F 2 "" H 2600 5850 50  0001 C CNN
F 3 "" H 2600 5850 50  0001 C CNN
	1    2600 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5200 2250 5200
Wire Wire Line
	2250 5200 2250 4600
$Comp
L My_Parts:2-pole_power_in_screw_terminal U4
U 1 1 607870A4
P 2000 5500
F 0 "U4" H 2403 5501 50  0000 L CNN
F 1 "Power in" H 2403 5410 50  0000 L CNN
F 2 "My_Parts:2-pole_power_in_screw_terminal" H 2175 5625 50  0001 C CNN
F 3 "" H 2175 5625 50  0001 C CNN
	1    2000 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 3950 1500 3950
Connection ~ 1500 3950
Wire Wire Line
	1400 3150 1500 3150
Connection ~ 1500 3150
Wire Wire Line
	1500 3150 1500 3950
Wire Wire Line
	1400 3050 1600 3050
Wire Wire Line
	1600 3050 1600 1800
Connection ~ 1600 1800
Wire Wire Line
	1400 3850 1600 3850
Wire Wire Line
	1600 3850 1600 3050
Connection ~ 1600 3050
$Comp
L My_Parts:DFRobot_Gravity_TDS-meter U3
U 1 1 6056F317
P 1400 3750
F 0 "U3" H 1605 3990 50  0000 C CNN
F 1 "TDS meter" H 1605 3899 50  0000 C CNN
F 2 "My_Headers:3-pin_DFRobot_Gravity_TDS-meter_header_large" H 1575 3875 50  0001 C CNN
F 3 "" H 1575 3875 50  0001 C CNN
	1    1400 3750
	-1   0    0    -1  
$EndComp
$Comp
L My_Parts:DFRobot_Gravity_pH-sensor U2
U 1 1 6056DA8C
P 1400 2950
F 0 "U2" H 1605 3190 50  0000 C CNN
F 1 "pH sensor" H 1605 3099 50  0000 C CNN
F 2 "My_Headers:3-pin_DFRobot_Gravity_pH-sensor_header_large" H 1575 3075 50  0001 C CNN
F 3 "" H 1575 3075 50  0001 C CNN
	1    1400 2950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 2950 1700 2950
Wire Wire Line
	1700 2950 1700 2500
Wire Wire Line
	1700 2500 2900 2500
Wire Wire Line
	1400 3750 1800 3750
Wire Wire Line
	1800 3750 1800 2600
Wire Wire Line
	1800 2600 2900 2600
Wire Wire Line
	7600 3150 7500 3150
Connection ~ 7600 3150
Wire Wire Line
	7400 3900 7600 3900
Connection ~ 7600 3900
Wire Wire Line
	7600 4650 7300 4650
Connection ~ 7600 4650
Wire Wire Line
	7600 5400 7200 5400
Connection ~ 7600 5400
Connection ~ 7600 2400
Wire Wire Line
	2000 5600 2600 5600
Wire Wire Line
	2600 4800 2900 4800
Wire Wire Line
	2600 4800 2600 5600
Wire Wire Line
	8750 1600 8750 5000
Wire Wire Line
	2600 5850 2600 5600
Connection ~ 2600 5600
Text GLabel 7050 2400 0    50   Input ~ 0
button1
Text GLabel 7050 3150 0    50   Input ~ 0
button2
Text GLabel 7050 3900 0    50   Input ~ 0
button3
Text GLabel 7050 4650 0    50   Input ~ 0
button4
Text GLabel 7050 5400 0    50   Input ~ 0
button5
$Comp
L Connector:Screw_Terminal_01x06 J2
U 1 1 607CA2CB
P 1300 6300
F 0 "J2" H 1380 6292 50  0000 L CNN
F 1 "Buttons" H 1380 6201 50  0000 L CNN
F 2 "My_Parts:6-pole_5-NO_switch_screw_terminal" H 1300 6300 50  0001 C CNN
F 3 "~" H 1300 6300 50  0001 C CNN
	1    1300 6300
	1    0    0    -1  
$EndComp
Text GLabel 1000 6200 0    50   Input ~ 0
button1
Text GLabel 1000 6300 0    50   Input ~ 0
button2
Text GLabel 1000 6400 0    50   Input ~ 0
button3
Text GLabel 1000 6500 0    50   Input ~ 0
button4
Text GLabel 1000 6600 0    50   Input ~ 0
button5
Wire Wire Line
	1100 6200 1000 6200
Wire Wire Line
	1000 6300 1100 6300
Wire Wire Line
	1100 6400 1000 6400
Wire Wire Line
	1000 6500 1100 6500
Wire Wire Line
	1100 6600 1000 6600
Text GLabel 7600 1100 1    50   Input ~ 0
pH+
Text GLabel 7500 1100 1    50   Input ~ 0
pH-
Text GLabel 7400 1100 1    50   Input ~ 0
nutrA
Text GLabel 7300 1100 1    50   Input ~ 0
nutrB
Text GLabel 7200 1100 1    50   Input ~ 0
stirrer
Wire Wire Line
	7600 1200 7600 1100
Connection ~ 7600 1200
Wire Wire Line
	7600 1200 5500 1200
$Comp
L Connector:Screw_Terminal_01x07 J3
U 1 1 60855372
P 2150 7050
F 0 "J3" H 2230 7092 50  0000 L CNN
F 1 "MOSFETs" H 2230 7001 50  0000 L CNN
F 2 "My_Parts:7-pole_6-MOSFET_screw_terminal" H 2150 7050 50  0001 C CNN
F 3 "~" H 2150 7050 50  0001 C CNN
	1    2150 7050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 60856567
P 1850 6550
F 0 "#PWR0113" H 1850 6400 50  0001 C CNN
F 1 "+5V" H 1865 6723 50  0000 C CNN
F 2 "" H 1850 6550 50  0001 C CNN
F 3 "" H 1850 6550 50  0001 C CNN
	1    1850 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6750 1850 6750
Wire Wire Line
	1850 6750 1850 6550
Text GLabel 1700 6950 0    50   Input ~ 0
pH+
Text GLabel 1700 7050 0    50   Input ~ 0
pH-
Text GLabel 1700 7150 0    50   Input ~ 0
nutrA
Text GLabel 1700 7250 0    50   Input ~ 0
nutrB
Text GLabel 1700 7350 0    50   Input ~ 0
stirrer
Wire Wire Line
	1950 6950 1700 6950
Wire Wire Line
	1700 7050 1950 7050
Wire Wire Line
	1950 7150 1700 7150
Wire Wire Line
	1700 7250 1950 7250
Wire Wire Line
	1950 7350 1700 7350
Wire Wire Line
	1950 6850 1850 6850
Wire Wire Line
	1850 6850 1850 7450
$Comp
L power:GND #PWR0114
U 1 1 6091C813
P 1850 7450
F 0 "#PWR0114" H 1850 7200 50  0001 C CNN
F 1 "GND" H 1855 7277 50  0000 C CNN
F 2 "" H 1850 7450 50  0001 C CNN
F 3 "" H 1850 7450 50  0001 C CNN
	1    1850 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1300 5500 1300
Wire Wire Line
	9050 1300 7500 1300
Connection ~ 7500 1300
Wire Wire Line
	7500 1100 7500 1300
Wire Wire Line
	7400 1400 5500 1400
Wire Wire Line
	8950 1400 7400 1400
Connection ~ 7400 1400
Wire Wire Line
	7400 1400 7400 1100
Wire Wire Line
	7300 1500 8850 1500
Wire Wire Line
	5500 1500 7300 1500
Connection ~ 7300 1500
Wire Wire Line
	7300 1500 7300 1100
Wire Wire Line
	7200 1600 5500 1600
Wire Wire Line
	8750 1600 7200 1600
Connection ~ 7200 1600
Wire Wire Line
	7200 1100 7200 1600
Wire Wire Line
	1000 6100 1100 6100
Wire Wire Line
	1000 6100 1000 5900
$Comp
L power:+5V #PWR0111
U 1 1 607CDEE8
P 1000 5900
F 0 "#PWR0111" H 1000 5750 50  0001 C CNN
F 1 "+5V" H 1015 6073 50  0000 C CNN
F 2 "" H 1000 5900 50  0001 C CNN
F 3 "" H 1000 5900 50  0001 C CNN
	1    1000 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 5200 1050 5200
Wire Wire Line
	1500 3950 1500 5200
Wire Wire Line
	1050 5300 1050 5200
Connection ~ 1050 5200
Wire Wire Line
	1050 5200 1050 5050
Wire Wire Line
	1600 3850 1600 4350
Wire Wire Line
	1600 4350 1050 4350
Wire Wire Line
	1050 4350 1050 4450
Connection ~ 1600 3850
Wire Wire Line
	1350 4750 1600 4750
Wire Wire Line
	1900 4750 1900 2700
Wire Wire Line
	1900 2700 2900 2700
Wire Wire Line
	1600 4400 1600 4350
Connection ~ 1600 4350
Wire Wire Line
	1600 4700 1600 4750
Connection ~ 1600 4750
Wire Wire Line
	1600 4750 1900 4750
Wire Wire Line
	7600 1700 5500 1700
Wire Wire Line
	7600 1700 7600 2400
Wire Wire Line
	7500 1800 5500 1800
Wire Wire Line
	7500 1800 7500 3150
Wire Wire Line
	7400 1900 5500 1900
Wire Wire Line
	7400 1900 7400 3900
Wire Wire Line
	7300 2000 5500 2000
Wire Wire Line
	7300 2000 7300 4650
Wire Wire Line
	7200 2100 5500 2100
Wire Wire Line
	7200 2100 7200 5400
Wire Wire Line
	7050 5400 7200 5400
Connection ~ 7200 5400
Wire Wire Line
	7050 4650 7300 4650
Connection ~ 7300 4650
Wire Wire Line
	7050 3900 7400 3900
Connection ~ 7400 3900
Wire Wire Line
	7050 3150 7500 3150
Connection ~ 7500 3150
Wire Wire Line
	7050 2400 7600 2400
$Comp
L power:GND #PWR0105
U 1 1 6065BBCD
P 6600 7450
F 0 "#PWR0105" H 6600 7200 50  0001 C CNN
F 1 "GND" H 6605 7277 50  0000 C CNN
F 2 "" H 6600 7450 50  0001 C CNN
F 3 "" H 6600 7450 50  0001 C CNN
	1    6600 7450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 7450 6600 7300
Wire Wire Line
	6600 6500 5850 6500
$Comp
L power:+3.3V #PWR0106
U 1 1 6066632F
P 2500 4600
F 0 "#PWR0106" H 2500 4450 50  0001 C CNN
F 1 "+3.3V" H 2515 4773 50  0000 C CNN
F 2 "" H 2500 4600 50  0001 C CNN
F 3 "" H 2500 4600 50  0001 C CNN
	1    2500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5100 2500 5100
Wire Wire Line
	2500 5100 2500 4600
$Comp
L power:+3.3V #PWR0115
U 1 1 6066FC4A
P 4300 6200
F 0 "#PWR0115" H 4300 6050 50  0001 C CNN
F 1 "+3.3V" H 4315 6373 50  0000 C CNN
F 2 "" H 4300 6200 50  0001 C CNN
F 3 "" H 4300 6200 50  0001 C CNN
	1    4300 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 6800 4300 6800
Wire Wire Line
	4300 6800 4300 6600
Text GLabel 2800 1400 0    50   Input ~ 0
Rx
Text GLabel 2800 1500 0    50   Input ~ 0
Tx
Text GLabel 4800 6700 0    50   Input ~ 0
espReset
Wire Wire Line
	4900 6700 4800 6700
Text GLabel 4800 6500 0    50   Input ~ 0
Rx
Wire Wire Line
	4900 6500 4800 6500
Text GLabel 6300 5750 1    50   Input ~ 0
Tx
Wire Wire Line
	6300 6800 5850 6800
Wire Wire Line
	4900 6600 4300 6600
Connection ~ 4300 6600
Wire Wire Line
	4300 6600 4300 6200
$Comp
L Device:R R7
U 1 1 60744C67
P 6300 6100
F 0 "R7" H 6370 6146 50  0000 L CNN
F 1 "1k" H 6370 6055 50  0000 L CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 6230 6100 50  0001 C CNN
F 3 "~" H 6300 6100 50  0001 C CNN
	1    6300 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R8
U 1 1 60745883
P 6300 7050
F 0 "R8" H 6370 7096 50  0000 L CNN
F 1 "2.2k" H 6370 7005 50  0000 L CNN
F 2 "My_Misc:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal_larger_pads" V 6230 7050 50  0001 C CNN
F 3 "~" H 6300 7050 50  0001 C CNN
	1    6300 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 6250 6300 6800
Wire Wire Line
	6300 6800 6300 6900
Connection ~ 6300 6800
Wire Wire Line
	6300 5950 6300 5750
Wire Wire Line
	6300 7200 6300 7300
Wire Wire Line
	6300 7300 6600 7300
Connection ~ 6600 7300
Wire Wire Line
	6600 7300 6600 6500
$Comp
L My_Arduino:ESP-01 U10
U 1 1 608444F6
P 4900 6500
F 0 "U10" H 5375 6725 50  0000 C CNN
F 1 "ESP-01" H 5375 6634 50  0000 C CNN
F 2 "My_Arduino:ESP-01_large" H 5600 6350 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 5600 6350 50  0001 C CNN
	1    4900 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 1400 2800 1400
Wire Wire Line
	2900 1500 2800 1500
Text GLabel 5600 2200 2    50   Input ~ 0
espReset
Wire Wire Line
	5600 2200 5500 2200
Wire Wire Line
	2000 5500 2900 5500
$Comp
L My_Parts:KY-019_relay_module K1
U 1 1 6076CBC1
P 3050 6600
F 0 "K1" H 3400 6967 50  0000 C CNN
F 1 "KY-019_relay_module" H 3400 6876 50  0000 C CNN
F 2 "My_Headers:3-pin_KY-019_Relay_header_larger_pads" H 3550 6550 50  0001 L CNN
F 3 "" V 3400 6400 50  0001 C CNN
	1    3050 6600
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 6076DCDC
P 2550 6550
F 0 "#PWR0112" H 2550 6400 50  0001 C CNN
F 1 "+5V" H 2565 6723 50  0000 C CNN
F 2 "" H 2550 6550 50  0001 C CNN
F 3 "" H 2550 6550 50  0001 C CNN
	1    2550 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6700 2550 6700
Wire Wire Line
	2550 6700 2550 6550
Text GLabel 2950 6600 0    50   Input ~ 0
Relay
$Comp
L power:GND #PWR0116
U 1 1 6077A902
P 3950 7300
F 0 "#PWR0116" H 3950 7050 50  0001 C CNN
F 1 "GND" H 3955 7127 50  0000 C CNN
F 2 "" H 3950 7300 50  0001 C CNN
F 3 "" H 3950 7300 50  0001 C CNN
	1    3950 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 6600 3950 6600
Wire Wire Line
	3950 6600 3950 7300
Wire Wire Line
	3050 6600 2950 6600
Text GLabel 5950 6600 2    50   Input ~ 0
Relay
Wire Wire Line
	5950 6600 5850 6600
$Comp
L Device:Jumper JP1
U 1 1 60771DF8
P 2400 3200
F 0 "JP1" V 2446 3113 50  0000 R CNN
F 1 "Flash" V 2355 3113 50  0000 R CNN
F 2 "My_Parts:Jumper_1x02_P2.54mm_large" H 2400 3200 50  0001 C CNN
F 3 "~" H 2400 3200 50  0001 C CNN
	1    2400 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2400 2900 2400 1900
Wire Wire Line
	2400 1900 2900 1900
Wire Wire Line
	2400 4300 2400 3500
Wire Wire Line
	2400 4300 2900 4300
$EndSCHEMATC
