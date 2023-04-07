#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_ADS1X15.h>
#include <DFRobot_ESP_EC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
 
#define ONE_WIRE_BUS 14
#define ONE_WIRE_BUS 13                // this is the gpio pin 13 on esp32.
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
 
DFRobot_ESP_EC ec;
Adafruit_ADS1115 ads;
 
float voltage, ecValue, temperature = 25;
 
String apiKey = "AX0LBY82YHRWIKH0";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "NOTHING";     // replace with your wifi ssid and wpa2 key
const char *pass =  "123456987";
const char *server = "api.thingspeak.com";
const int ecPin = 27;   // pin that the sensor is attached to
const int ledPin1=13 ;      // pin that the LED1 is attached to
const int ledPin2=1;      // pin that the LED2 is attached to


WiFiClient client;
 
 
void setup()
{
  Serial.begin(115200);
  EEPROM.begin(32);//needed EEPROM.begin to store calibration k in eeprom
  ec.begin();
  sensors.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
 
  Serial.println("Connecting to ");
  Serial.println(ssid);
 
 
  WiFi.begin(ssid, pass);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
 
void loop()
{
  voltage = analogRead(A0); // A0 is the gpio 36
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);  // read your temperature sensor to execute temperature compensation
  ecValue = ec.readEC(voltage, temperature); // convert voltage to EC with temperature compensation
 
  Serial.print("Temperature:");
  Serial.print(temperature, 2);
  Serial.println("ºC"); //celcius
 
  Serial.print("EC:");
  Serial.println(ecValue, 2);
  Serial.println("S/m"); //siemens per metre
  display.setTextSize(2);
  display.setTextColor(WHITE);
 
  display.setCursor(0, 10);
  display.print("T:");
  display.print(temperature, 2);
  display.drawCircle(85, 10, 2, WHITE); // put degree symbol ( ° )
  display.setCursor(90, 10);
  display.print("C");
 
  display.setCursor(0, 40);
  display.print("EC:");
  display.print(ecValue, 2);
  display.display();
  delay(1500);
  display.clearDisplay();
 
  ec.calibration(voltage, temperature); // calibration process by Serail CMD
 
  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
 
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(temperature, 2);
    postStr += "&field2=";
    postStr += String(ecValue, 2);
    postStr += "\r\n\r\n";
    delay(500);
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    delay(500);
  }
  client.stop();
}

void Setup() {
  
  pinMode(ledPin1, OUTPUT);  // initialize the LED pin as an output
  
  Serial.begin(9600); // initialize serial communication
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);  
}

void Loop() {
  // read the value of the electrical conductivity:
  int ecValue = analogRead(ecPin);

  // if the analog value is high enough, turn on the LED:
  if (ecValue>=0.5 && ecValue<=3) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin2, HIGH);
  }

  // print the ec value:
  Serial.println(ecValue);
  delay(1);  // delay in between reads for stability
}
