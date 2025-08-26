#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <DHT.h>

#define DHTPIN D2         // Data pin of DHT sensor
#define DHTTYPE DHT22     // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(hum); Serial.println(" %");

  // Optional: send data to cloud server
  // HTTPClient http;
  // http.begin("http://yourserver.com/update?temp="+String(temp)+"&hum="+String(hum));
  // http.GET();
  // http.end();

  delay(5000);
}
