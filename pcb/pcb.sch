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
L Driver_Motor:L293D U1
U 1 1 5FBAA003
P 6100 3000
F 0 "U1" H 6100 4181 50  0000 C CNN
F 1 "L293D" H 6100 4090 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 6350 2250 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/l293.pdf" H 5800 3700 50  0001 C CNN
	1    6100 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3800 6300 3950
Wire Wire Line
	6200 3800 6200 3950
Wire Wire Line
	6200 3950 6300 3950
$Comp
L power:+5V #PWR0103
U 1 1 5FBB901E
P 6000 1700
F 0 "#PWR0103" H 6000 1550 50  0001 C CNN
F 1 "+5V" H 6015 1873 50  0000 C CNN
F 2 "" H 6000 1700 50  0001 C CNN
F 3 "" H 6000 1700 50  0001 C CNN
	1    6000 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0105
U 1 1 5FBBA74E
P 5400 3400
F 0 "#PWR0105" H 5400 3250 50  0001 C CNN
F 1 "+5V" H 5415 3573 50  0000 C CNN
F 2 "" H 5400 3400 50  0001 C CNN
F 3 "" H 5400 3400 50  0001 C CNN
	1    5400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3400 5600 3400
Wire Wire Line
	6000 1700 6000 1850
Wire Wire Line
	6200 2000 6200 1850
Wire Wire Line
	6200 1850 6000 1850
Connection ~ 6000 1850
Wire Wire Line
	6000 1850 6000 2000
Text GLabel 1850 2200 0    50   Input ~ 0
M1_neg
Text GLabel 1850 2000 0    50   Input ~ 0
M1_pos
Text GLabel 1850 2300 0    50   Input ~ 0
M2_pos
Text GLabel 1850 2600 0    50   Input ~ 0
M2_neg
Wire Wire Line
	1850 2000 2100 2000
Wire Wire Line
	1850 2200 2100 2200
Wire Wire Line
	1850 2300 2100 2300
Wire Wire Line
	1850 2600 2100 2600
Text GLabel 5150 2500 0    50   Input ~ 0
M1_neg
Text GLabel 5150 2400 0    50   Input ~ 0
M1_pos
Text GLabel 5150 3000 0    50   Input ~ 0
M2_pos
Text GLabel 5150 3100 0    50   Input ~ 0
M2_neg
Wire Wire Line
	5150 2400 5600 2400
Wire Wire Line
	5150 2500 5600 2500
Wire Wire Line
	5600 2500 5600 2600
Wire Wire Line
	5150 3000 5600 3000
Wire Wire Line
	5150 3100 5600 3100
Wire Wire Line
	5600 3100 5600 3200
$Comp
L MX_Alps_Hybrid:MX-LED MX1
U 1 1 5FBCC34C
P 2250 4800
F 0 "MX1" H 2332 5024 60  0000 C CNN
F 1 "MX-LED" H 2332 4950 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1625 4775 60  0001 C CNN
F 3 "" H 1625 4775 60  0001 C CNN
	1    2250 4800
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX2
U 1 1 5FBCD95B
P 2800 4800
F 0 "MX2" H 2882 5024 60  0000 C CNN
F 1 "MX-LED" H 2882 4950 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2175 4775 60  0001 C CNN
F 3 "" H 2175 4775 60  0001 C CNN
	1    2800 4800
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX3
U 1 1 5FBCDFF2
P 2250 5500
F 0 "MX3" H 2332 5724 60  0000 C CNN
F 1 "MX-LED" H 2332 5650 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1625 5475 60  0001 C CNN
F 3 "" H 1625 5475 60  0001 C CNN
	1    2250 5500
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX4
U 1 1 5FBCEADF
P 2800 5500
F 0 "MX4" H 2882 5724 60  0000 C CNN
F 1 "MX-LED" H 2882 5650 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2175 5475 60  0001 C CNN
F 3 "" H 2175 5475 60  0001 C CNN
	1    2800 5500
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX5
U 1 1 5FBCF3A4
P 2250 6300
F 0 "MX5" H 2332 6524 60  0000 C CNN
F 1 "MX-LED" H 2332 6450 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1625 6275 60  0001 C CNN
F 3 "" H 1625 6275 60  0001 C CNN
	1    2250 6300
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX6
U 1 1 5FBCF943
P 2800 6300
F 0 "MX6" H 2882 6524 60  0000 C CNN
F 1 "MX-LED" H 2882 6450 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2175 6275 60  0001 C CNN
F 3 "" H 2175 6275 60  0001 C CNN
	1    2800 6300
	1    0    0    -1  
