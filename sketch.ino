// Now turn this trash into treasure!

#include "DHT.h"

#define DHTPIN 18
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial1.println("hey there");

  dht.begin();
}
void loop() {
  delay(2000);

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

  Serial1.print(F("Humidity: "));
  Serial1.print(h);
  Serial1.print(F("%  Temperature: "));
  Serial1.print(t);
  Serial1.print(F("°C "));
  Serial1.print(f);
  Serial1.print(F("°F  Heat index: "));
  Serial1.print(hic);
  Serial1.print(F("°C "));
  Serial1.print(hif);
  Serial1.println(F("°F"));
}