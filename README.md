# Android-Things---Individual-Project
Android Things individual project 
	ESP32 Wi-Fi Control Hub: Remote LED Management System

The ESP32 Smart Control Panel project demonstrates how to create a web-based control system. The project configures an ESP32 microcontroller as a Wi-Fi access point, hosting a responsive web interface that can be accessed by nearby devices. The interface features two intuitive buttons that allow users to remotely toggle the state of two LEDs mounted on the motherboard. When a user connects to the ESP32's network and loads the webpage, they can interact with the buttons to send commands wirelessly to the microcontroller, which then processes these commands and controls the corresponding LED outputs in real-time, providing visual feedback of the system's operation

Screenshots


![image](https://github.com/user-attachments/assets/0c191221-628e-465a-90c5-cfbbb35dddb5)

![image](https://github.com/user-attachments/assets/d2bd71cb-9ff5-4ac4-8c72-a2a890d559c4)


Schematics

 ![image](https://github.com/user-attachments/assets/1df868d3-99ba-4a30-905e-aa8c419e9b42)

Prerequisites:
•	ESP32 WiFi Module
•	Arduino IDE

The following individual components:
•	2 LEDs (1 red, 1 green)
•	2 220Ω resistors
•	Jumper wires (4) 
•	1 breadboard

Running
To run the ESP8266/ESP32 LED control project:

1.Connect the LEDs to your ESP8266/ESP32 GPIO pins according to the schematics in the diagram:
Green LED connected to GPIO6 (with 220Ω resistor)
Red LED connected to GPIO7 (with 220Ω resistor)

2.Install the required libraries in Arduino IDE: ESP32 board package
3.Deploy and run the sketch to your ESP32 module
4.Verify that the LEDs respond correctly when changing the buttons values 
