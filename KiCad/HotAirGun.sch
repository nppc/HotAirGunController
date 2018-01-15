EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:KiCadCustomLibraries
LIBS:HotAirGun-cache
EELAYER 25 0
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
L Conn_01x02 Fan1
U 1 1 59B297ED
P 4000 2350
F 0 "Fan1" H 4000 2450 50  0000 C CNN
F 1 "Fan" H 4200 2300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 4000 2350 50  0001 C CNN
F 3 "" H 4000 2350 50  0001 C CNN
	1    4000 2350
	-1   0    0    1   
$EndComp
$Comp
L Q_NMOS_GSD Q2
U 1 1 59B2A260
P 4300 2650
F 0 "Q2" H 4500 2700 50  0000 L CNN
F 1 "SI2308" H 4500 2600 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4500 2750 50  0001 C CNN
F 3 "" H 4300 2650 50  0001 C CNN
	1    4300 2650
	-1   0    0    -1  
$EndComp
$Comp
L Conn_01x02 TEMP1
U 1 1 59B2A3BB
P 1050 5500
F 0 "TEMP1" H 1050 5600 50  0000 C CNN
F 1 "Temp sensor" H 1350 5450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 1050 5500 50  0001 C CNN
F 3 "" H 1050 5500 50  0001 C CNN
	1    1050 5500
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 5A1FE630
P 4400 3000
F 0 "R3" V 4480 3000 50  0000 C CNN
F 1 "10K" V 4400 3000 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4330 3000 50  0001 C CNN
F 3 "" H 4400 3000 50  0001 C CNN
	1    4400 3000
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 5A1FE79F
P 4750 2650
F 0 "R5" V 4830 2650 50  0000 C CNN
F 1 "100" V 4750 2650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 4680 2650 50  0001 C CNN
F 3 "" H 4750 2650 50  0001 C CNN
	1    4750 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 2350 4200 2450
Wire Wire Line
	4500 2650 4600 2650
Wire Wire Line
	4550 2650 4550 3000
Connection ~ 4550 2650
Wire Wire Line
	4250 3000 4200 3000
Wire Wire Line
	4200 2850 4200 3100
$Comp
L GND #PWR7
U 1 1 5A1FEF82
P 4200 3100
F 0 "#PWR7" H 4200 2850 50  0001 C CNN
F 1 "GND" H 4200 2950 50  0000 C CNN
F 2 "" H 4200 3100 50  0001 C CNN
F 3 "" H 4200 3100 50  0001 C CNN
	1    4200 3100
	1    0    0    -1  
$EndComp
Connection ~ 4200 3000
$Comp
L Arduino_Nano_Header J4
U 1 1 5A1FFBDE
P 6250 3550
F 0 "J4" H 6250 4350 60  0000 C CNN
F 1 "Arduino_Nano_Header" H 6250 2750 60  0000 C CNN
F 2 "Modules:Arduino_Nano" H 6450 2650 60  0001 C CNN
F 3 "" H 6250 3550 60  0000 C CNN
	1    6250 3550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR16
U 1 1 5A1FFE27
P 6900 3150
F 0 "#PWR16" H 6900 3000 50  0001 C CNN
F 1 "VCC" H 6900 3290 50  0000 C CNN
F 2 "" H 6900 3150 50  0001 C CNN
F 3 "" H 6900 3150 50  0001 C CNN
	1    6900 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3150 6900 3150
Wire Wire Line
	4900 2650 5200 2650
$Comp
L GND #PWR11
U 1 1 5A20085B
P 5300 3150
F 0 "#PWR11" H 5300 2900 50  0001 C CNN
F 1 "GND" H 5300 3000 50  0000 C CNN
F 2 "" H 5300 3150 50  0001 C CNN
F 3 "" H 5300 3150 50  0001 C CNN
	1    5300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3150 5900 3150
$Comp
L GND #PWR14
U 1 1 5A2009BC
P 6700 2950
F 0 "#PWR14" H 6700 2700 50  0001 C CNN
F 1 "GND" H 6700 2800 50  0000 C CNN
F 2 "" H 6700 2950 50  0001 C CNN
F 3 "" H 6700 2950 50  0001 C CNN
	1    6700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2950 6700 2950
Text Label 5200 2650 2    60   ~ 0
Fan
$Comp
L Conn_01x04 LCD1
U 1 1 5A201342
P 7500 3550
F 0 "LCD1" H 7500 3750 50  0000 C CNN
F 1 "LCD" H 7500 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 7500 3550 50  0001 C CNN
F 3 "" H 7500 3550 50  0001 C CNN
	1    7500 3550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR18
