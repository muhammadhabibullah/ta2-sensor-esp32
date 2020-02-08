
void getCyclerData() {

    if (IS_WIFI_CONNECTED == true) {
        String request = generateGetHTTP(CYCLER_DATA_URL);
        DynamicJsonDocument response = requestData(request, CD_JSON_TOTAL_OBJECTS, CD_JSON_STRING_BYTES);
        
        cycler.yearAge = response["age"];
        cycler.maxHeartRate = 220 - cycler.yearAge;
        cycler.target.distance = response["distance"];
        cycler.target.elevation = response["elevation"];
        cycler.target.finishTime = response["time"];
    
        Serial.println("Cycler age: " + cycler.yearAge);
        Serial.println("Success get cycler data");   
    }

}
