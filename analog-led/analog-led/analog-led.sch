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
L Transistor_BJT:BC547 Q2
U 1 1 61C36CAF
P 5800 5950
F 0 "Q2" H 5991 5996 50  0000 L CNN
F 1 "BC547" H 5991 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6000 5875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 5800 5950 50  0001 L CNN
	1    5800 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R4
U 1 1 61C37FF9
P 6350 3050
F 0 "R4" H 6418 3096 50  0000 L CNN
F 1 "R_Small_US" H 6418 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6350 3050 50  0001 C CNN
F 3 "~" H 6350 3050 50  0001 C CNN
	1    6350 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 61C389C8
P 6150 5600
F 0 "C2" H 6242 5646 50  0000 L CNN
F 1 "C_Small" H 6242 5555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6150 5600 50  0001 C CNN
F 3 "~" H 6150 5600 50  0001 C CNN
	1    6150 5600
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 61C38FB7
P 10550 1500
F 0 "#PWR0101" H 10550 1350 50  0001 C CNN
F 1 "+5V" H 10565 1673 50  0000 C CNN
F 2 "" H 10550 1500 50  0001 C CNN
F 3 "" H 10550 1500 50  0001 C CNN
	1    10550 1500
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 61C392F9
P 8350 1500
F 0 "#PWR0102" H 8350 1350 50  0001 C CNN
F 1 "+3.3V" H 8365 1673 50  0000 C CNN
F 2 "" H 8350 1500 50  0001 C CNN
F 3 "" H 8350 1500 50  0001 C CNN
	1    8350 1500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 61C395E7
P 5900 6400
F 0 "#PWR0103" H 5900 6150 50  0001 C CNN
F 1 "GND" H 5905 6227 50  0000 C CNN
F 2 "" H 5900 6400 50  0001 C CNN
F 3 "" H 5900 6400 50  0001 C CNN
	1    5900 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D5
U 1 1 61C39B85
P 5700 3300
F 0 "D5" V 5739 3183 50  0000 R CNN
F 1 "LED" V 5648 3183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 3300 50  0001 C CNN
F 3 "~" H 5700 3300 50  0001 C CNN
	1    5700 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 61C3FA54
P 5450 3050
F 0 "R3" H 5518 3096 50  0000 L CNN
F 1 "R_Small_US" H 5518 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5450 3050 50  0001 C CNN
F 3 "~" H 5450 3050 50  0001 C CNN
	1    5450 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D6
U 1 1 61C402CC
P 5700 3550
F 0 "D6" V 5739 3433 50  0000 R CNN
F 1 "LED" V 5648 3433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 3550 50  0001 C CNN
F 3 "~" H 5700 3550 50  0001 C CNN
	1    5700 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D7
U 1 1 61C4051A
P 5700 3850
F 0 "D7" V 5739 3733 50  0000 R CNN
F 1 "LED" V 5648 3733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 3850 50  0001 C CNN
F 3 "~" H 5700 3850 50  0001 C CNN
	1    5700 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 5750 5900 5600
Wire Wire Line
	5900 3850 5850 3850
Wire Wire Line
	5900 6150 5900 6400
Wire Wire Line
	5900 5600 6050 5600
Wire Wire Line
	5550 3850 5450 3850
Wire Wire Line
	5450 3300 5550 3300
Wire Wire Line
	5550 3550 5450 3550
Connection ~ 5450 3550
Wire Wire Line
	5450 3550 5450 3300
Wire Wire Line
	5450 3300 5450 3150
Connection ~ 5450 3300
$Comp
L Regulator_Linear:AZ1117-3.3 U1
U 1 1 61C4442B
P 9200 1500
F 0 "U1" H 9200 1742 50  0000 C CNN
F 1 "AZ1117-3.3" H 9200 1651 50  0000 C CNN
F 2 "" H 9200 1750 50  0001 C CIN
F 3 "https://www.diodes.com/assets/Datasheets/AZ1117.pdf" H 9200 1500 50  0001 C CNN
	1    9200 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 61C45953
