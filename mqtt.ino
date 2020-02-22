
// connectBroker connect to MQTT broker
void connectBroker() {
    Serial.println("Connecting to MQTT broker");
    while (!mqttClient.connect(CLIENT_NAME, CLIENT_USERNAME, CLIENT_PASSWORD)) {
        Serial.print(".");
    }
     
    Serial.println("Connected to broker!");
}
