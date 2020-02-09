
DynamicJsonDocument requestData(String request, int jsonLength, int jsonStringBytes) {
  
    if (!wifiClient.connect(SERVER_HOST, SERVER_PORT)) {
        Serial.println("connection failed");
    }
    wifiClient.print(request);

    const size_t capacity = JSON_OBJECT_SIZE(jsonLength) + jsonStringBytes;
    DynamicJsonDocument doc(capacity);
    
    getServerResponse(doc);
    return doc;
    
}

void getServerResponse(DynamicJsonDocument doc) {
  
    char status[32] = {0};
    wifiClient.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status + 9, "200 OK") != 0) {
        Serial.print(F("Unexpected response: "));
        Serial.println(status);
    }

    char endOfHeaders[] = "\r\n\r\n";
    if (!wifiClient.find(endOfHeaders)) {
        Serial.println(F("Invalid response"));
    }

    
    DeserializationError error = deserializeJson(doc, wifiClient);
    if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
    }
    
}
