
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char* ssid = "Unknown2";
const char* password = "Bethany123";

const char* accessoryName = "light-sever";

#define BED_1 4
#define BED_2 5
#define BED_3 6
#define BED_4 7
#define BATHROOM 20
#define LANDING 19


#define ANALOG_PIN 2


String toJson() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["bed1Light"] = bed1Light();
  root["bed2Light"] = bed2Light();
  root["bed3Light"] = bed3Light;
  root["bed4Light"] = bed4Light;
  root["bathroomLight"] = bathroomLight;
  root["landingLight"] = landingLight;

  String res;
  root.printTo(res);

  return res;
}

void setup() {

delay(1000);

  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);

  WiFi.mode(WIFI_STA);
  WiFi.hostname(accessoryName);

  WiFi.begin(ssid, password);

  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin(accessoryName, WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  //Define  pins to output voltage only
  pinMode(BED_1, OUTPUT);
  pinMode(BED_2, OUTPUT);
  pinMode(BED_3, OUTPUT);
  pinMode(BED_4, OUTPUT);
  pinMode(BATHROOM, OUTPUT);
  pinMode(LANDING, OUTPUT);
}

void changeMux(int a, int b, int c, int d, int e, int f) {
  digitalWrite(BED_1, a);
  digitalWrite(BED_2, b);
  digitalWrite(BED_3, c);
  digitalWrite(BED_4, d);
  digitalWrite(BATHROOM, e);
  digitalWrite(LANDING, f);
}

void loop() {

  float readPin;

    changeMux(LOW, LOW, LOW, LOW, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // All pins off

    changeMux(HIGH, LOW, LOW, LOW, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BED_1 read
    return bed1Light;

    changeMux(LOW, HIGH, LOW, LOW, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BED_2 read
    return bed2Light;

    changeMux(LOW, LOW, HIGH, LOW, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BED_3 read
    return bed3Light;

    changeMux(LOW, LOW, LOW, HIGH, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BED_4 read
    return bed4Light;

    changeMux(LOW, LOW, LOW, HIGH, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BATHROOM read
    return BathroomLight;

    changeMux(LOW, LOW, LOW, HIGH, LOW, LOW);
    readPin = analogRead(ANALOG_PIN); // BATHROOM read
    return LandingLight;

}

