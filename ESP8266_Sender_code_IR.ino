#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// ---------------- IR Sensor Pin ----------------
#define IR_PIN D5   // GPIO14

// ---------------- WiFi Credentials ----------------
const char* ssid = "Airtel_chit_0880";
const char* password = "air11658";

// ---------------- MQTT Configuration ----------------
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266/ir_sensor";

// ---------------- MQTT Client ----------------
WiFiClient espClient;
PubSubClient client(espClient);

// ---------------- WiFi Setup ----------------
void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MQTT Reconnect ----------------
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266_IR_Client")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

// ---------------- Setup ----------------
void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

// ---------------- Loop ----------------
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read raw IR sensor value
  int raw_ir = digitalRead(IR_PIN);

  // Convert to required logical output
  int ir_status;
  const char* status_text;

  if (raw_ir == LOW) {
    ir_status = 1;                 // Object detected
    status_text = "Object Detected";
  } else {
    ir_status = 0;                 // No object
    status_text = "No Object";
  }

  // Create JSON payload
  StaticJsonDocument<200> doc;
  doc["ir_status"] = ir_status;
  doc["status"] = status_text;

  char buffer[128];
  serializeJson(doc, buffer);

  // Publish to MQTT
  client.publish(mqtt_topic, buffer);

  // Serial Monitor Output
  Serial.print("IR Status: ");
  Serial.print(ir_status);
  Serial.print(" | ");
  Serial.println(status_text);

  delay(1000);   // Publish every 1 second
}
