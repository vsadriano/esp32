#include <WiFi.h>

#define STA_SSID ""
#define STA_PSK  ""

void initWiFi(){
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(STA_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

}

void setup() {

  Serial.begin(115200);
  
  initWiFi();

}

void loop() {

}
