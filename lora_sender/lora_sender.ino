#include <LoRa.h>
#include <SPI.h>
#include <Wire.h>

#define BAND 915E6
#define SCK_LORA 5
#define MISO_LORA 19
#define MOSI_LORA 27
#define RESET_PIN_LORA 14
#define SS_PIN_LORA 18
#define HIGH_GAIN_LORA 20

char informationToSend = 0;
bool loraInit(void);

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

  while(loraInit() == false);

}

void loop() {
  Serial.println("Sending package...");
  LoRa.beginPacket();
  LoRa.write((unsigned char *)&informationToSend, sizeof(informationToSend));
  LoRa.endPacket();

  Serial.print("Sent value: ");
  Serial.println(informationToSend);

  informationToSend ++;

  delay(1000);

}