P 9750 1650
F 0 "C5" H 9842 1696 50  0000 L CNN
F 1 "C_Small" H 9842 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9750 1650 50  0001 C CNN
F 3 "~" H 9750 1650 50  0001 C CNN
	1    9750 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C4
U 1 1 61C45E22
P 8800 1650
F 0 "C4" H 8892 1696 50  0000 L CNN
F 1 "C_Small" H 8892 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8800 1650 50  0001 C CNN
F 3 "~" H 8800 1650 50  0001 C CNN
	1    8800 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 61C46095
P 8550 1650
F 0 "C3" H 8642 1696 50  0000 L CNN
F 1 "C_Small" H 8642 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8550 1650 50  0001 C CNN
F 3 "~" H 8550 1650 50  0001 C CNN
	1    8550 1650
	-1   0    0    1   
$EndComp
Wire Wire Line
	9500 1500 9750 1500
Wire Wire Line
	8900 1500 8800 1500
Wire Wire Line
	8800 1500 8800 1550
Wire Wire Line
	8800 1500 8550 1500
Wire Wire Line
	8550 1500 8550 1550
Connection ~ 8800 1500
Wire Wire Line
	9750 1500 9750 1550
Connection ~ 9750 1500
Wire Wire Line
	9200 1800 9200 2000
Wire Wire Line
	9200 2000 9750 2000
Wire Wire Line
	9750 2000 9750 1750
Wire Wire Line
	9200 2000 8800 2000
Wire Wire Line
	8800 2000 8800 1750
Connection ~ 9200 2000
Wire Wire Line
	8800 2000 8550 2000
Wire Wire Line
	8550 2000 8550 1750
Connection ~ 8800 2000
$Comp
L power:GND #PWR0104
U 1 1 61C488DA
P 9200 2150
F 0 "#PWR0104" H 9200 1900 50  0001 C CNN
F 1 "GND" H 9205 1977 50  0000 C CNN
F 2 "" H 9200 2150 50  0001 C CNN
F 3 "" H 9200 2150 50  0001 C CNN
	1    9200 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2000 9200 2150
Wire Wire Line
	6350 5600 6250 5600
Wire Wire Line
	6350 2950 6350 2850
Wire Wire Line
	6350 2850 5450 2850
Wire Wire Line
	5450 2850 5450 2950
$Comp
L power:+3.3V #PWR0105
U 1 1 61C4BE22
P 6700 2850
F 0 "#PWR0105" H 6700 2700 50  0001 C CNN
F 1 "+3.3V" H 6715 3023 50  0000 C CNN
F 2 "" H 6700 2850 50  0001 C CNN
F 3 "" H 6700 2850 50  0001 C CNN
	1    6700 2850
	0    1    1    0   
$EndComp
Wire Wire Line
	6700 2850 6350 2850
Connection ~ 6350 2850
Wire Wire Line
	8550 1500 8350 1500
Connection ~ 8550 1500
Wire Wire Line
	5850 3300 5900 3300
Wire Wire Line
	5900 3300 5900 3550
Wire Wire Line
	5850 3550 5900 3550
Connection ~ 5900 3550
Wire Wire Line
	5900 3550 5900 3850
Wire Wire Line
	4650 5600 4800 5600
Wire Wire Line
	5100 5600 5000 5600
Wire Wire Line
	5100 2950 5100 2850
Wire Wire Line
	5100 2850 4200 2850
Wire Wire Line
	5450 2850 5100 2850
Connection ~ 5100 2850
Wire Wire Line
	5600 5950 5100 5950
Wire Wire Line
	5100 5950 5100 5600
Connection ~ 5100 5600
Wire Wire Line
	5900 3850 5900 4100
Connection ~ 5900 3850
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 61C65DD2
P 4550 5950
F 0 "Q1" H 4741 5996 50  0000 L CNN
F 1 "BC547" H 4741 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4750 5875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4550 5950 50  0001 L CNN
	1    4550 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 61C65DE4
