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
F 2 "My_Arduino:Arduino_Mega2560_Shield_large" H 4900 6100 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-mega-2560-rev3" H 4900 6100 60  0001 C CNN
	1    4200 3350
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Temperature:DS18B20 U1
U 1 1 60465402
P 6500 2950
F 0 "U1" H 6270 2996 50  0000 R CNN
F 1 "DS18B20" H 6270 2905 50  0000 R CNN
F 2 "My_Headers:3_pin_Dallas_1-wire_header_larger_pads" H 5500 2700 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf" H 6350 3200 50  0001 C CNN
	1    6500 2950
	-1   0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U?
U 1 1 6046FFFD
P 9550 1200
F 0 "U?" H 10278 1171 50  0000 L CNN
F 1 "pH+ pump" H 10278 1080 50  0000 L CNN
F 2 "" H 9725 1425 50  0001 C CNN
F 3 "" H 9725 1425 50  0001 C CNN
	1    9550 1200
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U?
U 1 1 60471911
P 9550 2150
F 0 "U?" H 10278 2121 50  0000 L CNN
F 1 "pH- pump" H 10278 2030 50  0000 L CNN
F 2 "" H 9725 2375 50  0001 C CNN
F 3 "" H 9725 2375 50  0001 C CNN
	1    9550 2150
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U?
U 1 1 60471FF1
P 9550 3100
F 0 "U?" H 10278 3071 50  0000 L CNN
F 1 "nutr A pump" H 10278 2980 50  0000 L CNN
F 2 "" H 9725 3325 50  0001 C CNN
F 3 "" H 9725 3325 50  0001 C CNN
	1    9550 3100
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:HCMODU0083_IRF520_MOSFET_module U?
U 1 1 604749DB
P 9550 4050
F 0 "U?" H 10278 4021 50  0000 L CNN
F 1 "nutr B pump" H 10278 3930 50  0000 L CNN
F 2 "" H 9725 4275 50  0001 C CNN
F 3 "" H 9725 4275 50  0001 C CNN
	1    9550 4050
	1    0    0    -1  
$EndComp
$Comp
L My_Headers:4-pin_I2C_LCD_header J?
U 1 1 60475C3F
P 1650 1900
F 0 "J?" H 1878 1896 50  0000 L CNN
F 1 "LCD display" H 1878 1805 50  0000 L CNN
F 2 "" H 1850 1500 50  0001 C CNN
F 3 "~" H 1650 1900 50  0001 C CNN
	1    1650 1900
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60556DA2
P 9150 800
F 0 "#PWR?" H 9150 650 50  0001 C CNN
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
L My_Parts:HCMODU0083_IRF520_MOSFET_module U?
U 1 1 60559B77
P 9550 5000
F 0 "U?" H 10278 4971 50  0000 L CNN
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
	9550 1200 5500 1200
Wire Wire Line
	9550 2150 9050 2150
Wire Wire Line
	9050 2150 9050 1300
Wire Wire Line
	9050 1300 5500 1300
Wire Wire Line
	9550 3100 8950 3100
Wire Wire Line
	8950 3100 8950 1400
Wire Wire Line
	8950 1400 5500 1400
Wire Wire Line
	5500 1500 8850 1500
Wire Wire Line
	8850 1500 8850 4050
Wire Wire Line
	8850 4050 9550 4050
Wire Wire Line
	5500 2100 8750 2100
Wire Wire Line
	8750 2100 8750 5000
Wire Wire Line
	8750 5000 9550 5000
$Comp
L power:GND #PWR?
U 1 1 605B2E05
P 9250 5300
F 0 "#PWR?" H 9250 5050 50  0001 C CNN
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
L power:+5V #PWR?
U 1 1 605CA37C
P 8450 800
F 0 "#PWR?" H 8450 650 50  0001 C CNN
F 1 "+5V" H 8465 973 50  0000 C CNN
F 2 "" H 8450 800 50  0001 C CNN
F 3 "" H 8450 800 50  0001 C CNN
	1    8450 800 
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 60662502
P 8000 2500
F 0 "SW?" H 8000 2785 50  0000 C CNN
F 1 "SW_Push" H 8000 2694 50  0000 C CNN
F 2 "" H 8000 2700 50  0001 C CNN
F 3 "~" H 8000 2700 50  0001 C CNN
	1    8000 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6066C4F1
