# Embedded C project for PIC microcontroller
# Table of contents
- [Description](#description)
- [Requirements](#requirements)
- [Embedded System](#embedded-system)

# Description
- Developed a C-based driver for PIC16F887 to control the hardware (LCD screen, 2 LEDs, 2 push-buttons, photoresistor). Utilized I2C protocol to interface with the LCD screen and ADC converter to interface with the photoresistor.
- Developed an LCD library including commonly used functions such as clear and write to screen and move the cursor. The LCD screen displays an informative message in the first row and the current brightness in the second row.
- To concurrently serve timer and I/O events while main functions continue to execute, PIC interrupts are used. For example, an LED blinks to indicate that the system is up and a second LED lights up while a button is pressed.

[![Youtube Demo of Project](https://user-images.githubusercontent.com/98546890/155945937-2bbcddb1-84fe-410f-9edf-12444f013c57.png)](https://youtu.be/UswdGbRHbeY)

# Requirements
For PIC16F887 microcontroller programming, the following are required:
- PICkit 2 or 3 Programmer
- MPLAB X IDE ([download](https://www.microchip.com/mplab/mplab-x-ide))
- XC8 compiler ([download](https://www.microchip.com/mplab/compilers))

# Embedded System
## Parts
- PIC16F887
- LCD 16x2 character with I2C interface
- Two LEDs
- Two push-buttons
- Photoresistor
- Resistor 10K Ohm
- Voltage Regulator L7805CV (5V 1.5A)

## Schematic
At the center of the schematic is the PIC16F887 microcontroller, which is connecting with:
- LCD screen (top-center) using I2C
- Two LEDs (bottom-right)
- Two push-buttons (bottom-left)
- Photoresistor (middle-left)

The project also includes a voltage regulator to maintain a constant voltage level (not shown in the schematic below). <br/>
Power dissipation of L7805CV: Power = [V<sub>in</sub> - V<sub>out</sub>] x I<sub>out</sub> = (7.3 - 5) * 0.053 = 0.122 mWatt (safe operating area)

![schematic](https://user-images.githubusercontent.com/98546890/155946819-313a21d3-0da2-4815-95db-06f017a885cf.PNG)

## Prototyped
![IMG_20220227_115829](https://user-images.githubusercontent.com/98546890/155946601-706e1d15-bcba-46e0-89d6-d9125a9a5bb6.jpg)
![IMG_20220227_115832](https://user-images.githubusercontent.com/98546890/155946604-40c5d138-1a96-47d5-8904-9d675a04bd1a.jpg)
