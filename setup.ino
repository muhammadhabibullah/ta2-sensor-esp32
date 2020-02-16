
// Setup serial monitor & GPS baud
void setupSerial() {
    Serial.begin(115200);
    Serial1.begin(9600, SERIAL_8N1, RX2_PIN, TX2_PIN);
}

// Setup pin mode for button, buzzer, and LED
void setupInterfaceIO() {
    pinMode(START_PIN, INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    EasyBuzzer.setPin(BUZZER_PIN);
}