$EndComp
Text GLabel 1900 4950 0    50   Input ~ 0
key_row1
Text GLabel 1900 5650 0    50   Input ~ 0
key_row2
Text GLabel 1900 6450 0    50   Input ~ 0
key_row3
Text GLabel 2400 3950 0    50   Input ~ 0
key_col1
Text GLabel 2950 3950 0    50   Input ~ 0
key_col2
Wire Wire Line
	1900 4950 2200 4950
Wire Wire Line
	2200 4950 2750 4950
Connection ~ 2200 4950
Wire Wire Line
	1900 5650 2200 5650
Wire Wire Line
	2200 5650 2750 5650
Connection ~ 2200 5650
Wire Wire Line
	1900 6450 2200 6450
Wire Wire Line
	2200 6450 2750 6450
Connection ~ 2200 6450
Wire Wire Line
	2400 4750 2400 5450
Wire Wire Line
	2400 5450 2400 6250
Connection ~ 2400 5450
Wire Wire Line
	2950 4750 2950 5450
Wire Wire Line
	2950 5450 2950 6250
Connection ~ 2950 5450
Text GLabel 3200 2300 2    50   Input ~ 0
key_row1
Text GLabel 3200 2400 2    50   Input ~ 0
key_row2
Text GLabel 3200 2500 2    50   Input ~ 0
key_row3
Wire Wire Line
	3200 2300 3000 2300
Text GLabel 1850 2400 0    50   Input ~ 0
key_col1
Text GLabel 1850 2500 0    50   Input ~ 0
key_col2
Wire Wire Line
	2100 2400 1850 2400
Wire Wire Line
	2100 2500 1850 2500
NoConn ~ 2350 4800
NoConn ~ 2250 4900
NoConn ~ 2900 4800
NoConn ~ 2800 4900
NoConn ~ 2900 5500
NoConn ~ 2800 5600
NoConn ~ 2350 5500
NoConn ~ 2250 5600
NoConn ~ 2350 6300
NoConn ~ 2250 6400
NoConn ~ 2800 6400
NoConn ~ 2900 6300
$Comp
L power:Earth #PWR0101
U 1 1 5FC0CB14
P 6300 3950
F 0 "#PWR0101" H 6300 3700 50  0001 C CNN
F 1 "Earth" H 6300 3800 50  0001 C CNN
F 2 "" H 6300 3950 50  0001 C CNN
F 3 "~" H 6300 3950 50  0001 C CNN
	1    6300 3950
	1    0    0    -1  
$EndComp
Connection ~ 6300 3950
Wire Wire Line
	6000 3950 5900 3950
Wire Wire Line
	6000 3800 6000 3950
Wire Wire Line
	5900 3800 5900 3950
$Comp
L power:Earth #PWR0102
U 1 1 5FC0F60F
P 5900 3950
F 0 "#PWR0102" H 5900 3700 50  0001 C CNN
F 1 "Earth" H 5900 3800 50  0001 C CNN
F 2 "" H 5900 3950 50  0001 C CNN
F 3 "~" H 5900 3950 50  0001 C CNN
	1    5900 3950
	1    0    0    -1  
$EndComp
Connection ~ 5900 3950
Text GLabel 8400 2200 2    50   Input ~ 0
fader1
$Comp
L power:+5V #PWR0108
U 1 1 5FBDE070
P 8150 1900
F 0 "#PWR0108" H 8150 1750 50  0001 C CNN
F 1 "+5V" H 8165 2073 50  0000 C CNN
F 2 "" H 8150 1900 50  0001 C CNN
F 3 "" H 8150 1900 50  0001 C CNN
	1    8150 1900
	1    0    0    -1  
