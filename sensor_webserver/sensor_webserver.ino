#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT22
#define STASSID ""
#define STAPSK  ""

DHT dht(DHTPIN, DHTTYPE);
WiFiServer server(80);

void initWiFi(){
  Serial.print("Connecting to ");
  Serial.println(STASSID);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

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

void initServer(){
  server.begin();
  Serial.println("Server started!");
  
  Serial.println("Server Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  dht.begin();

  initWiFi();
  initServer();

}

void loop() {
  WiFiClient client = server.available();
  
  if(!client) {
    return;   
  }
 
  Serial.println("New client...");
  
  while(!client.available()) {
    delay(1);
  }
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  if(isnan(h) || isnan(t)) {
    Serial.println("Failed operation!");
    return;
  }

  Serial.println("===============");
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.println("%\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("C");
  Serial.println("===============");

  char txt[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n"
  "<h1>Welcome!</h1>"
  "<h3>Temperature/Humidity Server Example</h3>"
  "<p>Temperature and Humidity</p>\n";

  client.print(txt);
  client.print(h);
  client.print("% ");
  client.print(t);
  client.print("C");
  client.print("</html>");

  delay(3000);

}
