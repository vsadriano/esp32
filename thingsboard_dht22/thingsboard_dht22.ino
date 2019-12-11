#include <DHT.h>
#include <PubSubClient.h>
#include <ThingsBoard.h>
#include <WiFi.h>

#define DHTPIN 4
#define DHTTYPE DHT22
#define TOKEN "" // ThingsBoard Device Token
#define STA_SSID ""
#define STA_PSK  ""

DHT dht(DHTPIN, DHTTYPE);
WiFiClient WFCLIENT;
ThingsBoard tb(WFCLIENT);
PubSubClient MQTT(WFCLIENT);

char thingsboardServer[] = ""; // ThingsBoard Server
unsigned long lastSend;

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

void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data...");

  // Reading temperature or humidity takes about 250 milliseconds!
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("Sending data to ThingsBoard:");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C ");

  tb.sendTelemetryFloat("temperature", temperature);
  tb.sendTelemetryFloat("humidity", humidity);
}

void reconnect() {
  // Loop until we're reconnected
  while (!tb.connected()) {
    int status = WiFi.status();
    if ( status != WL_CONNECTED) {
      initWiFi();
    }
    Serial.print("Connecting to ThingsBoard node ...");
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

void setup() {
  delay(3000);
  dht.begin();
  Serial.begin(115200);
  initWiFi();
  lastSend = 0;
  Serial.println("Settup completed!");

}

void loop() {
  if ( !tb.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
    getAndSendTemperatureAndHumidityData();
    lastSend = millis();
  }

  tb.loop();

}
