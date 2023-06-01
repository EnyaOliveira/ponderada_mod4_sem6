//adicionando bibliotecas necessárias
#include "UbidotsEsp32Mqtt.h"

//fazendo o setup do ambiente 
const char *UBIDOTS_TOKEN = "BBFF-Mv1C1wZkHEu3MK61H13hnkOxMwOzgt";  
const char *WIFI_SSID = "Inteli-welcome";      
const char *WIFI_PASS = "";      
const char *DEVICE_LABEL = "godoi";   
const char *VARIABLE_LABEL = "ponderada6"; 

const int PUBLISH_FREQUENCY = 2000; 

unsigned long tempo;
uint8_t analogPin = 34; 

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char *topic, byte *payload, unsigned int length)
{
 // Serial.print("Messagem recebida");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  tempo = millis();
}

void loop(){

  // unsigned long millis();
  static unsigned long millisAntes = 0;

  if (!ubidots.connected()){
    ubidots.reconnect();
  }
  if (abs(long(millis())) - millisAntes >= PUBLISH_FREQUENCY) {
    float value = WiFi.RSSI();
    ubidots.add(VARIABLE_LABEL, WiFi.RSSI()); 
    ubidots.publish(DEVICE_LABEL);
    Serial.print("Intensidade do sinal:");
    Serial.print(WiFi.RSSI());
    Serial.println("dBm");
    tempo = millis();
  }
  ubidots.loop();
}