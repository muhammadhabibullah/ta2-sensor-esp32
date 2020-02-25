
void publishRawData() {
    mqttClient.publish("raw", JSONRawBuffer); 
    delay(750);
    Serial.print("uploading raw data: ");
    Serial.println(JSONRawBuffer);
}

void publishFinaleData() {
    mqttClient.publish("finale", JSONFinBuffer); 
    delay(750);
    Serial.print("uploading finale data: ");
    Serial.println(JSONFinBuffer);
}
