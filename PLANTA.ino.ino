#include <ESP8266WiFi.h> 
//defines
#define SSID_REDE     "UFPI"  
#define SENHA_REDE    ""  
#define INTERVALO_ENVIO_THINGSPEAK  30000  //intervalo entre envios de dados ao ThingSpeak (em ms)
 
//constantes e variáveis globais
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "9MQN6AZ5AAW9FW78";
long lastConnectionTime; 
WiFiClient client;
 
//prototipos
void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
float FazLeituraUmidade(void);
 
/*
 * Implementações
 */
 
//Função: envia informações ao ThingSpeak
void EnviaInformacoesThingspeak(String StringDados)
{
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {         
        //faz a requisição HTTP ao ThingSpeak
        client.print("POST /update HTTP/1.1n");
        client.print("Host: api.thingspeak.comn");
        client.print("Connection: closen");
        client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"n");
        client.print("Content-Type: application/x-www-form-urlencodedn");
        client.print("Content-Length: ");
        client.print(StringDados.length());
        client.print("nn");
        client.print(StringDados);
  
        lastConnectionTime = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
     }   
}
 
//Função: faz a conexão WiFI
void FazConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
 
    delay(1000);
}
 
//Função: faz a leitura do nível de umidade (ON HOLD)
float FazLeituraUmidade(void)
{
    int ValorADC;
    float UmidadePercentual;
 
     ValorADC = analogRead(0);  
     Serial.print("[Leitura ADC] ");
     Serial.println(ValorADC);
 
     UmidadePercentual = 100 * ((978-(float)ValorADC) / 978);
     Serial.print("[Umidade Percentual] ");
     Serial.print(UmidadePercentual);
     Serial.println("%");
 
     return UmidadePercentual;
}
void setup()
{  
    Serial.begin(9600);
    lastConnectionTime = 0; 
    FazConexaoWiFi();
    Serial.println("Irrigation Sys");
}
 

