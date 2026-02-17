
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D4
#define RST_PIN D1

MFRC522 mfrc522(SS_PIN, RST_PIN);

// Wi-Fi credentials
const char* ssid = "Galaxy A14 5G 930D";
const char* password = "Varshigaavrishapa";

// Receiver NodeMCU IP (Staffroom)
const char* host = "192.168.193.123";

// For preventing repeat scans
String lastUID = "";
unsigned long lastScanTime = 0;
const unsigned long scanCooldown = 5000;  // 5 seconds

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  // Look for new card
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
    return;

  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid.toUpperCase();

  Serial.println("Scanned UID: " + uid);

  // Prevent rapid repeated scans of same tag
  if (uid == lastUID && millis() - lastScanTime < scanCooldown) {
    Serial.println("Duplicate scan ignored.");
    return;
  }

  lastUID = uid;
  lastScanTime = millis();

  if (uid == "35E2F54") { // Replace with your actual UID
    sendAttendance("attended");
  } else {
    sendAttendance("unattended");
  }
}

void sendAttendance(String status) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Skipping send.");
    return;
  }

  WiFiClient client;
  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }

  String url = "/update?status=" + status;
  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for server response
  unsigned long timeout = millis();
  while (client.connected() && millis() - timeout < 5000) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }

  String response = client.readString();
  Serial.println("Response: " + response);
}
