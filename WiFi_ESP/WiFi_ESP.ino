#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "MLV 2.4G";     // SSID da sua rede Wi-Fi
const char* password = "mlv181524"; // Senha da sua rede Wi-Fi

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);  // Conecta-se à rede Wi-Fi

  Serial.println();
  Serial.print("Conectando");

  while (WiFi.status() != WL_CONNECTED) { // Aguarda a conexão com a rede Wi-Fi
    delay(1000);
    Serial.println(".");
  }

  Serial.println("");

  Serial.println("WiFi Conectado");

  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    Serial.print("Dados recebidos do Arduino: ");
    Serial.println(input);

    // Verifica se os dados recebidos são de distância do sensor
    if (input.startsWith("D:")) {
      // Remove o prefixo "D:" para obter o valor da distância
      String distanceStr = input.substring(2);
      float distance = distanceStr.toFloat();

      // Realiza o POST dos dados para o servidor
      WiFiClient client; // Cria um objeto WiFiClient
      HTTPClient http;
      http.begin(client, "http://192.168.0.71:5000/api/data"); // URL do seu servidor
      http.addHeader("Content-Type", "application/json");

      // Corpo da requisição (JSON com o valor da distância)
      String json = "{\"value\": " + String(distance) + "}";

      int httpResponseCode = http.POST(json);
      if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.println(payload);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      http.end(); // Encerra a conexão HTTP
    }
  }

  delay(1000); // Aguarda 1 segundo antes de verificar novamente
}