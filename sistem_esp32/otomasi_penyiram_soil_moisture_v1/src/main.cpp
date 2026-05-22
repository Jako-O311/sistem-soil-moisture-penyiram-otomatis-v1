#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHTesp.h>

// // put function declarations here:
// int myFunction(int, int);

// pinout
const int soilMoisturePin1 = 34;  // Pin untuk sensor kelembaban tanah 1
// const int soilMoisturePin2 = 35;  // Pin untuk sensor kelembaban tanah 2
// DHTesp dht; // Inisialisasi objek DHT
// const int dhtPin = 17; // Pin untuk sensor kelembaban udara DHT22
// TempAndHumidity dhtData; // Variabel untuk menyimpan data sensor DHT22
const int relayPin = 12;          // Pin untuk relay 1 channel
LiquidCrystal_I2C lcd(0x27, 16, 2);
// threshold kelembaban dalam persen
const int moistureThreshold = 30;

// // kredensial wifi
// const char* ssid = "ssid";
// const char* password = "pass";
// WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  // inisialisasi serial monitor
  Serial.begin(115200);
  // Set pin relay sebagai output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  // // setup sensor DHT22
  // dht.setup(dhtPin, DHTesp::DHT22);
  // dhtData = dht.getTempAndHumidity(); // Baca data awal dari DHT22
  // setup wifi
  // WiFi.begin(ssid, password);
  // Serial.println("koneksi ke wifi");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // server.on("/", []() {
  //   server.send(200, "text/plain", "test123");
  // });
  // serv
  // server.begin();

  // inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("soil moisture");
  lcd.setCursor(0, 1);
  lcd.print("sistem siap");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  // baca nilai analog dari sensor (0-4095 untuk ESP32)
  int sensorValue1 = analogRead(soilMoisturePin1);
  // int sensorValue2 = analogRead(soilMoisturePin2);
  // konversi ke persentase kelembaban
  // diasumsikan jika 0 = basah 100%, 4095 = kering 0%)
  // sesuaikan mapping berdasarkan kalibrasi sensor
  int moisturePercent1 = map(sensorValue1, 0, 4095, 100, 0);
  // int moisturePercent2 = map(sensorValue2, 0, 4095, 100, 0) + 10;
  // hitung rata kelembaban
  // int avgMoisture = (moisturePercent1 + moisturePercent2) / 2;
  // kontrol relay - relay menyala jika rata-rata kelembaban di bawah threshold
  // delay(dht.getMinimumSamplingPeriod()); // Tunggu sesuai dengan periode sampling minimum DHT22
  // dht.getTempAndHumidity(); // Update data DHT22

  if (moisturePercent1 < moistureThreshold) {
    digitalWrite(relayPin, LOW);  // Nyalakan relay untuk penyiraman
  } else {
    digitalWrite(relayPin, HIGH); // Matikan relay
  }
  // tampilan interface LCD untuk interaksi user
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(moisturePercent1);
  lcd.print("%");
  // lcd.print(moisturePercent2);
  // lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Relay: ");
  if (digitalRead(relayPin) == LOW) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
  // tampilan untuk serial monitor untuk debugging
  Serial.print("Sensor1: ");
  Serial.print(moisturePercent1);
  // Serial.print("%, Sensor2: ");
  // Serial.print(moisturePercent2);
  // Serial.print("%, Avg: ");
  // Serial.print(avgMoisture);
  // Serial.println("Temp: "+String(dhtData.temperature, 2)+"'C Kelembaban: "+String(dhtData.humidity, 1)+"%");
  Serial.print("Relay: ");
  Serial.println(digitalRead(relayPin) == LOW ? "ON" : "OFF");
  // delay 1 detik
  delay(1000);
}

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }