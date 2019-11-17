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
  "<h3>Web Server</h3>"
  "<h5>Server is running!</h5>"
  "</body></html>\n";

  String rootPage = html;
  
  Serial.println("You called root page");
  server.send(200, "text/html", rootPage);
  
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

  server.on("/", handleRoot);
  server.begin();

  Serial.println("Server Address: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println("HTTP server is started");
  
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  initWiFi();
  initServer();

}

void loop() {

  server.handleClient();

}
