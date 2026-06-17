/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete instructions at https://RandomNerdTutorials.com/esp32-websocket-server-sensor/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <Arduino_JSON.h>

// Substitua pelas credenciais da sua rede
const char* ssid = "IJC";
const char* senha = "rede142536";

// Cria o objeto do servidor na porta 80
AsyncWebServer servidor(80);

// Cria um objeto WebSocket
AsyncWebSocket ws("/ws");

// Variável JSON para armazenar as leituras do sensor
JSONVar leituras;

// Variáveis de temporizador
unsigned long ultimoTempo = 0;
unsigned long atrasoTemporizador = 1000;

int valorUmidade, leituraSensor;
const int pinoSensor = 36;  /* Pino de saída do sensor de umidade do solo */

// Obtém as leituras do sensor e retorna um objeto JSON
String obterLeituraSensor() {
  leituras["umidade"] = valorUmidade;
  String jsonString = JSON.stringify(leituras);
  return jsonString;
}

// Inicializa o LittleFS
void iniciarLittleFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("Ocorreu um erro ao montar o LittleFS");
  }
  Serial.println("LittleFS montado com sucesso");
}

// Inicializa o WiFi
void iniciarWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, senha);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void notificarClientes(String leituraSensor) {
  ws.textAll(leituraSensor);
}

void lidarMensagemWebSocket(void *arg, uint8_t *dados, size_t comprimento) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == comprimento && info->opcode == WS_TEXT) {
    String leituraSensor = obterLeituraSensor();
    Serial.print(leituraSensor);
    notificarClientes(leituraSensor);
  }
}

void onEvent(AsyncWebSocket *servidor, AsyncWebSocketClient *cliente, AwsEventType tipo, void *arg, uint8_t *dados, size_t comprimento) {
  switch (tipo) {
    case WS_EVT_CONNECT:
      Serial.printf("Cliente WebSocket #%u conectado de %s\n", cliente->id(), cliente->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("Cliente WebSocket #%u desconectado\n", cliente->id());
      break;
    case WS_EVT_DATA:
      lidarMensagemWebSocket(arg, dados, comprimento);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void iniciarWebSocket() {
  ws.onEvent(onEvent);
  servidor.addHandler(&ws);
}

void setup() {
  Serial.begin(115200);
  iniciarWiFi();
  iniciarLittleFS();
  iniciarWebSocket();

  // URL raiz do servidor Web
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest *requisicao) {
    requisicao->send(LittleFS, "/index.html", "text/html");
  });

  servidor.serveStatic("/", LittleFS, "/");

  // Inicia o servidor
  servidor.begin();
}

void loop() {
  if ((millis() - ultimoTempo) > atrasoTemporizador) {
    String leituraSensor = obterLeituraSensor();
    Serial.print(leituraSensor);
    notificarClientes(leituraSensor);
    ultimoTempo = millis();
  }
  leituraSensor = analogRead(pinoSensor);
  valorUmidade = (100 - ((leituraSensor / 4095.00) * 100));
  ws.cleanupClients();
}

