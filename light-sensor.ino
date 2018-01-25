
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
  server.on("/lights", HTTP_OPTIONS, []() {
    sendCors();
    server.send(200, "text/html", "ok");
  });

  /* GET /daikin
     Content-Type: application/json
  */
  server.on("/lights", HTTP_GET, []() {
    sendCors();
    server.send(200, "application/json", ac.toJson());
  });

  /* POST /daikin
     Content-Type: application/json
     {
       "targetMode": "heat",
       "targetFanSpeed": "auto",
       "targetTemperature": 23,
       "swingVertical": true,
       "swingHorizontal": false,
       "powerful": false,
       "quiet": true
     }
  */
  server.on("/lights", HTTP_POST, []() {
    /* Parse the json body into the "body" variable */
    DynamicJsonBuffer jsonBuffer;
    JsonObject& body = jsonBuffer.parseObject(server.arg("plain"));
    
  //Define pins to output voltage only
  pinMode(BED_1, OUTPUT);
  pinMode(BED_2, OUTPUT);
  pinMode(BED_3, OUTPUT);
  pinMode(BED_4, OUTPUT);
  pinMode(BATHROOM, OUTPUT);
  pinMode(LANDING, OUTPUT);
}

void changePins(int a, int b, int c, int d, int e, int f) {
  digitalWrite(BED_1, a);
  digitalWrite(BED_2, b);
  digitalWrite(BED_3, c);
  digitalWrite(BED_4, d);
  digitalWrite(BATHROOM, e);
  digitalWrite(LANDING, f);
}

void loop() {


      changePins(LOW, LOW, LOW, LOW, LOW, LOW); // Set all Pins off

// These will return a value which can be used for determining if the light
// is on or off. Will do the `is light on or off` code on client side.

  float bed1Light; // BED_1 read
    changePins(HIGH, LOW, LOW, LOW, LOW, LOW);
    bed1Light = analogRead(ANALOG_PIN);
    return bed1Light;

  float bed2Light; // BED_2 read
    changePins(LOW, HIGH, LOW, LOW, LOW, LOW);
    bed2Light = analogRead(ANALOG_PIN);
    lightCalc(readPin)
    return bed2Light;

  float bed3Light; // BED_3 read
    changePins(LOW, LOW, HIGH, LOW, LOW, LOW);
    bed3Light = analogRead(ANALOG_PIN);
    return bed3Light;

  float bed4Light; // BED_4 read
    changePins(LOW, LOW, LOW, HIGH, LOW, LOW);
    bed4Light = analogRead(ANALOG_PIN);
    return bed4Light;

  float bathroomLight; // BATHROOM read
    changePins(LOW, LOW, LOW, HIGH, LOW, LOW);
    bathroomLight = analogRead(ANALOG_PIN);
    return bathroomLight;

  float landingLight; // LANDING read
    changePins(LOW, LOW, LOW, HIGH, LOW, LOW);
    landingLight = analogRead(ANALOG_PIN);
    return landingLight;

}

