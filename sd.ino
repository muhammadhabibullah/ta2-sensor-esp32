
// Initialize SD card module connection
void connectSD() {
    SD.begin(SD_CS_PIN);  
    if(!SD.begin(SD_CS_PIN)) {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }
    Serial.println("Initializing SD card...");
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }

    Serial.println("Success initialize SD card");
}
