
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
        OVER_BPM = true;
        LOW_BPM = false;
    } else if (BPM < 30) {
        OVER_BPM = false;
        LOW_BPM = true;
    } else {
        OVER_BPM = false;
        LOW_BPM = false;
    }

    if (OVER_BPM || LOW_BPM) {
        CURRENT_CHANNEL = HEART_RATE;
        EasyBuzzer.beep(frequency, beeps);
        EasyBuzzer.stopBeep();
        // EasyBuzzer.update();
    }
}