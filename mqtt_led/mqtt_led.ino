#include <WiFi.h>
#include <PubSubClient.h>

#define LDR_PIN 36
#define MQTT_CLIENT "TRIGGERMQTTLED"
#define STA_SSID ""
#define STA_PSK  ""
#define MQTT_SERVER ""
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PWD ""

WiFiClient WFCLIENT;
PubSubClient MQTT(WFCLIENT);

void initMqtt(){

  MQTT.setServer(MQTT_SERVER, MQTT_PORT);
  MQTT.setCallback(mqttCallback);

  Serial.println("MQTT initialized!");

}

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

void mqttCallback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Success message");
  Serial.print(topic);

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
}

void mqttReconnect(){

  while (!MQTT.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (MQTT.connect("ESP32Client", MQTT_USER, MQTT_PWD)) {
 
      Serial.println("Connected to MQTT!");  
 
    } else {
 
      Serial.print("Connection failed.");
      Serial.println(MQTT.state());
      
      delay(2000);
 
    }
  }

  Serial.println("MQTT connection process terminated!");
  
}

void setup() {

  delay(3000);

  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  initWiFi();
  initMqtt();
  mqttReconnect();

  Serial.println("Settup completed!");

}

void loop() {

  delay(2000);
  
  int state = analogRead(LDR_PIN);
  char stateToSend[10];
  sprintf(stateToSend, "%d", state);

  Serial.print("Resistência: ");
  Serial.println(stateToSend);

  if (state >= 3000) {
    digitalWrite(LED_BUILTIN, HIGH);
    MQTT.publish("monitoring/ldr", stateToSend);
    MQTT.publish("monitoring/period", "Night");
    Serial.println("Night");
  }
  else {
    digitalWrite(LED_BUILTIN, LOW);
    MQTT.publish("monitoring/ldr", stateToSend);
    MQTT.publish("monitoring/period", "Day");
    Serial.println("Day");
  }

  MQTT.loop();

}