P 4650 6400
F 0 "#PWR0106" H 4650 6150 50  0001 C CNN
F 1 "GND" H 4655 6227 50  0000 C CNN
F 2 "" H 4650 6400 50  0001 C CNN
F 3 "" H 4650 6400 50  0001 C CNN
	1    4650 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 61C65DEA
P 4450 3300
F 0 "D1" V 4489 3183 50  0000 R CNN
F 1 "LED" V 4398 3183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 3300 50  0001 C CNN
F 3 "~" H 4450 3300 50  0001 C CNN
	1    4450 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 61C65DF0
P 4200 3050
F 0 "R1" H 4268 3096 50  0000 L CNN
F 1 "R_Small_US" H 4268 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4200 3050 50  0001 C CNN
F 3 "~" H 4200 3050 50  0001 C CNN
	1    4200 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 61C65DF6
P 4450 3550
F 0 "D2" V 4489 3433 50  0000 R CNN
F 1 "LED" V 4398 3433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 3550 50  0001 C CNN
F 3 "~" H 4450 3550 50  0001 C CNN
	1    4450 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D3
U 1 1 61C65DFC
P 4450 3850
F 0 "D3" V 4489 3733 50  0000 R CNN
F 1 "LED" V 4398 3733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 3850 50  0001 C CNN
F 3 "~" H 4450 3850 50  0001 C CNN
	1    4450 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 5750 4650 5600
Wire Wire Line
	4650 3850 4600 3850
Wire Wire Line
	4650 6150 4650 6400
Wire Wire Line
	4300 3850 4200 3850
Wire Wire Line
	4200 3300 4300 3300
Wire Wire Line
	4300 3550 4200 3550
Connection ~ 4200 3550
Wire Wire Line
	4200 3550 4200 3300
Wire Wire Line
	4200 3300 4200 3150
Connection ~ 4200 3300
Wire Wire Line
	4200 2850 4200 2950
Wire Wire Line
	4600 3300 4650 3300
Wire Wire Line
	4650 3300 4650 3550
Wire Wire Line
	4600 3550 4650 3550
Connection ~ 4650 3550
Wire Wire Line
	4650 3550 4650 3850
Wire Wire Line
	4200 2850 3850 2850
Wire Wire Line
	4350 5950 3850 5950
Wire Wire Line
	4650 3850 4650 4100
Connection ~ 4650 3850
$Comp
L Device:C_Small C1
U 1 1 61C6A2A7
P 4900 5600
F 0 "C1" H 4992 5646 50  0000 L CNN
F 1 "C_Small" H 4992 5555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4900 5600 50  0001 C CNN
F 3 "~" H 4900 5600 50  0001 C CNN
	1    4900 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 61C6B9B7
P 5100 3050
F 0 "R2" H 5168 3096 50  0000 L CNN
F 1 "22K" H 5168 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5100 3050 50  0001 C CNN
F 3 "~" H 5100 3050 50  0001 C CNN
	1    5100 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D8
U 1 1 61C6D452
P 5700 4100
F 0 "D8" V 5739 3983 50  0000 R CNN
F 1 "LED" V 5648 3983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 4100 50  0001 C CNN
F 3 "~" H 5700 4100 50  0001 C CNN
	1    5700 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 4100 5850 4100
Wire Wire Line
	5550 4100 5450 4100
Wire Wire Line
	5450 3550 5450 3850
$Comp
L Device:LED D4
U 1 1 61C6F043
P 4450 4100
F 0 "D4" V 4489 3983 50  0000 R CNN
F 1 "LED" V 4398 3983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 4100 50  0001 C CNN
F 3 "~" H 4450 4100 50  0001 C CNN
	1    4450 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 4100 4600 4100
Wire Wire Line
	4300 4100 4200 4100
Connection ~ 5450 3850
Wire Wire Line
	5450 3850 5450 4100
Wire Wire Line
	4200 3550 4200 3850
Connection ~ 4200 3850
Wire Wire Line
	4200 3850 4200 4100