U 1 1 5A201514
P 7300 3750
F 0 "#PWR18" H 7300 3500 50  0001 C CNN
F 1 "GND" H 7300 3600 50  0000 C CNN
F 2 "" H 7300 3750 50  0001 C CNN
F 3 "" H 7300 3750 50  0001 C CNN
	1    7300 3750
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR17
U 1 1 5A201552
P 7100 3650
F 0 "#PWR17" H 7100 3500 50  0001 C CNN
F 1 "VCC" H 7100 3790 50  0000 C CNN
F 2 "" H 7100 3650 50  0001 C CNN
F 3 "" H 7100 3650 50  0001 C CNN
	1    7100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3650 7300 3650
Wire Wire Line
	6600 3450 7200 3450
Wire Wire Line
	7200 3450 7200 3550
Wire Wire Line
	7200 3550 7300 3550
Wire Wire Line
	6600 3550 6950 3550
Wire Wire Line
	6950 3550 6950 3400
Wire Wire Line
	6950 3400 7300 3400
Wire Wire Line
	7300 3400 7300 3450
$Comp
L Rotary_Encoder_Switch SW1
U 1 1 5A203BA2
P 4750 3850
F 0 "SW1" H 4750 4110 50  0000 C CNN
F 1 "Rotary_Encoder" H 4750 4250 50  0000 C CNN
F 2 "KiCadCustomLibs:SF-ROTARY-ENCODER" H 4650 4010 50  0001 C CNN
F 3 "" H 4750 4110 50  0001 C CNN
	1    4750 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5050 3750 5400 3750
Wire Wire Line
	5400 3750 5400 3350
Wire Wire Line
	5400 3350 5900 3350
Wire Wire Line
	5050 3950 5500 3950
Wire Wire Line
	5500 3450 5500 4350
Wire Wire Line
	5500 3450 5900 3450
$Comp
L GND #PWR8
U 1 1 5A203FE0
P 4300 3750
F 0 "#PWR8" H 4300 3500 50  0001 C CNN
F 1 "GND" H 4300 3600 50  0000 C CNN
F 2 "" H 4300 3750 50  0001 C CNN
F 3 "" H 4300 3750 50  0001 C CNN
	1    4300 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR9
U 1 1 5A204015
P 5150 4050
F 0 "#PWR9" H 5150 3800 50  0001 C CNN
F 1 "GND" H 5150 3900 50  0000 C CNN
F 2 "" H 5150 4050 50  0001 C CNN
F 3 "" H 5150 4050 50  0001 C CNN
	1    5150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 3850 5150 3850
Wire Wire Line
	5150 3850 5150 4050
Wire Wire Line
	5900 3650 5600 3650
Text Label 5600 3950 0    60   ~ 0
Fan
Wire Wire Line
	4300 3750 4450 3750
Wire Wire Line
	4450 3950 4450 4250
Wire Wire Line
	4450 4250 5900 4250
$Comp
L C_Small C1
U 1 1 5A2120D3
P 5100 4450
F 0 "C1" H 5110 4520 50  0000 L CNN
F 1 "10n" H 5110 4370 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5100 4450 50  0001 C CNN
F 3 "" H 5100 4450 50  0001 C CNN
	1    5100 4450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C3
U 1 1 5A2121CD
P 5500 4450
F 0 "C3" H 5510 4520 50  0000 L CNN
F 1 "10n" H 5510 4370 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5500 4450 50  0001 C CNN
F 3 "" H 5500 4450 50  0001 C CNN
	1    5500 4450
	1    0    0    -1  
$EndComp
$Comp
L C_Small C2
U 1 1 5A21222B
P 5300 4450
F 0 "C2" H 5310 4520 50  0000 L CNN
F 1 "10n" H 5310 4370 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5300 4450 50  0001 C CNN
F 3 "" H 5300 4450 50  0001 C CNN
	1    5300 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4350 5100 4250
Connection ~ 5100 4250
Wire Wire Line
	5300 4350 5300 3750
Connection ~ 5300 3750
Connection ~ 5500 3950
Wire Wire Line
	5100 4550 5100 4600
Wire Wire Line
	5100 4600 5500 4600
Wire Wire Line
	5300 4600 5300 4550
Wire Wire Line
	5500 4600 5500 4550