$EndComp
Text GLabel 8400 3750 2    50   Input ~ 0
fader2
$Comp
L power:+5V #PWR0110
U 1 1 5FBE2BF3
P 8150 3450
F 0 "#PWR0110" H 8150 3300 50  0001 C CNN
F 1 "+5V" H 8165 3623 50  0000 C CNN
F 2 "" H 8150 3450 50  0001 C CNN
F 3 "" H 8150 3450 50  0001 C CNN
	1    8150 3450
	1    0    0    -1  
$EndComp
Text GLabel 3200 2100 2    50   Input ~ 0
fader1
Text GLabel 3200 2200 2    50   Input ~ 0
fader2
$Comp
L power:+5V #PWR0111
U 1 1 5FBEC32E
P 5400 2800
F 0 "#PWR0111" H 5400 2650 50  0001 C CNN
F 1 "+5V" H 5415 2973 50  0000 C CNN
F 2 "" H 5400 2800 50  0001 C CNN
F 3 "" H 5400 2800 50  0001 C CNN
	1    5400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 2800 5600 2800
$Comp
L MX_Alps_Hybrid:MX-LED MX7
U 1 1 5FBEF25D
P 2250 7100
F 0 "MX7" H 2332 7324 60  0000 C CNN
F 1 "MX-LED" H 2332 7250 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 1625 7075 60  0001 C CNN
F 3 "" H 1625 7075 60  0001 C CNN
	1    2250 7100
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX8
U 1 1 5FBEF263
P 2800 7100
F 0 "MX8" H 2882 7324 60  0000 C CNN
F 1 "MX-LED" H 2882 7250 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2175 7075 60  0001 C CNN
F 3 "" H 2175 7075 60  0001 C CNN
	1    2800 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 7250 2200 7250
Wire Wire Line
	2200 7250 2750 7250
Connection ~ 2200 7250
Wire Wire Line
	2400 6250 2400 7050
Wire Wire Line
	2950 6250 2950 7050
NoConn ~ 2350 7100
NoConn ~ 2250 7200
NoConn ~ 2800 7200
NoConn ~ 2900 7100
Text GLabel 1900 7250 0    50   Input ~ 0
key_row4
Text GLabel 3200 2600 2    50   Input ~ 0
key_row4
NoConn ~ 8150 2000
NoConn ~ 8150 3550
Wire Wire Line
	7500 4050 7500 3900
Wire Wire Line
	8150 2200 8400 2200
Wire Wire Line
	8150 3750 8400 3750
Wire Wire Line
	3000 2600 3200 2600
Wire Wire Line
	3200 2500 3000 2500
Wire Wire Line
	3200 2400 3000 2400
Wire Wire Line
	3000 2100 3200 2100
Wire Wire Line
	3000 2200 3200 2200
$Comp
L power:+5V #PWR0112
U 1 1 5FC00EA8
P 3100 1500
F 0 "#PWR0112" H 3100 1350 50  0001 C CNN
F 1 "+5V" H 3115 1673 50  0000 C CNN
F 2 "" H 3100 1500 50  0001 C CNN
F 3 "" H 3100 1500 50  0001 C CNN
	1    3100 1500
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0113
U 1 1 5FC01BE9
P 3350 1600
F 0 "#PWR0113" H 3350 1350 50  0001 C CNN
F 1 "Earth" H 3350 1450 50  0001 C CNN
F 2 "" H 3350 1600 50  0001 C CNN
F 3 "~" H 3350 1600 50  0001 C CNN
	1    3350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1500 3100 1500
Wire Wire Line
	3000 1600 3350 1600
$Comp
L pcb_lib:motorized_fader MF1
U 1 1 5FC14390
P 7750 2200
F 0 "MF1" H 8178 2004 50  0000 L CNN
F 1 "motorized_fader" H 8178 2095 50  0000 L CNN
F 2 "pcb:motorized_fader" H 8250 2050 50  0001 C CNN
F 3 "https://tech.alpsalpine.com/prod/e/html/potentiometer/slidepotentiometers/rsn1m/rsa0n11m9a0j.html" H 8250 2050 50  0001 C CNN
	1    7750 2200
	-1   0    0    1   
