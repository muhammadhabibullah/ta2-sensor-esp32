
// createCyclingDataFile create csv file with current date time name
void createCyclingDataFile() {
    sprintf(CDR_FILEPATH, "/%s-raw.csv", startDateTime);
    strReplace(CDR_FILEPATH, ":", "");
    createFile(CDR_FILEPATH);
    // String cdFileHeader = "seconds,lat,long,alt,pace,bpm\r\n";
    // appendFile(SD, CDR_FILEPATH, cdFileHeader.c_str());
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
    sprintf(CDF_FILEPATH, "/%s-finale.csv", startDateTime);
    strReplace(CDF_FILEPATH, ":", "");
    createFile(CDF_FILEPATH);
    // String cdFileHeader = "bid,start,finish,distance,elevation,pace,bpm\r\n";
    // appendFile(SD, CDF_FILEPATH, cdFileHeader.c_str());
    String cdFileData = String(BICYCLE_ID) + "," + String(startDateTime) + "," + String(finishDateTime) +
        "," + String(totalDistance) + "," + String(totalElevation) + "," + String(averagePace) + 
        "," + String(averageBPM) + "\r\n";
    appendFile(SD, CDF_FILEPATH, cdFileData.c_str());
}
