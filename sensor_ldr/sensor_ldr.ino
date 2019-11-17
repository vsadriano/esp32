// Sensor de luz com LDR
// Quanto maior luminosidade, menor o valor da leitura
// Quanto menor o indice de luminosidade, maior o valor
// da resistencia - valor que sera impresso na leitura
// do pino 0
 
int ldrPin = 36; //LDR no pino analígico 8
int ldrValue = 0; //Valor lido do LDR
int intensity;
 
void setup() {
 pinMode(LED_BUILTIN,OUTPUT);
 Serial.begin(115200);
}
 
void loop() {
  ldrValue = analogRead(ldrPin);
  Serial.print("Resistência: ");
  Serial.println(ldrValue);
  intensity = map(ldrValue,0,4095,1,100); // Valor atribuido a intensidade da luz
  Serial.print("Intensidade: ");
  Serial.println(intensity);
 
  //Se o valor lido for maior que 500, liga o led
  if (ldrValue>=3000) digitalWrite(LED_BUILTIN,HIGH);
  // senão, apaga o led
  else digitalWrite(LED_BUILTIN,LOW);

  delay(3000);
}