$Comp
L Device:LED D25
U 1 1 61C8DB90
P 4450 4300
F 0 "D25" V 4489 4183 50  0000 R CNN
F 1 "LED" V 4398 4183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 4300 50  0001 C CNN
F 3 "~" H 4450 4300 50  0001 C CNN
	1    4450 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D26
U 1 1 61C8DB96
P 4450 4550
F 0 "D26" V 4489 4433 50  0000 R CNN
F 1 "LED" V 4398 4433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 4550 50  0001 C CNN
F 3 "~" H 4450 4550 50  0001 C CNN
	1    4450 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D27
U 1 1 61C8DB9C
P 4450 4850
F 0 "D27" V 4489 4733 50  0000 R CNN
F 1 "LED" V 4398 4733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 4850 50  0001 C CNN
F 3 "~" H 4450 4850 50  0001 C CNN
	1    4450 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 4850 4200 4850
Wire Wire Line
	4200 4300 4300 4300
Wire Wire Line
	4300 4550 4200 4550
Connection ~ 4200 4550
Wire Wire Line
	4200 4550 4200 4300
Connection ~ 4200 4300
Wire Wire Line
	4600 4300 4650 4300
Wire Wire Line
	4650 4300 4650 4550
Wire Wire Line
	4600 4550 4650 4550
$Comp
L Device:LED D28
U 1 1 61C8DBB1
P 4450 5100
F 0 "D28" V 4489 4983 50  0000 R CNN
F 1 "LED" V 4398 4983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 4450 5100 50  0001 C CNN
F 3 "~" H 4450 5100 50  0001 C CNN
	1    4450 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 5100 4600 5100
Wire Wire Line
	4300 5100 4200 5100
Wire Wire Line
	4200 4550 4200 4850
Connection ~ 4200 4850
Wire Wire Line
	4200 4850 4200 5100
$Comp
L Device:LED D29
U 1 1 61C91E8E
P 5700 4300
F 0 "D29" V 5739 4183 50  0000 R CNN
F 1 "LED" V 5648 4183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 4300 50  0001 C CNN
F 3 "~" H 5700 4300 50  0001 C CNN
	1    5700 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D30
U 1 1 61C91E94
P 5700 4550
F 0 "D30" V 5739 4433 50  0000 R CNN
F 1 "LED" V 5648 4433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 4550 50  0001 C CNN
F 3 "~" H 5700 4550 50  0001 C CNN
	1    5700 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D31
U 1 1 61C91E9A
P 5700 4850
F 0 "D31" V 5739 4733 50  0000 R CNN
F 1 "LED" V 5648 4733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 4850 50  0001 C CNN
F 3 "~" H 5700 4850 50  0001 C CNN
	1    5700 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 4850 5450 4850
Wire Wire Line
	5450 4300 5550 4300
Wire Wire Line
	5550 4550 5450 4550
Connection ~ 5450 4550
Wire Wire Line
	5450 4550 5450 4300
Connection ~ 5450 4300
Wire Wire Line
	5850 4300 5900 4300
Wire Wire Line
	5900 4300 5900 4550
Wire Wire Line
	5850 4550 5900 4550
$Comp
L Device:LED D32
U 1 1 61C91EAF
P 5700 5100
F 0 "D32" V 5739 4983 50  0000 R CNN
F 1 "LED" V 5648 4983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 5700 5100 50  0001 C CNN
F 3 "~" H 5700 5100 50  0001 C CNN
	1    5700 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 5100 5850 5100
Wire Wire Line
	5550 5100 5450 5100
Wire Wire Line
	5450 4550 5450 4850
Connection ~ 5450 4850
Wire Wire Line
	5450 4850 5450 5100
Wire Wire Line
	5900 4100 5900 4300
Connection ~ 5900 4100
Connection ~ 5900 4300
Wire Wire Line
	5450 4100 5450 4300
Connection ~ 5450 4100
Wire Wire Line
	4650 4100 4650 4300
