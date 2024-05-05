#include "FirebaseESP8266.h"
// #include <ESP8266WiFi.h>

#define WIFI_SSID "sss"
#define WIFI_PASSWORD "999999999"

#define DATABASE_URL "https://kendali-led-87708-default-rtdb.firebaseio.com///" //MASUKKAN URL HOST DISINI tanpa https
#define FIREBASE_AUTH "Mz5wutv0KRkwqSpbbYVNN4Fnvm6zgtgtuvqSfSfI" //MASUKKAN KODE SECRET DISINI

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

int led = D4;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); //nilai awal relay akan off
  
  WifiConnect();
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  config.host = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
  //Firebase.begin("firebase host", "firebase auth database");
}

void WifiConnect() {
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//memulai menghubungkan ke wifi router
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("."); //status saat mengkoneksikan
  }
Serial.println("Sukses terkoneksi wifi!");
Serial.println("IP Address:"); //alamat ip lokal
Serial.println(WiFi.localIP());
}

void loop() {
  if (Firebase.getString(firebaseData, "/led")) {
  if  (firebaseData.dataType() == "string")
    {
      String Status = firebaseData.stringData();
      if (Status == "ON") {                                                        
      Serial.println("Led Menyala");                        
      digitalWrite(led, HIGH); }
      else if (Status == "OFF") {                                                 
      Serial.println("led Mati");
      digitalWrite(led, LOW);                                               
      }
      else {Serial.println("Silahkan hanya isi dengan ON atau OFF");}
    }
  }
}