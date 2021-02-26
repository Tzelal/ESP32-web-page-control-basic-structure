#include <Arduino.h>

//ESP32'nin wifi özelliğini kullanabilmemizi sağlayan kütüphane
#include <WiFi.h>

//AsyncTCP ve ESPAsyncWebServer web sitesini oluşturmak için gerekli kütüphanelerdir.
#include <AsyncTCP.h> 
#include "ESPAsyncWebServer.h"

const char* ssid = "Ağ İsmini yerleştirin";
const char* password = "Şifre girin";

//port 80'de AsyncWebServer objesi oluşturulur (80 HTTP serverlerinin standart portudur)
AsyncWebServer server(80);

/*
 index_html değişkeni web sitesini oluşturacak HTML,CSS,JS kodlarını saklar.
 PROGMEM değişkenin flash'a kaydedileceğini belirtir. 
 R ile rawliteral arasında kalan herşey saf string olarak algılanır.
 rawliteral yerine kullanılmamış farklı bir isim kullanılabilir.
 */
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
</head>
<body>
</body>
</html>)rawliteral";

void initWiFi (){
 // ESP32 modülü wifi istasyonu olarak ayarlanır
  WiFi.mode(WIFI_STA);

  // Ağa bağlanılan kısım
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  initWiFi();

  /*
  Serial monitördeki ESP32 Ip adresi üzerinden istek geldiğinde 
  aşağıdaki kod devreye giricek ve index_html değişkeni ile web sitesi çalıştırılıcak.
  */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  //(Son olarak web sitesi çalıştırılır.) 
  server.begin();
}

//Asenkron web server'i ile çalışdığı için loop()'a gerek yok.
void loop() {
}
