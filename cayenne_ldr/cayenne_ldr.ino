#include <CayenneMQTTESP32.h>

char wifi_ssid[] = "";
char wifi_pwd[] = "";
char cayenne_user[] = "";
char cayenne_pwd[] = "";
char cayenne_id[] = "";

CAYENNE_IN(0){
  digitalWrite(LED_BUILTIN,getValue.asInt());
}

void setup() {
  Cayenne.begin(cayenne_user, cayenne_pwd, cayenne_id, wifi_ssid, wifi_pwd);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  Cayenne.loop();
  Cayenne.virtualWrite(1, analogRead(32));
  delay(2000);

}