P 8000 2800
F 0 "R?" V 7793 2800 50  0000 C CNN
F 1 "10k" V 7884 2800 50  0000 C CNN
F 2 "" V 7930 2800 50  0001 C CNN
F 3 "~" H 8000 2800 50  0001 C CNN
	1    8000 2800
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 6066EB9E
P 8000 3250
F 0 "SW?" H 8000 3535 50  0000 C CNN
F 1 "SW_Push" H 8000 3444 50  0000 C CNN
F 2 "" H 8000 3450 50  0001 C CNN
F 3 "~" H 8000 3450 50  0001 C CNN
	1    8000 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6066EBA4
P 8000 3550
F 0 "R?" V 7793 3550 50  0000 C CNN
F 1 "10k" V 7884 3550 50  0000 C CNN
F 2 "" V 7930 3550 50  0001 C CNN
F 3 "~" H 8000 3550 50  0001 C CNN
	1    8000 3550
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 6066F98B
P 8000 4000
F 0 "SW?" H 8000 4285 50  0000 C CNN
F 1 "SW_Push" H 8000 4194 50  0000 C CNN
F 2 "" H 8000 4200 50  0001 C CNN
F 3 "~" H 8000 4200 50  0001 C CNN
	1    8000 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6066F991
P 8000 4300
F 0 "R?" V 7793 4300 50  0000 C CNN
F 1 "10k" V 7884 4300 50  0000 C CNN
F 2 "" V 7930 4300 50  0001 C CNN
F 3 "~" H 8000 4300 50  0001 C CNN
	1    8000 4300
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 606707FC
P 8000 4750
F 0 "SW?" H 8000 5035 50  0000 C CNN
F 1 "SW_Push" H 8000 4944 50  0000 C CNN
F 2 "" H 8000 4950 50  0001 C CNN
F 3 "~" H 8000 4950 50  0001 C CNN
	1    8000 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60670802
P 8000 5050
F 0 "R?" V 7793 5050 50  0000 C CNN
F 1 "10k" V 7884 5050 50  0000 C CNN
F 2 "" V 7930 5050 50  0001 C CNN
F 3 "~" H 8000 5050 50  0001 C CNN
	1    8000 5050
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 60671685
P 8000 5500
F 0 "SW?" H 8000 5785 50  0000 C CNN
F 1 "SW_Push" H 8000 5694 50  0000 C CNN
F 2 "" H 8000 5700 50  0001 C CNN
F 3 "~" H 8000 5700 50  0001 C CNN
	1    8000 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5500 8450 5500
Wire Wire Line
	8450 2500 8200 2500
Wire Wire Line
	8200 3250 8450 3250
Connection ~ 8450 3250
Wire Wire Line
	8450 3250 8450 2500
Wire Wire Line
	8200 4000 8450 4000
Connection ~ 8450 4000
Wire Wire Line
	8450 4000 8450 3250
Wire Wire Line
	8450 5500 8450 4750
Wire Wire Line
	8200 4750 8450 4750
Connection ~ 8450 4750
Wire Wire Line
	8450 4750 8450 4000
$Comp
L Device:R R?
U 1 1 6067168B
P 8000 5800
F 0 "R?" V 7793 5800 50  0000 C CNN
F 1 "10k" V 7884 5800 50  0000 C CNN
F 2 "" V 7930 5800 50  0001 C CNN
F 3 "~" H 8000 5800 50  0001 C CNN
	1    8000 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 5500 7600 5500
Wire Wire Line
	7600 5500 7600 5800
Wire Wire Line
	7600 5800 7850 5800
Wire Wire Line
	7800 4750 7600 4750
