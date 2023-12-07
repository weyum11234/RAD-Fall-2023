#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;

const char* ssid = "nyu-media2.4GHz";
const char* pwd = "nyumedia-23-24";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

int bpm = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(5, OUTPUT);

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", [](){server.send(200, "text/plain", "Testing, testing. 1, 2, 3!");});
  server.on("/pulse", pulse);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bpm > 0) {
    digitalWrite(5, HIGH);
    delay(7000 / bpm);
    digitalWrite(5, LOW);
    delay(53000 / bpm);
  }
  server.handleClient();
}

void pulse() {
  String output = "BPM set to " + server.arg("bpm");
  bpm = server.arg("bpm").toInt();
  server.send(200, "text/plain", output);
}
