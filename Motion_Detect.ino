#include <WiFiNINA.h>
#include <PubSubClient.h> // MQTT library

// WiFi credentials
#define WIFI_SSID "Optus_508297_EXT"
#define WIFI_PASSWORD "heezegytes22umL"

// MQTT Broker settings (HiveMQ Cloud)
#define MQTT_SERVER "333ee9d324244021a2661d2fc723ca4a.s1.eu.hivemq.cloud"      // example: abc7.s1.eu.hivemq.cloud
#define MQTT_PORT 8883
#define MQTT_TOPIC "sensor/motion"
#define MQTT_USER "hivemq.webclient.1745744841681"
#define MQTT_PASSWORD "0AE6*ktBg!3WC4wrF.:n"

// PIR sensor pin
const int pirSensorPin = 2;
int motionDetected = 0;

WiFiSSLClient wifiSSLClient;
PubSubClient mqttClient(wifiSSLClient);

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqttClient.connect("ArduinoNanoIoT", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pirSensorPin, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  connectMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();

  motionDetected = digitalRead(pirSensorPin);
  if (motionDetected == HIGH) {
    Serial.println("Motion Detected!");
    mqttClient.publish(MQTT_TOPIC, "Motion detected");
  } else {
    Serial.println("No motion detected.");
    mqttClient.publish(MQTT_TOPIC, "No motion detected");
  }
  delay(5000); // Send data every 5 seconds
}