Wire Wire Line
	7600 4750 7600 5050
Wire Wire Line
	7600 5050 7850 5050
Wire Wire Line
	7800 4000 7600 4000
Wire Wire Line
	7600 4000 7600 4300
Wire Wire Line
	7600 4300 7850 4300
Wire Wire Line
	7800 3250 7600 3250
Wire Wire Line
	7600 3250 7600 3550
Wire Wire Line
	7600 3550 7850 3550
Wire Wire Line
	7800 2500 7600 2500
Wire Wire Line
	7600 2500 7600 2800
Wire Wire Line
	7600 2800 7850 2800
Wire Wire Line
	7600 2500 7600 1600
Wire Wire Line
	7600 1600 5500 1600
Connection ~ 7600 2500
Wire Wire Line
	5500 1700 7500 1700
Wire Wire Line
	7500 1700 7500 3250
Wire Wire Line
	7500 3250 7600 3250
Connection ~ 7600 3250
Wire Wire Line
	5500 1800 7400 1800
Wire Wire Line
	7400 1800 7400 4000
Wire Wire Line
	7400 4000 7600 4000
Connection ~ 7600 4000
Wire Wire Line
	5500 1900 7300 1900
Wire Wire Line
	7300 1900 7300 4750
Wire Wire Line
	7300 4750 7600 4750
Connection ~ 7600 4750
Wire Wire Line
	5500 2000 7200 2000
Wire Wire Line
	7200 2000 7200 5500
Wire Wire Line
	7200 5500 7600 5500
Connection ~ 7600 5500
Wire Wire Line
	8150 5800 8350 5800
Wire Wire Line
	8350 5800 8350 5050
Wire Wire Line
	8350 2800 8150 2800
Wire Wire Line
	8150 3550 8350 3550
Connection ~ 8350 3550
Wire Wire Line
	8350 3550 8350 2800
Wire Wire Line
	8150 4300 8350 4300
Connection ~ 8350 4300
Wire Wire Line
	8350 4300 8350 3550
Wire Wire Line
	8150 5050 8350 5050
Connection ~ 8350 5050
Wire Wire Line
	8350 5050 8350 4300
$Comp
L power:GND #PWR?
U 1 1 606C1AC9
P 8350 5950
F 0 "#PWR?" H 8350 5700 50  0001 C CNN
F 1 "GND" H 8355 5777 50  0000 C CNN
F 2 "" H 8350 5950 50  0001 C CNN
F 3 "" H 8350 5950 50  0001 C CNN
	1    8350 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 5950 8350 5800
Connection ~ 8350 5800
Wire Wire Line
	8450 2500 8450 800 
Connection ~ 8450 2500
Wire Wire Line
	6500 2650 6500 2450
$Comp
L power:+5V #PWR?
U 1 1 606F8C9A
P 6500 800
F 0 "#PWR?" H 6500 650 50  0001 C CNN
F 1 "+5V" H 6515 973 50  0000 C CNN
F 2 "" H 6500 800 50  0001 C CNN
F 3 "" H 6500 800 50  0001 C CNN
	1    6500 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606FE80C
P 6500 3350
F 0 "#PWR?" H 6500 3100 50  0001 C CNN
F 1 "GND" H 6505 3177 50  0000 C CNN
F 2 "" H 6500 3350 50  0001 C CNN
F 3 "" H 6500 3350 50  0001 C CNN
	1    6500 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3350 6500 3250
Wire Wire Line
	5500 2200 6100 2200
Wire Wire Line
	6100 2200 6100 2450
Wire Wire Line
	6100 2950 6200 2950
$Comp
L Device:R R?
U 1 1 6070C8C3
P 6300 2450
F 0 "R?" V 6093 2450 50  0000 C CNN
F 1 "4.7k" V 6184 2450 50  0000 C CNN
F 2 "" V 6230 2450 50  0001 C CNN
F 3 "~" H 6300 2450 50  0001 C CNN
	1    6300 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 2450 6500 2450
