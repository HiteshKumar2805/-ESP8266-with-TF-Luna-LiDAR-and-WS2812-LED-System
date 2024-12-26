# ESP8266 TF-Luna LiDAR and WS2812 LED System

This project demonstrates a wireless communication system using ESP8266, TF-Luna LiDAR, and WS2812 RGB LEDs with the ESP-NOW protocol. The goal is to detect objects within a 10 cm range using the TF-Luna LiDAR sensor and change the color of WS2812 LEDs based on the detected distance. If an object is detected within 10 cm, the LEDs will glow green for 10 seconds. If no object is detected, the LEDs will remain red.

## Project Components
- **ESP8266**: A Wi-Fi microcontroller used for communication between the LiDAR sensor and the WS2812 LEDs.
- **TF-Luna LiDAR**: A ToF (Time of Flight) sensor for measuring distances.
- **WS2812 LEDs**: RGB LEDs used to indicate the status based on the LiDAR data.

## Libraries Used
- **Wire**: For I2C communication between the ESP8266 and TF-Luna LiDAR sensor.
- **espnow**: For wireless communication using the ESP-NOW protocol.
- **ESP8266WiFi**: Used for Wi-Fi functionality of the ESP8266.
- **ArduinoJson**: Used for formatting and sending data in JSON format.
- **FastLED**: For controlling the WS2812 RGB LEDs.

## Hardware Setup
1. Connect the TF-Luna LiDAR to the ESP8266 via I2C (SDA, SCL).
2. Connect the WS2812 LEDs to the ESP8266 on a specified GPIO pin (D0 in this case).
3. The ESP-NOW protocol is used for communication between two ESP8266 boards:
   - One board acts as the sender (connected to the LiDAR sensor).
   - The other board acts as the receiver (controlling the WS2812 LEDs).

## How It Works
- **Sender Code**: The sender continuously reads distance data from the TF-Luna LiDAR sensor. When the distance is 10 cm or less, it sends a message to the receiver to turn the LEDs green for 10 seconds. Otherwise, the LEDs stay red.
- **Receiver Code**: The receiver listens for incoming messages over ESP-NOW. Upon receiving the message, it processes the distance value and changes the color of the LEDs accordingly.

### Flow
1. The **sender** sends a JSON message with the distance value.
2. The **receiver** receives the data, extracts the distance, and controls the LEDs.
3. If the distance is less than or equal to 10 cm, the LEDs turn green for 10 seconds.
4. If the distance is greater than 10 cm, the LEDs turn red.

## Output
The LEDs will glow:
- **Green** when an object is detected within 10 cm.
- **Red** when no object is detected within the specified range.

## Installation
1. Install the required libraries in the Arduino IDE:
   - **Wire**
   - **espnow**
   - **ESP8266WiFi**
   - **ArduinoJson**
   - **FastLED**

2. Upload the **sender code** to one ESP8266 and the **receiver code** to the other ESP8266.

3. Power both ESP8266 devices, and the system will start operating, detecting objects and controlling the LEDs based on the distance.

## Future Improvements
- Implement more complex object detection and categorization.
- Enhance the LED effects for different distances.
- Add a web interface for configuration and status monitoring.

## License
This project is open-source and available under the [MIT License](LICENSE).
