#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  dht.begin();
  Serial.begin(115200);

}

void loop() {
  delay(3000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(h) || isnan(t)) {
    Serial.println("Failed operation!");
    return;
  }

  Serial.println("===============");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%\t");
  Serial.print("Temperature: ");
  Serial.println(t);
  Serial.println("===============");

}