Connection ~ 6500 2450
Wire Wire Line
	6500 2450 6500 800 
Wire Wire Line
	6150 2450 6100 2450
Connection ~ 6100 2450
Wire Wire Line
	6100 2450 6100 2950
Wire Wire Line
	1850 2000 2900 2000
Wire Wire Line
	1850 2100 2900 2100
Wire Wire Line
	1850 1800 1950 1800
Wire Wire Line
	1950 1800 1950 800 
$Comp
L power:+5V #PWR?
U 1 1 607442DE
P 1950 800
F 0 "#PWR?" H 1950 650 50  0001 C CNN
F 1 "+5V" H 1965 973 50  0000 C CNN
F 2 "" H 1950 800 50  0001 C CNN
F 3 "" H 1950 800 50  0001 C CNN
	1    1950 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60744827
P 1950 2350
F 0 "#PWR?" H 1950 2100 50  0001 C CNN
F 1 "GND" H 1955 2177 50  0000 C CNN
F 2 "" H 1950 2350 50  0001 C CNN
F 3 "" H 1950 2350 50  0001 C CNN
	1    1950 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1900 1950 1900
Wire Wire Line
	1950 1900 1950 2350
$Comp
L power:+5V #PWR?
U 1 1 607528B2
P 2500 4500
F 0 "#PWR?" H 2500 4350 50  0001 C CNN
F 1 "+5V" H 2515 4673 50  0000 C CNN
F 2 "" H 2500 4500 50  0001 C CNN
F 3 "" H 2500 4500 50  0001 C CNN
	1    2500 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60752EDB
P 2600 5900
F 0 "#PWR?" H 2600 5650 50  0001 C CNN
F 1 "GND" H 2605 5727 50  0000 C CNN
F 2 "" H 2600 5900 50  0001 C CNN
F 3 "" H 2600 5900 50  0001 C CNN
	1    2600 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 5900 2600 4600
Wire Wire Line
	2600 4600 2900 4600
Wire Wire Line
	2900 5200 2500 5200
Wire Wire Line
	2500 5200 2500 4500
Wire Wire Line
	2900 5500 2200 5500
Wire Wire Line
	2200 5500 2200 4500
$Comp
L power:+6V #PWR?
U 1 1 60765CCF
P 2200 4500
F 0 "#PWR?" H 2200 4350 50  0001 C CNN
F 1 "+6V" H 2215 4673 50  0000 C CNN
F 2 "" H 2200 4500 50  0001 C CNN
F 3 "" H 2200 4500 50  0001 C CNN
	1    2200 4500
	1    0    0    -1  
$EndComp
$Comp
L My_Parts:2-pole_power_in_screw_terminal U?
U 1 1 607870A4
P 5900 6700
F 0 "U?" H 6303 6701 50  0000 L CNN
F 1 "Power in" H 6303 6610 50  0000 L CNN
F 2 "" H 6075 6825 50  0001 C CNN
F 3 "" H 6075 6825 50  0001 C CNN
	1    5900 6700
	1    0    0    -1  
$EndComp
$Comp
L power:+6V #PWR?
U 1 1 6078A76B
P 5800 6500
F 0 "#PWR?" H 5800 6350 50  0001 C CNN
F 1 "+6V" H 5815 6673 50  0000 C CNN
F 2 "" H 5800 6500 50  0001 C CNN
F 3 "" H 5800 6500 50  0001 C CNN
	1    5800 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6078AD58
P 5800 6950
F 0 "#PWR?" H 5800 6700 50  0001 C CNN
F 1 "GND" H 5805 6777 50  0000 C CNN
F 2 "" H 5800 6950 50  0001 C CNN
F 3 "" H 5800 6950 50  0001 C CNN
	1    5800 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 6700 5800 6700
Wire Wire Line
	5800 6700 5800 6500
Wire Wire Line
	5900 6800 5800 6800
Wire Wire Line
	5800 6800 5800 6950
$EndSCHEMATC
