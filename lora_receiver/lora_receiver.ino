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
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
#define OLED_RESET 16

#define OLED_LINE1 0
#define OLED_LINE2 10
#define OLED_LINE3 20
#define OLED_LINE4 30
#define OLED_LINE5 40
#define OLED_LINE6 50

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 16);

void initDisplay(void){
  if(!display.begin(SSD1306_SWITCHAPVCC, OLED_ADDR)){
    Serial.print("[LoRa Receiver] OLED display initialize failed."); 
  }
  else{
    Serial.println("[LoRa Receiver] OLED display connection established.");

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
  }
}

bool loraInit(void){
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

void setup() {
  Serial.begin(115200);

  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  
  initDisplay();

  display.clearDisplay();
  display.setCursor(0, OLED_LINE1);
  display.print("Wait...");
  display.display();

  while(loraInit() == false);

}

void loop() {
  char receivedByte;
  int sizePacket = 0;
  int loraRssi = 0;
  long receivedInformation = 0;
  char * ptReceivedInformation = NULL;
  if (packet_size == sizeof(informacao_recebida)) 
    {
        Serial.print("[LoRa Receiver] Há dados a serem lidos");
                      
        ptInformaraoRecebida = (char *)&informacao_recebida;  
        while (LoRa.available()) 
        {
            byte_recebido = (char)LoRa.read();
            *ptInformaraoRecebida = byte_recebido;
            ptInformaraoRecebida++;
        }

        /* Escreve RSSI de recepção e informação recebida */
        lora_rssi = LoRa.packetRssi();
        display.clearDisplay();   
        display.setCursor(0, OLED_LINE1);
        display.print("RSSI: ");
        display.println(lora_rssi);
        display.setCursor(0, OLED_LINE2);
        display.print("Informacao: ");
        display.setCursor(0, OLED_LINE3);
        display.println(informacao_recebida);
        display.display();      
    }

}
