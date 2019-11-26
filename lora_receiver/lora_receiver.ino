#include <LoRa.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAND 915E6
#define SCK_LORA 5
#define MISO_LORA 19
#define MOSI_LORA 27
#define RESET_PIN_LORA 14
#define SS_PIN_LORA 18
#define HIGH_GAIN_LORA 20

#define OLED_SDA_PIN 4
#define OLED_SCL_PIN 15
#define OLED_RESET 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define OLED_LINE1 0
#define OLED_LINE2 10
#define OLED_LINE3 20
#define OLED_LINE4 30
#define OLED_LINE5 40
#define OLED_LINE6 50

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 16);
void initDisplay(void);
bool initLora(void);

void initDisplay(void){
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)){
    Serial.print("[LoRa Receiver] OLED display initialize failed."); 
  }
  else{
    Serial.println("[LoRa Receiver] OLED display connection established.");

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
  }
}

bool initLora(void){
  bool init_status = false;
  
  Serial.println("[LoRa Sender] Trying start LoRa comunication...");
  
  SPI.begin(SCK_LORA, MISO_LORA, MOSI_LORA, SS_PIN_LORA);
  LoRa.setPins(SS_PIN_LORA, RESET_PIN_LORA, LORA_DEFAULT_DIO0_PIN);

  if(!LoRa.begin(BAND)){
    Serial.print("Radio LoRa initialize failed.");
    delay(1000);
    init_status = false;
  }
  else{LoRa.setTxPower(HIGH_GAIN_LORA);
    Serial.print("Radio LoRa initialized.");
    Serial.println("[LoRa Sender] LoRa connection established.");
    init_status = true;
  }

  return init_status;
}

void onReceive(int packetSize) {
  String incoming = "";
  
  if (packetSize == 0) return;
  
  while (LoRa.available()) {
    incoming += '0' + (char)LoRa.read();
    
  }

  display.clearDisplay();
  display.setCursor(0, OLED_LINE1);
  display.print("RSSI: ");
  display.println(LoRa.packetRssi());
  display.setCursor(0, OLED_LINE2);
  display.print("SNR: ");
  display.println(LoRa.packetSnr());
  display.setCursor(0, OLED_LINE3);
  display.print("Information: ");
  display.println(incoming);
  display.display();
  
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
  
}

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  
  initDisplay();

  display.clearDisplay();
  display.setCursor(0, OLED_LINE1);
  display.println("Katz Viado");
  display.println("LoRa Receiver");
  display.print("Waiting for content...");
  display.display();

  while(initLora() == false);

}

void loop() {
  onReceive(LoRa.parsePacket());

}