Connection ~ 4650 4100
Connection ~ 4650 4300
Wire Wire Line
	4200 4100 4200 4300
Connection ~ 4200 4100
Wire Wire Line
	5900 4550 5900 4850
Wire Wire Line
	5900 4850 5850 4850
Connection ~ 5900 4550
Wire Wire Line
	5900 4850 5900 5100
Connection ~ 5900 4850
Wire Wire Line
	5900 5100 5900 5600
Connection ~ 5900 5100
Connection ~ 5900 5600
Wire Wire Line
	4650 5100 4650 4850
Wire Wire Line
	4650 4850 4600 4850
Connection ~ 4650 5100
Wire Wire Line
	4650 4850 4650 4550
Connection ~ 4650 4850
Connection ~ 4650 4550
Wire Wire Line
	4650 5100 4650 5600
Connection ~ 4650 5600
Wire Wire Line
	5100 3150 5100 5600
Wire Wire Line
	6350 3150 6350 5600
Connection ~ 4200 2850
Connection ~ 5450 2850
$Comp
L Transistor_BJT:BC547 Q4
U 1 1 61CFB4A1
P 3300 5950
F 0 "Q4" H 3491 5996 50  0000 L CNN
F 1 "BC547" H 3491 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3500 5875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 3300 5950 50  0001 L CNN
	1    3300 5950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R8
U 1 1 61CFB4A7
P 3850 3050
F 0 "R8" H 3918 3096 50  0000 L CNN
F 1 "R_Small_US" H 3918 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3850 3050 50  0001 C CNN
F 3 "~" H 3850 3050 50  0001 C CNN
	1    3850 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 61CFB4AD
P 3650 5600
F 0 "C7" H 3742 5646 50  0000 L CNN
F 1 "C_Small" H 3742 5555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3650 5600 50  0001 C CNN
F 3 "~" H 3650 5600 50  0001 C CNN
	1    3650 5600
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 61CFB4B3
P 3400 6400
F 0 "#PWR0107" H 3400 6150 50  0001 C CNN
F 1 "GND" H 3405 6227 50  0000 C CNN
F 2 "" H 3400 6400 50  0001 C CNN
F 3 "" H 3400 6400 50  0001 C CNN
	1    3400 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D17
U 1 1 61CFB4B9
P 3200 3300
F 0 "D17" V 3239 3183 50  0000 R CNN
F 1 "LED" V 3148 3183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 3300 50  0001 C CNN
F 3 "~" H 3200 3300 50  0001 C CNN
	1    3200 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R7
U 1 1 61CFB4BF
P 2950 3050
F 0 "R7" H 3018 3096 50  0000 L CNN
F 1 "R_Small_US" H 3018 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2950 3050 50  0001 C CNN
F 3 "~" H 2950 3050 50  0001 C CNN
	1    2950 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D18
U 1 1 61CFB4C5
P 3200 3550
F 0 "D18" V 3239 3433 50  0000 R CNN
F 1 "LED" V 3148 3433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 3550 50  0001 C CNN
F 3 "~" H 3200 3550 50  0001 C CNN
	1    3200 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D19
U 1 1 61CFB4CB
P 3200 3850
F 0 "D19" V 3239 3733 50  0000 R CNN
F 1 "LED" V 3148 3733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 3850 50  0001 C CNN
F 3 "~" H 3200 3850 50  0001 C CNN
	1    3200 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 5750 3400 5600
Wire Wire Line
	3400 3850 3350 3850
Wire Wire Line
	3400 6150 3400 6400
Wire Wire Line
	3400 5600 3550 5600
Wire Wire Line
	3050 3850 2950 3850
Wire Wire Line
	2950 3300 3050 3300
Wire Wire Line
	3050 3550 2950 3550
Connection ~ 2950 3550
Wire Wire Line
	2950 3550 2950 3300
Wire Wire Line
	2950 3300 2950 3150
Connection ~ 2950 3300
Wire Wire Line
	3850 5600 3750 5600
Wire Wire Line
	3850 2950 3850 2850
