# 🌀 SmartFanPi
**An offline voice-controlled smart fan powered by Raspberry Pi and Arduino using Snowboy for speech recognition.**

---

## Abstract
SmartFanPi is a smart home project that integrates **Raspberry Pi**, **Arduino**, and the **Snowboy** wake-word detection engine to realize a **fully offline voice-controlled electric fan**.  
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

## Software & Tools
| Component | Description |
|------------|-------------|
| **Raspberry Pi OS** | Main operating system for running Python and Snowboy |
| **Arduino IDE (C/C++)** | For uploading control logic to Arduino board |
| **Python 3** | Implements voice command logic and serial communication |
| **Snowboy** | Offline wake-word detection engine |
| **Docker** | Used for model training environment |
| **VirtualBox** | Used for testing and simulation environment |

---

## 🔮 未來展望 (Future Work)
- Improve **microphone sensitivity** and **recognition accuracy**  
- Expand **voice model dataset** for multi-speaker robustness  
- Add **sound localization** for auto head-turning toward user  
- Develop **mobile app** for custom voice command setup  
- Integrate with IoT cloud or MQTT for smart home ecosystem  

---

## 🪪 License
This project is released for educational and research purposes.  
You may modify and share under the terms of the MIT License.

---

> 🌀 *“Technology inspired by humanity — making everyday life smarter and simpler.”*
