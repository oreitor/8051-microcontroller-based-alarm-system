# 8051 Microcontroller Based Alarm System

This project is about an 8051 microcontroller based home burglar alarm system using PIR and Magnetic Reed Switch sensors. The circuit detects motions using the Magnetic sensor and also detects living things using the PIR sensor. When an intrusion occurs, password verification is requested and if it answers incorrectly, there is a security violation. When this situation happens, a warning signal is sent through serial communication.

There are many different ways to send an warning signal with serial comm. You can send SMS with the GSM module or make different applications. I used TCP/IP comm for warning signal. When there is a security violation, 8051 microcontroller sends '1' signal to serial port. Then, my Python client code gets these signals. When the received signal reaches every 3 times, a warning message is sent by Python to the Police server. For given example to this scenario, I made these [client](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/client.py) and [server](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/server.py) code with Python. 

### Proteus Circuit Schematic
<p align="center">
  <img width="600" src="https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/8051-mbas.png">
</p>

### Scenarios of System
* [S1 - Security Violation and Police Warning Signal](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S1.gif)
* [S1 - Python](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S1.gif)
* [S2 - Alarm Disabling](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S2.gif)
* [S3 - Incorrect Password](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S3.gif)
* [S4 - Password Reset](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S4.gif)
* [S5 - Reset Button](https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/Scenarios%20of%20System/S5.gif)

### Project Requirements
* AT89C52 Microcontroller
* PIR Sensor
* Magnetic Reed Switch Sensor
* LCD Panel
* 4x3 Keypad
* Buzzer
* LED
* Crystal (Important for serial comm!)

### Determination of Crystal Frequency


### Flowchart of System
<p align="center">
  <img width="250" src="https://github.com/oreitor/8051-microcontroller-based-alarm-system/blob/main/flowchart.png">
</p>