Wire Wire Line
	3850 2850 2950 2850
Wire Wire Line
	2950 2850 2950 2950
Connection ~ 3850 2850
Wire Wire Line
	3350 3300 3400 3300
Wire Wire Line
	3400 3300 3400 3550
Wire Wire Line
	3350 3550 3400 3550
Connection ~ 3400 3550
Wire Wire Line
	3400 3550 3400 3850
Wire Wire Line
	2150 5600 2300 5600
Wire Wire Line
	2600 5600 2500 5600
Wire Wire Line
	2600 2950 2600 2850
Wire Wire Line
	2600 2850 1700 2850
Wire Wire Line
	2950 2850 2600 2850
Connection ~ 2600 2850
Wire Wire Line
	3100 5950 2600 5950
Wire Wire Line
	2600 5950 2600 5600
Connection ~ 2600 5600
Wire Wire Line
	3400 3850 3400 4100
Connection ~ 3400 3850
$Comp
L Transistor_BJT:BC547 Q3
U 1 1 61CFB4F2
P 2050 5950
F 0 "Q3" H 2241 5996 50  0000 L CNN
F 1 "BC547" H 2241 5905 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2250 5875 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 2050 5950 50  0001 L CNN
	1    2050 5950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 61CFB4F8
P 2150 6400
F 0 "#PWR0108" H 2150 6150 50  0001 C CNN
F 1 "GND" H 2155 6227 50  0000 C CNN
F 2 "" H 2150 6400 50  0001 C CNN
F 3 "" H 2150 6400 50  0001 C CNN
	1    2150 6400
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D9
U 1 1 61CFB4FE
P 1950 3300
F 0 "D9" V 1989 3183 50  0000 R CNN
F 1 "LED" V 1898 3183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 3300 50  0001 C CNN
F 3 "~" H 1950 3300 50  0001 C CNN
	1    1950 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R5
U 1 1 61CFB504
P 1700 3050
F 0 "R5" H 1768 3096 50  0000 L CNN
F 1 "R_Small_US" H 1768 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1700 3050 50  0001 C CNN
F 3 "~" H 1700 3050 50  0001 C CNN
	1    1700 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 61CFB50A
P 1950 3550
F 0 "D10" V 1989 3433 50  0000 R CNN
F 1 "LED" V 1898 3433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 3550 50  0001 C CNN
F 3 "~" H 1950 3550 50  0001 C CNN
	1    1950 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D11
U 1 1 61CFB510
P 1950 3850
F 0 "D11" V 1989 3733 50  0000 R CNN
F 1 "LED" V 1898 3733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 3850 50  0001 C CNN
F 3 "~" H 1950 3850 50  0001 C CNN
	1    1950 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 5750 2150 5600
Wire Wire Line
	2150 3850 2100 3850
Wire Wire Line
	2150 6150 2150 6400
Wire Wire Line
	1800 3850 1700 3850
Wire Wire Line
	1700 3300 1800 3300
Wire Wire Line
	1800 3550 1700 3550
Connection ~ 1700 3550
Wire Wire Line
	1700 3550 1700 3300
Wire Wire Line
	1700 3300 1700 3150
Connection ~ 1700 3300
Wire Wire Line
	1700 2850 1700 2950
Wire Wire Line
	2100 3300 2150 3300
Wire Wire Line
	2150 3300 2150 3550
Wire Wire Line
	2100 3550 2150 3550
Connection ~ 2150 3550
Wire Wire Line
	2150 3550 2150 3850
Wire Wire Line
	1700 2850 1350 2850
Wire Wire Line
	1850 5950 1350 5950
Wire Wire Line
	2150 3850 2150 4100
Connection ~ 2150 3850
$Comp
L Device:C_Small C6
U 1 1 61CFB52A
P 2400 5600
F 0 "C6" H 2492 5646 50  0000 L CNN
F 1 "C_Small" H 2492 5555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2400 5600 50  0001 C CNN
F 3 "~" H 2400 5600 50  0001 C CNN
	1    2400 5600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R6
