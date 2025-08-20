#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "wifi_pass"
#define API_KEY "api_key"
#define DATABASE_URL "realtime_db_link"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("SignUp OK");
  } else {
    Serial.println("SignUp Failed");
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  if (Firebase.RTDB.setInt(&fbdo, "/test/value", 123)) {
    Serial.println("Write OK");
  } else {
    Serial.println("Write Failed: " + fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "/test/value")) {
    if (fbdo.dataType() == "int") {
      Serial.print("Read: ");
      Serial.println(fbdo.intData());
    }
  } else {
    Serial.println("Read Failed: " + fbdo.errorReason());
  }

  delay(5000);
}
