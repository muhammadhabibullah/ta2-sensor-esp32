
// calculateCyclingData count average pace & BPM when cycling based on raw data on csv file
void calculateCyclingData() {
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