Connection ~ 5300 4600
$Comp
L GND #PWR12
U 1 1 5A2126AB
P 5300 4600
F 0 "#PWR12" H 5300 4350 50  0001 C CNN
F 1 "GND" H 5300 4450 50  0000 C CNN
F 2 "" H 5300 4600 50  0001 C CNN
F 3 "" H 5300 4600 50  0001 C CNN
	1    5300 4600
	1    0    0    -1  
$EndComp
$Comp
L MAX31855KASA U1
U 1 1 5A5CA738
P 2000 5450
F 0 "U1" H 1700 5800 50  0000 L CNN
F 1 "MAX31855K" H 2050 5800 50  0000 L CNN
F 2 "Housings_SOIC:SOIC-8_3.9x4.9mm_Pitch1.27mm" H 3000 5100 50  0001 C CIN
F 3 "" H 2000 5450 50  0001 C CNN
	1    2000 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5A5CA92C
P 2000 5850
F 0 "#PWR3" H 2000 5600 50  0001 C CNN
F 1 "GND" H 2000 5700 50  0000 C CNN
F 2 "" H 2000 5850 50  0001 C CNN
F 3 "" H 2000 5850 50  0001 C CNN
	1    2000 5850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR2
U 1 1 5A5CA9B9
P 2000 4900
F 0 "#PWR2" H 2000 4750 50  0001 C CNN
F 1 "+3.3V" H 2000 5040 50  0000 C CNN
F 2 "" H 2000 4900 50  0001 C CNN
F 3 "" H 2000 4900 50  0001 C CNN
	1    2000 4900
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR15
U 1 1 5A5CA9FB
P 6750 4150
F 0 "#PWR15" H 6750 4000 50  0001 C CNN
F 1 "+3.3V" H 6750 4290 50  0000 C CNN
F 2 "" H 6750 4150 50  0001 C CNN
F 3 "" H 6750 4150 50  0001 C CNN
	1    6750 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 4150 6600 4150
$Comp
L C_Small C5
U 1 1 5A5CB2BA
P 1400 5450
F 0 "C5" H 1500 5450 50  0000 L CNN
F 1 "10n" H 1350 5250 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1400 5450 50  0001 C CNN
F 3 "" H 1400 5450 50  0001 C CNN
	1    1400 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 4900 2000 5050
$Comp
L C_Small C6
U 1 1 5A5CB920
P 1450 5000
F 0 "C6" H 1400 5200 50  0000 L CNN
F 1 "100n" H 1400 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1450 5000 50  0001 C CNN
F 3 "" H 1450 5000 50  0001 C CNN
	1    1450 5000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C4
U 1 1 5A5CBAC7
P 1150 5000
F 0 "C4" H 1100 5200 50  0000 L CNN
F 1 "10uf" H 1050 4850 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 1150 5000 50  0001 C CNN
F 3 "" H 1150 5000 50  0001 C CNN
	1    1150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 4900 2000 4900
Connection ~ 1450 4900
Connection ~ 2000 4900
Wire Wire Line
	1150 5100 1450 5100
$Comp
L GND #PWR1
U 1 1 5A5CBE64
P 1300 5100
F 0 "#PWR1" H 1300 4850 50  0001 C CNN
F 1 "GND" H 1300 4950 50  0000 C CNN
F 2 "" H 1300 5100 50  0001 C CNN
F 3 "" H 1300 5100 50  0001 C CNN
	1    1300 5100
	1    0    0    -1  
$EndComp
Connection ~ 1300 5100
Wire Wire Line
	1250 5400 1250 5350
Wire Wire Line
	1250 5350 1600 5350
Connection ~ 1400 5350
Wire Wire Line
	1250 5500 1250 5550
Wire Wire Line
	1250 5550 1600 5550
Connection ~ 1400 5550
$Comp
L D D1
U 1 1 5A5CCAA5
P 2850 5150
F 0 "D1" H 2850 5250 50  0000 C CNN
F 1 "1n4148w" H 2850 5050 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-523" H 2850 5150 50  0001 C CNN
F 3 "" H 2850 5150 50  0001 C CNN
	1    2850 5150
	-1   0    0    1   
$EndComp
$Comp
L D D2
U 1 1 5A5CCE46
P 2850 5550
F 0 "D2" H 2850 5650 50  0000 C CNN
F 1 "1n4148w" H 2850 5450 50  0000 C CNN
F 2 "Diodes_SMD:D_SOD-523" H 2850 5550 50  0001 C CNN
F 3 "" H 2850 5550 50  0001 C CNN
	1    2850 5550
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 5250 2400 5250
Wire Wire Line
	2550 5050 2550 5250