$EndComp
$Comp
L pcb_lib:motorized_fader MF2
U 1 1 5FC15DBA
P 7750 3750
F 0 "MF2" H 8178 3554 50  0000 L CNN
F 1 "motorized_fader" H 8178 3645 50  0000 L CNN
F 2 "pcb:motorized_fader" H 8250 3600 50  0001 C CNN
F 3 "https://tech.alpsalpine.com/prod/e/html/potentiometer/slidepotentiometers/rsn1m/rsa0n11m9a0j.html" H 8250 3600 50  0001 C CNN
	1    7750 3750
	-1   0    0    1   
$EndComp
$Comp
L pcb_lib:QwiicProMicroUSBC PM1
U 1 1 5FC1872C
P 2550 1350
F 0 "PM1" H 2550 1465 50  0000 C CNN
F 1 "QwiicProMicroUSBC" H 2550 1374 50  0000 C CNN
F 2 "pcb:QwiicProMicroUSBC" H 2550 1350 50  0001 C CNN
F 3 "" H 2550 1350 50  0001 C CNN
	1    2550 1350
	1    0    0    -1  
$EndComp
NoConn ~ 2100 1700
NoConn ~ 2100 1800
NoConn ~ 3000 1700
NoConn ~ 3000 1800
Text GLabel 3200 2000 2    50   Input ~ 0
fader_cap2
Text GLabel 3200 1900 2    50   Input ~ 0
fader_cap1
Wire Wire Line
	3000 1900 3200 1900
Wire Wire Line
	3000 2000 3200 2000
Text GLabel 1850 1900 0    50   Input ~ 0
fader_out1
Text GLabel 1850 2100 0    50   Input ~ 0
fader_out2
Wire Wire Line
	1850 1900 2100 1900
Wire Wire Line
	1850 2100 2100 2100
Text GLabel 8850 3650 2    50   Input ~ 0
fader_cap2
Text GLabel 8850 2100 2    50   Input ~ 0
fader_cap1
Text GLabel 8850 1850 2    50   Input ~ 0
fader_out1
Text GLabel 8850 3400 2    50   Input ~ 0
fader_out2
$Comp
L Device:R R2
U 1 1 5FDAE858
P 8600 3400
F 0 "R2" V 8393 3400 50  0000 C CNN
F 1 "5M" V 8484 3400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8530 3400 50  0001 C CNN
F 3 "~" H 8600 3400 50  0001 C CNN
	1    8600 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	8850 3400 8750 3400
Wire Wire Line
	8450 3400 8450 3650
Wire Wire Line
	8450 3650 8150 3650
Wire Wire Line
	8450 3650 8850 3650
Connection ~ 8450 3650
$Comp
L Device:R R1
U 1 1 5FDB417E
P 8600 1850
F 0 "R1" V 8393 1850 50  0000 C CNN
F 1 "5M" V 8484 1850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 8530 1850 50  0001 C CNN
F 3 "~" H 8600 1850 50  0001 C CNN
	1    8600 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 1850 8450 2100
Wire Wire Line
	8450 2100 8150 2100
Wire Wire Line
	8450 2100 8850 2100
Connection ~ 8450 2100
Wire Wire Line
	8750 1850 8850 1850
$Comp
L MX_Alps_Hybrid:MX-LED MX10
U 1 1 5FDBF2D1
P 3350 5500
F 0 "MX10" H 3432 5724 60  0000 C CNN
F 1 "MX-LED" H 3432 5650 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2725 5475 60  0001 C CNN
F 3 "" H 2725 5475 60  0001 C CNN
	1    3350 5500
	1    0    0    -1  
$EndComp
$Comp
L MX_Alps_Hybrid:MX-LED MX11
U 1 1 5FDBF2D7
P 3350 6300
F 0 "MX11" H 3432 6524 60  0000 C CNN
F 1 "MX-LED" H 3432 6450 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2725 6275 60  0001 C CNN
F 3 "" H 2725 6275 60  0001 C CNN
	1    3350 6300
	1    0    0    -1  
$EndComp
Text GLabel 3500 3950 0    50   Input ~ 0
key_col3
Wire Wire Line
	2750 4950 3300 4950
Wire Wire Line
	2750 5650 3300 5650
