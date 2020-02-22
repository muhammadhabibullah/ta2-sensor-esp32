
void readCyclingData(char * path) {
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
        Serial.println(path);
        // modify path
        strncpy(clearFilePath, path + 1, 18);
        sprintf(renamedFile, "/xx-%s.csv", clearFilePath);
        Serial.println(renamedFile);
        renameFile(path, renamedFile);
    }
    file.close();
}
