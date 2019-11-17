#include <WiFi.h>
#include <WebServer.h>

#define STASSID ""
#define STAPSK  ""

WebServer server(80);

void handleRoot() {

  char html[] = "<!DOCTYPE HTML>\r\n<html>\r\n"
  "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
  "<link rel=\"icon\" href=\"data:,\">"
  "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}"
  ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;"
  "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}"
  ".button2 {background-color: #77878A;}</style></head>"
  "<body><h1>Welcome!</h1>"
  "<h3>LED On/Off</h3>"
  "<p><a href=\"ledOn\" target=\"myIframe\"><button class=\"button\">ON</button></a></p>"
  "<p><a href=\"ledOff\" target=\"myIframe\"><button class=\"button button2\">OFF</button></a></p>"
  "<p><a href=\"getStatus\" target=\"myIframe\"><button class=\"button button3\">Get Status</button></a></p>"
  "<iframe name=\"myIframe\" width=\"100\" height=\"25\" frameBorder=\"1\"><br>"
  "</body></html>\n";

  String rootPage = html;
  
  Serial.println("You called root page");
  server.send(200, "text/html", rootPage);
  
}

void handleLEDon() {
  
  Serial.println("LED is on!");
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.print("Saída do pino: ");
  Serial.println(digitalRead(LED_BUILTIN));
  server.send(200, "text/html", "LED is On");
  
}

void handleLEDoff() {
  
  Serial.println("LED off page");
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Saída do pino: ");
  Serial.println(digitalRead(LED_BUILTIN));
  server.send(200, "text/html", "LED is Off");
  
}

void handleLEDStatus() {
  
  Serial.println("Getting LED status...");
  int status = digitalRead(LED_BUILTIN);

  if(status == 1){
    Serial.println("LED ligado.");
    server.send(200, "text/html", "LED is On");
  }
  else{
    Serial.println("LED desligado.");
    server.send(200, "text/html", "LED is Off");
  }
  
}

void initWiFi() {
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

void initServer() {

  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/ledOn", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ledOff", handleLEDoff);
  server.on("/getStatus", handleLEDStatus);

  server.begin();
  Serial.println("Server started!");

  Serial.println("Server Address: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());

  Serial.println("HTTP server started");
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  initWiFi();
  initServer();

}

void loop() {

  server.handleClient();

}
