
// createCyclingDataFile create csv file with current date time name
void createCyclingDataFile() {
    sprintf(cyclingDataFileName, "%02d%02d%02d%02d%02d%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    sprintf(startDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    sprintf(CDR_FILEPATH, "/%s-raw.csv", cyclingDataFileName);
    createFile(CDR_FILEPATH);
}

// saveCyclingData save cycling data to csv file
void saveCyclingData() {
    if (elapsedTime % 3 == 0) {
        String cdFileData = String(elapsedTime) + "," + String(currentLat) + "," + String(currentLong) + 
            "," + String(currentAltitude) + "," + String(currentSpeed) + "," + String(BPM) + "\r\n";
            appendFile(SD, CDR_FILEPATH, cdFileData.c_str());
    }
}

// saveFinaleData save cycling finale data to csv file
void saveFinaleData() {
    sprintf(finishDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
    Serial.println("2a");
    sprintf(CDF_FILEPATH, "/%s-finale.csv", cyclingDataFileName);
    createFile(CDF_FILEPATH);
    String cdFileData = String(startDateTime) + "," + String(finishDateTime) +
        "," + String(totalDistance) + "," + String(totalElevation) + "," + String(averagePace) + 
        "," + String(averageBPM) + "\r\n";
    writeFile(SD, CDF_FILEPATH, cdFileData.c_str());
}