U 1 1 61CFB530
P 2600 3050
F 0 "R6" H 2668 3096 50  0000 L CNN
F 1 "R_Small_US" H 2668 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 2600 3050 50  0001 C CNN
F 3 "~" H 2600 3050 50  0001 C CNN
	1    2600 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D20
U 1 1 61CFB536
P 3200 4100
F 0 "D20" V 3239 3983 50  0000 R CNN
F 1 "LED" V 3148 3983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 4100 50  0001 C CNN
F 3 "~" H 3200 4100 50  0001 C CNN
	1    3200 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 4100 3350 4100
Wire Wire Line
	3050 4100 2950 4100
Wire Wire Line
	2950 3550 2950 3850
$Comp
L Device:LED D12
U 1 1 61CFB53F
P 1950 4100
F 0 "D12" V 1989 3983 50  0000 R CNN
F 1 "LED" V 1898 3983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 4100 50  0001 C CNN
F 3 "~" H 1950 4100 50  0001 C CNN
	1    1950 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 4100 2100 4100
Wire Wire Line
	1800 4100 1700 4100
Connection ~ 2950 3850
Wire Wire Line
	2950 3850 2950 4100
Wire Wire Line
	1700 3550 1700 3850
Connection ~ 1700 3850
Wire Wire Line
	1700 3850 1700 4100
$Comp
L Device:LED D13
U 1 1 61CFB54C
P 1950 4300
F 0 "D13" V 1989 4183 50  0000 R CNN
F 1 "LED" V 1898 4183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 4300 50  0001 C CNN
F 3 "~" H 1950 4300 50  0001 C CNN
	1    1950 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D14
U 1 1 61CFB552
P 1950 4550
F 0 "D14" V 1989 4433 50  0000 R CNN
F 1 "LED" V 1898 4433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 4550 50  0001 C CNN
F 3 "~" H 1950 4550 50  0001 C CNN
	1    1950 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D15
U 1 1 61CFB558
P 1950 4850
F 0 "D15" V 1989 4733 50  0000 R CNN
F 1 "LED" V 1898 4733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 4850 50  0001 C CNN
F 3 "~" H 1950 4850 50  0001 C CNN
	1    1950 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	1800 4850 1700 4850
Wire Wire Line
	1700 4300 1800 4300
Wire Wire Line
	1800 4550 1700 4550
Connection ~ 1700 4550
Wire Wire Line
	1700 4550 1700 4300
Connection ~ 1700 4300
Wire Wire Line
	2100 4300 2150 4300
Wire Wire Line
	2150 4300 2150 4550
Wire Wire Line
	2100 4550 2150 4550
$Comp
L Device:LED D16
U 1 1 61CFB567
P 1950 5100
F 0 "D16" V 1989 4983 50  0000 R CNN
F 1 "LED" V 1898 4983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 1950 5100 50  0001 C CNN
F 3 "~" H 1950 5100 50  0001 C CNN
	1    1950 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 5100 2100 5100
Wire Wire Line
	1800 5100 1700 5100
Wire Wire Line
	1700 4550 1700 4850
Connection ~ 1700 4850
Wire Wire Line
	1700 4850 1700 5100
$Comp
L Device:LED D21
U 1 1 61CFB572
P 3200 4300
F 0 "D21" V 3239 4183 50  0000 R CNN
F 1 "LED" V 3148 4183 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 4300 50  0001 C CNN
F 3 "~" H 3200 4300 50  0001 C CNN
	1    3200 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D22
U 1 1 61CFB578
P 3200 4550
F 0 "D22" V 3239 4433 50  0000 R CNN
F 1 "LED" V 3148 4433 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 4550 50  0001 C CNN
F 3 "~" H 3200 4550 50  0001 C CNN
	1    3200 4550
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D23
U 1 1 61CFB57E
P 3200 4850
F 0 "D23" V 3239 4733 50  0000 R CNN
F 1 "LED" V 3148 4733 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 4850 50  0001 C CNN
F 3 "~" H 3200 4850 50  0001 C CNN
	1    3200 4850
	-1   0    0    1   
