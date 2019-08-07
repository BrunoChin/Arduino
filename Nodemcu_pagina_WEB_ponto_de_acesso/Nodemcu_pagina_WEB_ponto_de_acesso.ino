#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//#include "arquivopaginaweb.h">
#include "paginaWebBotaop.h">

const char* ssid = "Harry Potter";
const char* senha = "coxinha123";

ESP8266WebServer server(80);

int valor;

int led_d4 = D0;

void setup() {
  pinMode(led_d4, OUTPUT);
  
 Serial.begin(115200);

 Serial.println("\n");
 Serial.println("Configurando ponto de acesso...");

 WiFi.mode(WIFI_AP);
 WiFi.softAP(ssid);

 Serial.print("Criando a rede: ");
 Serial.println(ssid);

 IPAddress meuIP = WiFi.softAPIP();

 Serial.print("Endereço IP: ");
 Serial.println(meuIP);

 server.on("/", raiz);
 server.on("/LED_D4_ligar", Ligar_led_d4);
 server.on("/LED_D4_desligar", Desligar_led_d4);
 server.on("/piscarLento", PiscarLento);
 server.on("/piscarRapido", PiscarRapido);
 server.begin();
}

void loop() {
  server.handleClient();
  if(valor == 1){
    digitalWrite(led_d4, 0);
    delay(200);
    digitalWrite(led_d4, 1);
    delay(200);
  }
  if(valor == 2){
    digitalWrite(led_d4, 0);
    delay(40);
    digitalWrite(led_d4, 1);
    delay(40);
  }
}

void raiz(){
  server.send(200, "text/html", paginaBotao);
}

void Ligar_led_d4(){
  digitalWrite(led_d4, 0);
  server.sendHeader("Location", "/");
  server.send(303);
}

void Desligar_led_d4(){
  digitalWrite(led_d4, 1);
  server.sendHeader("Location", "/");
  server.send(303);
}

void PiscarLento(){
  valor = 1;
  server.sendHeader("Location", "/");
  server.send(303);
}

void PiscarRapido(){
  valor = 2;
  server.sendHeader("Location", "/");
  server.send(303);
}
