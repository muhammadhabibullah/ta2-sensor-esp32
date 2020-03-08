
void startCountPulse() {
    pulseCounter.attach_ms(2, ISRTr);
    pulsePauser.attach(5, pauseOrResumePulse);
}

void pauseOrResumePulse() {
    if (!PAUSING_PULSE) {
        pulseCounter.detach();
        PAUSING_PULSE = true;
    } else {
        pulseCounter.attach_ms(2, ISRTr);
        PAUSING_PULSE = false;
    }
}

void stopCountPulse() {
    pulseCounter.detach();
    pulsePauser.detach();
}

void checkIfBPMAbnormal() {
    if (BPM > cycler.maxHeartRate) {
        if (!OVER_BPM) {
            abnormalBPMPeriod = millis();
            OVER_BPM = true;
            LOW_BPM = false;
        }
    } else if ((BPM < 30) && (BPM != 0)){
        if (!LOW_BPM) {
            abnormalBPMPeriod = millis();
            OVER_BPM = false;
            LOW_BPM = true;
        }
    } else {
        OVER_BPM = false;
        LOW_BPM = false;
    }

    if ((OVER_BPM || LOW_BPM) && (millis()-abnormalBPMPeriod >= maxAbnormalBPMPeriod)) {
        CURRENT_CHANNEL = HEART_RATE;
        startBuzzer();
    } else {
        stopBuzzer();
    }
}