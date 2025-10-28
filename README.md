# Voice-Controlled-Fan
**An offline voice-controlled smart fan powered by Raspberry Pi and Arduino using Snowboy for speech recognition.**

---

## Abstract
This is a project that integrates **Raspberry Pi**, **Arduino**, and the **Snowboy** wake-word detection engine to realize a **fully offline voice-controlled electric fan**.  
The system allows users to control the fan’s power, wind speed, oscillation, and timer using voice commands — eliminating the need for a remote control or internet connection.  

By combining **offline speech recognition** with **microcontroller-based hardware control**, SmartFanPi provides a convenient, privacy-preserving, and extensible solution for home appliance automation.  
This project demonstrates how AI and embedded systems can enhance daily life by merging **human-centered interaction** and **hardware innovation**.

---

## System Architecture

### Overview
SmartFanPi consists of four major components:
- **Raspberry Pi 4** — serves as the *speech recognition module*, running the Python program and managing wake-word detection using Snowboy.
- **Arduino Uno R3** — acts as the *control board*, receiving commands from the Raspberry Pi via serial communication and controlling the fan hardware.
- **Microphone** — captures the user’s voice commands and sends the audio to the Raspberry Pi for processing.
- **DC Electric Fan** — modified to interface with Arduino output pins to perform physical actions (power, speed, oscillation, timer, etc.).

###  Architecture Diagram
<img width="1716" height="530" alt="image" src="https://github.com/user-attachments/assets/30156573-9060-4c44-bdcb-0eef5fdee6c7" />

---

## Key Features
- **Offline Speech Recognition:**  
  Using Snowboy’s deep learning-based keyword detection to recognize commands without internet access.
- **Dual Microcontroller Design:**  
  Raspberry Pi handles recognition; Arduino executes control logic and timing.
- **Bidirectional Serial Communication:**  
  Ensures synchronization between voice recognition states and fan operations.
- **Multithreading & Semaphore Synchronization:**  
  Python program uses multithreading with binary semaphore (Peterson’s solution) to coordinate listeners.
- **Hardware Integration:**  
  Fan control board connected via GPIO through custom wiring.

---

## Setup

### Arduino 
- In the `fansArduino` directory, you will find all Arduino-related source files, including both **test programs** and the **main control program** `fanSystem.ino`.
### ResperryPi
- In the `fansRaspberryPi` directory, you will find all Raspberry Pi–related code, including both **test programs** and the **main runtime script** `snowboyDetection.py`.  
This Python script is responsible for **detecting voice commands** and **communicating with the Arduino** via serial connection.
To ensure proper operation, follow these setup steps:

1. Clone the [Kitt-AI Snowboy](https://github.com/Kitt-AI/snowboy) project onto Raspberry Pi.
2. Inside the cloned repository, locate the examples/python/ folder.
3. Copy the entire python folder and rename it to snowboytest.
4. Place your main script snowboyDetection.py and the trained voice model files (PMDL directory) into the ~/snowboytest/ folder.
5. Run the program
6. Once executed, the Raspberry Pi will start listening for your wake word and send control commands to the Arduino in real time.

---

## Note
For further details, demonstrations, and implementation explanations, please refer to the project report`專題成果報告書.pdf`.