Wire Wire Line
	2750 6450 3300 6450
Wire Wire Line
	3500 4750 3500 5450
Wire Wire Line
	3500 5450 3500 6250
Connection ~ 3500 5450
NoConn ~ 3450 4800
NoConn ~ 3350 4900
NoConn ~ 3450 5500
NoConn ~ 3350 5600
NoConn ~ 3350 6400
NoConn ~ 3450 6300
$Comp
L MX_Alps_Hybrid:MX-LED MX12
U 1 1 5FDBF2EB
P 3350 7100
F 0 "MX12" H 3432 7324 60  0000 C CNN
F 1 "MX-LED" H 3432 7250 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2725 7075 60  0001 C CNN
F 3 "" H 2725 7075 60  0001 C CNN
	1    3350 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 7250 3300 7250
Wire Wire Line
	3500 6250 3500 7050
NoConn ~ 3350 7200
NoConn ~ 3450 7100
Text GLabel 1800 1500 0    50   Input ~ 0
key_col3
Wire Wire Line
	2100 1500 1800 1500
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5FDC5C56
P 800 1600
F 0 "J1" H 718 1275 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 718 1366 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 800 1600 50  0001 C CNN
F 3 "~" H 800 1600 50  0001 C CNN
	1    800  1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 1600 1400 1600
$Comp
L power:+5V #PWR0104
U 1 1 5FDCD0EC
P 1000 1500
F 0 "#PWR0104" H 1000 1350 50  0001 C CNN
F 1 "+5V" H 1015 1673 50  0000 C CNN
F 2 "" H 1000 1500 50  0001 C CNN
F 3 "" H 1000 1500 50  0001 C CNN
	1    1000 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5FDCF188
P 1250 1600
F 0 "R3" V 1043 1600 50  0000 C CNN
F 1 "200" V 1134 1600 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1180 1600 50  0001 C CNN
F 3 "~" H 1250 1600 50  0001 C CNN
	1    1250 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	1100 1600 1000 1600
$Comp
L MX_Alps_Hybrid:MX-LED MX9
U 1 1 5FDBF2CB
P 3350 4800
F 0 "MX9" H 3432 5024 60  0000 C CNN
F 1 "MX-LED" H 3432 4950 20  0000 C CNN
F 2 "Button_Switch_Keyboard:SW_Cherry_MX_1.00u_PCB" H 2725 4775 60  0001 C CNN
F 3 "" H 2725 4775 60  0001 C CNN
	1    3350 4800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5FDDB7A9
P 2400 4250
F 0 "R4" H 2470 4296 50  0000 L CNN
F 1 "200" H 2470 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2330 4250 50  0001 C CNN
F 3 "~" H 2400 4250 50  0001 C CNN
	1    2400 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5FDDC8C8
P 2950 4250
F 0 "R5" H 3020 4296 50  0000 L CNN
F 1 "200" H 3020 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2880 4250 50  0001 C CNN
F 3 "~" H 2950 4250 50  0001 C CNN
	1    2950 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5FDDEBCF
P 3500 4250
F 0 "R6" H 3570 4296 50  0000 L CNN
F 1 "200" H 3570 4205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3430 4250 50  0001 C CNN
F 3 "~" H 3500 4250 50  0001 C CNN
	1    3500 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 4750 2400 4400
Connection ~ 2400 4750
Wire Wire Line
	2400 4100 2400 3950
Wire Wire Line
	2950 3950 2950 4100
Wire Wire Line
	2950 4400 2950 4750
Connection ~ 2950 4750
Wire Wire Line
	3500 3950 3500 4100
Wire Wire Line
	3500 4400 3500 4750
Connection ~ 3500 4750
Wire Wire Line
	6600 3000 7000 3000
Wire Wire Line
	7000 3000 7000 4050
Wire Wire Line
	7000 4050 7500 4050
Wire Wire Line
	6600 3200 7500 3200
Wire Wire Line
	7500 3200 7500 3300
Wire Wire Line
	6600 2600 7500 2600
Wire Wire Line
	7500 2350 7500 2600
Wire Wire Line
	6600 2400 6600 1750
Wire Wire Line
	6600 1750 7500 1750
$EndSCHEMATC
