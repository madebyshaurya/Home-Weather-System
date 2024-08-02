#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define DHTPIN 18
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* messages[] = {
  "Getting it ready...",
  "Loading...",
  "Firing the system...",
  "Getting stats..."
};

int inputPin = 17;               // choose the input pin (for PIR sensor)
int pirState = LOW;   
int val = 0;                    // variable for reading the pin status          // we start, assuming no motion detected

void setup() {
  Serial.begin(115200);
  pinMode(inputPin, INPUT);
  dht.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  // delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  // Display a random message
  randomSeed(analogRead(0)); // Initialize random number generator
  int randomIndex = random(0, sizeof(messages) / sizeof(messages[0]));
  display.println(messages[randomIndex]);

  display.display();
}

void loop() {
  delay(2000);

  display.clearDisplay()

  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if failed

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial1.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial1.println(hic);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  // Display static text
  display.println(F("Home Status: "));
  display.println(" ");
  display.print("Temp: ");

  char tempBuffer[6];
  dtostrf(t, 4, 1, tempBuffer); // Format temperature with 1 decimal place
  display.print(tempBuffer);

  display.print(" ");
  display.write(247); // Degree symbol
  display.println("C");
  display.println(" ");
  display.print("Humidity: ");
  display.print((int)h); // Cast to int to round down and remove decimal places
  display.println("%");
  display.display();
  } else {
    display.clearDisplay();
  }
}
