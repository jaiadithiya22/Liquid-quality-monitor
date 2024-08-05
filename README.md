# Liquid Quality Monitoring System

This Arduino project monitors the electrical conductivity (EC) and temperature of a liquid using an ESP32, displays the values on an OLED screen, and sends the data to ThingSpeak for remote monitoring. Additionally, the system uses LEDs to indicate the EC value range.

## Components Used

- ESP32
- DS18B20 Temperature Sensor
- DFRobot EC Sensor
- Adafruit SSD1306 OLED Display
- Adafruit ADS1115 ADC
- WiFi Module
- LEDs
- Resistors
- Breadboard and jumper wires

## Libraries Used

- `Wire`
- `EEPROM`
- `WiFi`
- `OneWire`
- `DallasTemperature`
- `Adafruit_ADS1X15`
- `DFRobot_ESP_EC`
- `Adafruit_GFX`
- `Adafruit_SSD1306`


## Code Explanation

### Setup

The setup function initializes the serial communication, the OLED display, and the WiFi connection. It also initializes the EC and temperature sensors.

### Loop

The loop function reads the EC and temperature values, displays them on the OLED screen, and sends them to ThingSpeak. It also controls the LEDs based on the EC value.

### Functions

- `setup()`: Initializes components and connects to WiFi.
- `loop()`: Continuously reads sensor data, updates the display, and sends data to ThingSpeak.
- `Setup()`: Sets up the pins for the LEDs and initializes serial communication.
- `Loop()`: Reads the EC value and controls the LEDs based on the value.

## Prerequisites

- Arduino IDE
- ESP32 board installed in Arduino IDE
- Required libraries installed

## Installation

1. **Clone the repository or download the script:**
   ```sh
   git clone (https://github.com/jaiadithiya22/Liquid-quality-monitor.git)
   cd Liquid-quality-monitor
   
Open the Arduino IDE and load the .ino file.

Install the required libraries from the Library Manager.

Connect your ESP32 and upload the code.

## Usage
Power the ESP32 and ensure it is connected to WiFi.
Observe the EC and temperature values displayed on the OLED screen.
Monitor the data remotely on ThingSpeak.

##ThingSpeak Setup
Create a ThingSpeak account and a new channel.
Get your Write API Key from the channel settings.
Replace the apiKey variable in the code with your ThingSpeak Write API Key.

## Notes
Ensure you have the necessary permissions to connect to the specified WiFi network.
Use appropriate calibration for the EC sensor for accurate readings.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
DFRobot for the EC sensor library.
Adafruit for the OLED display library and ADS1115 ADC library.
ThingSpeak for providing the platform for IoT data logging.

## Patent
This project has been granted an Indian patent for its innovative approach to liquid quality monitoring.
