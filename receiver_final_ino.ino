#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Wi-Fi credentials
const char* ssid = "Galaxy A14 5G 930D ";
const char* password = "Varshigaavrishapa";

ESP8266WebServer server(80);
String displayStatus = "Waiting...";

void setup() {
  Serial.begin(115200);

  // OLED init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Booting...");
  display.display();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/update", []() {
    String status = server.arg("status");
    Serial.println("Received attendance: " + status);
    server.send(200, "text/plain", "Attendance status received: " + status);
  });

  // Optional: handle root URL so it shows something in browser
  server.on("/", []() {
    server.send(200, "text/plain", "Receiver NodeMCU is running.");
  });

  server.begin();
  Serial.println("HTTP server started");
}


void loop() {
  server.handleClient();
}