Wire Wire Line
	2550 5150 2700 5150
Wire Wire Line
	2400 5550 2700 5550
Wire Wire Line
	2400 5350 3400 5350
Wire Wire Line
	3000 5150 3400 5150
Wire Wire Line
	3000 5550 3400 5550
$Comp
L R R1
U 1 1 5A5CD116
P 2550 4900
F 0 "R1" V 2630 4900 50  0000 C CNN
F 1 "10K" V 2550 4900 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2480 4900 50  0001 C CNN
F 3 "" H 2550 4900 50  0001 C CNN
	1    2550 4900
	-1   0    0    1   
$EndComp
Connection ~ 2550 5150
$Comp
L +3.3V #PWR4
U 1 1 5A5CD38D
P 2550 4750
F 0 "#PWR4" H 2550 4600 50  0001 C CNN
F 1 "+3.3V" H 2550 4890 50  0000 C CNN
F 2 "" H 2550 4750 50  0001 C CNN
F 3 "" H 2550 4750 50  0001 C CNN
	1    2550 4750
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A5CD3DA
P 2550 5800
F 0 "R2" V 2630 5800 50  0000 C CNN
F 1 "10K" V 2550 5800 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 2480 5800 50  0001 C CNN
F 3 "" H 2550 5800 50  0001 C CNN
	1    2550 5800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2550 5650 2550 5550
Connection ~ 2550 5550
$Comp
L +3.3V #PWR5
U 1 1 5A5CD5F1
P 2550 5950
F 0 "#PWR5" H 2550 5800 50  0001 C CNN
F 1 "+3.3V" H 2550 6090 50  0000 C CNN
F 2 "" H 2550 5950 50  0001 C CNN
F 3 "" H 2550 5950 50  0001 C CNN
	1    2550 5950
	-1   0    0    1   
$EndComp
Text Label 3400 5150 2    60   ~ 0
T_SCK
Text Label 3400 5350 2    60   ~ 0
T_SO
Text Label 3400 5550 2    60   ~ 0
T_CS
$Comp
L GND #PWR10
U 1 1 5A5D11C3
P 5300 1850
F 0 "#PWR10" H 5300 1600 50  0001 C CNN
F 1 "GND" H 5300 1700 50  0000 C CNN
F 2 "" H 5300 1850 50  0001 C CNN
F 3 "" H 5300 1850 50  0001 C CNN
	1    5300 1850
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5A5D1294
P 5550 2200
F 0 "R4" V 5630 2200 50  0000 C CNN
F 1 "680" V 5550 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0603" V 5480 2200 50  0001 C CNN
F 3 "" H 5550 2200 50  0001 C CNN
	1    5550 2200
	-1   0    0    1   
$EndComp
Wire Wire Line
	5550 1850 5550 2050
Wire Wire Line
	5550 2350 5550 2650
Text Label 5550 2650 1    60   ~ 0
Heater
Text Label 6900 3850 2    60   ~ 0
Heater
Text Label 5600 3850 0    60   ~ 0
T_SCK
Wire Wire Line
	5900 3950 5600 3950
Text Label 5600 3650 0    60   ~ 0
T_SO
Text Label 5600 3750 0    60   ~ 0
T_CS
$Comp
L Conn_01x01 Heater_pos1
U 1 1 5A2130CC
P 5550 1650
F 0 "Heater_pos1" H 5850 1650 50  0000 C CNN
F 1 "HEAT" H 5550 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x01_Pitch2.54mm" H 5550 1650 50  0001 C CNN
F 3 "" H 5550 1650 50  0001 C CNN
	1    5550 1650
	0    -1   -1   0   
$EndComp
$Comp
L +24V #PWR6
U 1 1 5A5D49AD
P 4200 2250
F 0 "#PWR6" H 4200 2100 50  0001 C CNN
F 1 "+24V" H 4200 2390 50  0000 C CNN
F 2 "" H 4200 2250 50  0001 C CNN
F 3 "" H 4200 2250 50  0001 C CNN
	1    4200 2250
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 Heater_neg1
U 1 1 5A5D4EE3
P 5300 1650
F 0 "Heater_neg1" H 5600 1650 50  0000 C CNN
F 1 "HEAT" H 5300 1550 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x01_Pitch2.54mm" H 5300 1650 50  0001 C CNN
F 3 "" H 5300 1650 50  0001 C CNN
	1    5300 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 3850 6900 3850
Wire Wire Line
	5900 3750 5600 3750
Wire Wire Line
	5900 3850 5600 3850
$EndSCHEMATC
