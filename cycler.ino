
void getCyclerData() {

    if (IS_WIFI_CONNECTED == true) {
        // String request = generateGetHTTP(CYCLER_DATA_URL);
        // DynamicJsonDocument response = requestData(request, CD_JSON_TOTAL_OBJECTS, CD_JSON_STRING_BYTES);

        http.begin(SERVER_HOST, SERVER_PORT, String(CYCLER_DATA_URL) + String(BICYCLE_ID));
        int httpCode = http.GET();

        if (httpCode > 0) {
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();

                const size_t capacity = JSON_OBJECT_SIZE(CD_JSON_TOTAL_OBJECTS) + CD_JSON_STRING_BYTES;
                DynamicJsonDocument doc(capacity);
                DeserializationError error = deserializeJson(doc, payload);
                if (error) {
                    Serial.print(F("deserializeJson() failed: "));
                    Serial.println(error.c_str());
                }

                cycler.yearAge = doc["age"];
                cycler.maxHeartRate = 220 - cycler.yearAge;
                cycler.target.distance = doc["distance"];
                cycler.target.elevation = doc["elevation"];
                cycler.target.finishTime = doc["time"];
            }

        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
          
    }

}
