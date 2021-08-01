EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5950 1800 5950 1700
Wire Wire Line
	5250 3700 5250 3500
Wire Wire Line
	5550 3700 5550 3500
Wire Wire Line
	5450 3700 5450 3500
Text GLabel 5650 3900 3    50   Input ~ 0
12_MISO
Text GLabel 5550 3700 3    50   Input ~ 0
Ground
Text GLabel 5950 1700 2    50   Input ~ 0
Ground
Text GLabel 5150 3700 3    50   Input ~ 0
10_CS
Text GLabel 5250 3700 3    50   Input ~ 0
11_MOSI
Wire Wire Line
	5650 3500 5650 3900
Wire Wire Line
	5150 3500 5150 3700
Text GLabel 5350 3750 3    50   Input ~ 0
3.3V
Wire Wire Line
	5350 3500 5350 3750
$Comp
L Device:C C12
U 1 1 5E66571C
P 5100 4500
F 0 "C12" H 5215 4546 50  0000 L CNN
F 1 "10u" H 5215 4455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5138 4350 50  0001 C CNN
F 3 "~" H 5100 4500 50  0001 C CNN
	1    5100 4500
	1    0    0    -1  
$EndComp
Text GLabel 5100 4200 0    50   Input ~ 0
3.3V
Text GLabel 5100 4800 0    50   Input ~ 0
Ground
Wire Wire Line
	5100 4800 5100 4650
Wire Wire Line
	5100 4200 5100 4350
Text GLabel 5450 3700 3    50   Input ~ 0
27_A13
$Comp
L Connector:Micro_SD_Card SDcard?
U 1 1 5DFCE3F6
P 5350 2600
AR Path="/5DFCE3F6" Ref="SDcard?"  Part="1" 
AR Path="/5DFCB53C/5DFCE3F6" Ref="SDcard1"  Part="1" 
AR Path="/5DE8C4DF/5DFCE3F6" Ref="SDcard1"  Part="1" 
F 0 "SDcard1" H 5300 3317 50  0000 C CNN
F 1 "Micro_SD_Card" H 5300 3226 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3D-SF" H 6500 2900 50  0001 C CNN
F 3 "http://katalog.we-online.de/em/datasheet/693072010801.pdf" H 5350 2600 50  0001 C CNN
	1    5350 2600
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
