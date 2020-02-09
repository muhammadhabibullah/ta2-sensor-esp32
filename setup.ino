
void setupSerial() {

    Serial.begin(115200);
    GPSSerial.begin(9600);

}

void setupInterfaceIO() {
  
    pinMode(START_STOP_PIN, INPUT_PULLUP);
    pinMode(CHANNEL_PIN, INPUT_PULLUP);
    // pinMode(LED_PIN, OUTPUT);
    // pinMode(BUZZER_PIN, OUTPUT);
    
}