$EndComp
Wire Wire Line
	3050 4850 2950 4850
Wire Wire Line
	2950 4300 3050 4300
Wire Wire Line
	3050 4550 2950 4550
Connection ~ 2950 4550
Wire Wire Line
	2950 4550 2950 4300
Connection ~ 2950 4300
Wire Wire Line
	3350 4300 3400 4300
Wire Wire Line
	3400 4300 3400 4550
Wire Wire Line
	3350 4550 3400 4550
$Comp
L Device:LED D24
U 1 1 61CFB58D
P 3200 5100
F 0 "D24" V 3239 4983 50  0000 R CNN
F 1 "LED" V 3148 4983 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric_Castellated" H 3200 5100 50  0001 C CNN
F 3 "~" H 3200 5100 50  0001 C CNN
	1    3200 5100
	-1   0    0    1   
$EndComp
Wire Wire Line
	3400 5100 3350 5100
Wire Wire Line
	3050 5100 2950 5100
Wire Wire Line
	2950 4550 2950 4850
Connection ~ 2950 4850
Wire Wire Line
	2950 4850 2950 5100
Wire Wire Line
	3400 4100 3400 4300
Connection ~ 3400 4100
Connection ~ 3400 4300
Wire Wire Line
	2950 4100 2950 4300
Connection ~ 2950 4100
Wire Wire Line
	2150 4100 2150 4300
Connection ~ 2150 4100
Connection ~ 2150 4300
Wire Wire Line
	1700 4100 1700 4300
Connection ~ 1700 4100
Wire Wire Line
	3400 4550 3400 4850
Wire Wire Line
	3400 4850 3350 4850
Connection ~ 3400 4550
Wire Wire Line
	3400 4850 3400 5100
Connection ~ 3400 4850
Wire Wire Line
	3400 5100 3400 5600
Connection ~ 3400 5100
Connection ~ 3400 5600
Wire Wire Line
	2150 5100 2150 4850
Wire Wire Line
	2150 4850 2100 4850
Connection ~ 2150 5100
Wire Wire Line
	2150 4850 2150 4550
Connection ~ 2150 4850
Connection ~ 2150 4550
Wire Wire Line
	2150 5100 2150 5600
Connection ~ 2150 5600
Wire Wire Line
	2600 3150 2600 5600
Wire Wire Line
	3850 3150 3850 5600
Connection ~ 1700 2850
Connection ~ 2950 2850
Wire Wire Line
	3850 5950 3850 5600
Connection ~ 3850 5600
Wire Wire Line
	1350 2850 1350 5950
Wire Notes Line
	7950 500  7950 2550
Wire Notes Line
	7950 2550 11150 2550
Wire Notes Line
	11150 2550 11150 500 
Wire Notes Line
	11150 500  7950 500 
$Comp
L Device:Fuse F1
U 1 1 61D3E481
P 10250 1500
F 0 "F1" V 10053 1500 50  0000 C CNN
F 1 "Fuse" V 10144 1500 50  0000 C CNN
F 2 "" V 10180 1500 50  0001 C CNN
F 3 "~" H 10250 1500 50  0001 C CNN
	1    10250 1500
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D33
U 1 1 61D3F41E
P 10000 1750
F 0 "D33" V 9954 1829 50  0000 L CNN
F 1 "D_Zener" V 10045 1829 50  0000 L CNN
F 2 "" H 10000 1750 50  0001 C CNN
F 3 "~" H 10000 1750 50  0001 C CNN
	1    10000 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	9750 1500 10000 1500
Wire Wire Line
	10000 1500 10000 1600
Connection ~ 10000 1500
Wire Wire Line
	10000 1500 10100 1500
Wire Wire Line
	9750 2000 10000 2000
Wire Wire Line
	10000 2000 10000 1900
Connection ~ 9750 2000
Wire Wire Line
	10550 1500 10400 1500
$EndSCHEMATC
