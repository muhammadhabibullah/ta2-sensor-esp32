
// createRawDataFile create csv file with current date time name
void createRawDataFile() {
    sprintf(cyclingDataFileName, "%02d%02d%02d%02d%02d%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    sprintf(startDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    sprintf(CDR_FILEPATH, "/%s-raw.csv", cyclingDataFileName);
    createFile(CDR_FILEPATH);
}

// saveRawData save cycling data to csv file
void saveRawData() {
    if (elapsedTime % 3 == 0) {
        String cdFileData = String(elapsedTime) + "," + String(currentLat) + "," + String(currentLong) + 
            "," + String(currentAltitude) + "," + String(currentSpeed) + "," + String(BPM) + "\r\n";
            appendFile(SD, CDR_FILEPATH, cdFileData.c_str());
    }
}

// saveFinaleData save cycling finale data to csv file
void saveFinaleData() {
    sprintf(finishDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    sprintf(CDF_FILEPATH, "/%s-finale.csv", cyclingDataFileName);
    createFile(CDF_FILEPATH);
    String cdFileData = String(startDateTime) + "," + String(finishDateTime) +
        "," + String(totalDistance) + "," + String(totalElevation) + "," + String(averagePace) + 
        "," + String(averageBPM) + "\r\n";
    writeFile(SD, CDF_FILEPATH, cdFileData.c_str());
}

// calculateData count average pace & BPM when cycling based on raw data on csv file
void calculateData() {
    int countPace;
    int countBPM;
    String str;

    File file = SD.open(CDR_FILEPATH);
    if (!file) {
        Serial.print(CDR_FILEPATH);
        Serial.println(" file doesn't exist");
    } else {
        int countComma;
        int singlePace;
        int singleBPM;
        while (file.available()) {
            str = file.readStringUntil(',');
            countComma = ++countComma;
            if (countComma % 5 == 0) {
                singlePace = str.toInt();
                if (singlePace != 0) {
                    averagePace = ((averagePace * countPace) + singlePace) / (countPace + 1);
                    countPace = ++countPace;
                }
                
                str = file.readStringUntil('\r\n');
                singleBPM = str.toInt();
                if (singleBPM != 0) {
                    averageBPM = ((averageBPM * countBPM) + singleBPM) / (countBPM + 1);
                    countBPM = ++countBPM;
                }
            }
        }
    }
    file.close();
}

// Send cycling data from SD card when connected to internet
void sendData() {
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    while (!mqttClient.connected()) {
        delay(1000);
        Serial.print(".");
    }
    CURRENT_CHANNEL = SENDING_DATA;
    displayChannel();

    parseAndUploadData(CDF_FILEPATH);
    parseAndUploadData(CDR_FILEPATH);

    CURRENT_CHANNEL = CLOCK;
}

void parseAndUploadData(char * path) {
    File file = SD.open(path);
    if (!file) {
        Serial.print(path);
        Serial.println(" file doesn't exist");
    } else {
        Serial.print("Reading ");
        Serial.print(path);
        Serial.println(" file ..");
        strncpy(checkFilePath, path + 16, 3);
        if ((strcmp("fin", checkFilePath)) == 0) {
            while (file.available()) {
                docRaw["b"] = String(BICYCLE_ID);
                readSDStr = file.readStringUntil(',');
                docRaw["s"] = readSDStr;
                readSDStr = file.readStringUntil(',');
                docRaw["f"] = readSDStr;
                readSDStr = file.readStringUntil(',');
                docRaw["d"] = roundf(readSDStr.toDouble()*100.0)/100.0;
                readSDStr = file.readStringUntil(',');
                docRaw["e"] = roundf(readSDStr.toDouble()*100.0)/100.0;
                readSDStr = file.readStringUntil(',');
                docRaw["p"] = roundf(readSDStr.toDouble()*100.0)/100.0;
                readSDStr = file.readStringUntil('\r\n');
                docRaw["h"] = readSDStr.toInt();
                serializeJson(docRaw, JSONRawBuffer);

                publishFinaleData();
            }
        } else if ((strcmp("raw", checkFilePath)) == 0) {
            while (file.available()) {
                docFin["b"] = String(BICYCLE_ID);
                readSDStr = file.readStringUntil(',');
                docFin["s"] = readSDStr.toInt();
                readSDStr = file.readStringUntil(',');
                docFin["t"] = readSDStr.toDouble();
                readSDStr = file.readStringUntil(',');
                docFin["g"] = readSDStr.toDouble();
                readSDStr = file.readStringUntil(',');
                docFin["a"] = roundf(readSDStr.toDouble()*100.0)/100.0;
                readSDStr = file.readStringUntil(',');
                docFin["p"] = roundf(readSDStr.toDouble()*100.0)/100.0;
                readSDStr = file.readStringUntil('\r\n');
                docFin["h"] = readSDStr.toInt();
                serializeJson(docFin, JSONFinBuffer);

                publishRawData();
            }
        }
        strncpy(clearFilePath, path + 1, 18);
        sprintf(renamedFile, "/xx-%s.csv", clearFilePath);
        renameFile(path, renamedFile);
    }
    file.close();
}
