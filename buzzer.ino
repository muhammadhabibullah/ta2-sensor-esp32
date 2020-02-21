
void stopBuzzer() {
    pinMode(BUZZER_PIN, INPUT);
    EasyBuzzer.stopBeep();
}

void startBuzzer() {
    pinMode(BUZZER_PIN, OUTPUT);
    if (millis()-lastPeriodStart>=periodDuration){
        lastPeriodStart+=periodDuration;
        EasyBuzzer.singleBeep(frequency, onDuration);
    } else {
        stopBuzzer();
    }
}
