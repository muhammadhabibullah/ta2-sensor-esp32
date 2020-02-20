
// createCyclingDataFile create csv file with current date time name
void createCyclingDataFile() {
    sprintf(CD_FILEPATH, "/%s.csv", dateTimeStr);
    strReplace(CD_FILEPATH, ":", "");
    createFile(CD_FILEPATH);
    String cdFileHeader = "seconds,lat,long,alt,pace,bpm\r\n";
    appendFile(SD, CD_FILEPATH, cdFileHeader.c_str());
}

// saveCyclingData save cycling data to csv file
void saveCyclingData() {
    if (elapsedTime % 3 == 0) {
        String cdFileData = String(elapsedTime) + "," + String(currentLat) + "," + String(currentLong) + 
            "," + String(currentAltitude) + "," + String(currentSpeed) + "," + String(BPM) + "\r\n";
            appendFile(SD, CD_FILEPATH, cdFileData.c_str());
    }
}
