//Include da lib de Wifi do ESP8266
#include <ESP8266WiFi.h>
 
const char* ssid = "Himalaia";
const char* password = "#*EC15D7";
String apiKey = "12HZ998MHW3ST0RN";  
const char* server = "api.thingspeak.com";
 
WiFiClient client;
 
void setup() {
  Serial.begin(9600);
  //Inicia o WiFi
  WiFi.begin(ssid, password);
 
  //conexão ao roteador
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  //Logs no console serial
  Serial.println("");
  Serial.print("Conectado na rede ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
 
  //Espera 30 segundos para fazer a leitura
  delay(30000);

  int umidadeSolo = analogRead(0);

  umidadeSolo = -0.0977*umidadeSolo + 100;
 
  //Inicia um client TCP para o envio dos dados
  if (client.connect(server,80)) {
    String postStr = apiKey;
           postStr +="&amp;field1=";
           postStr += String(umidadeSolo);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
 
     //Logs na porta serial
     Serial.print(" Umidade Solo: ");
     Serial.println(umidadeSolo);
  }
  client.stop();
}
