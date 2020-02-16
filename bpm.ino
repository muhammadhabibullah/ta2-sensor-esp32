
void startCountPulse() {
    if (!COUNTING_PULSE) {
        pulseCounter.attach_ms(2, ISRTr);
        pulsePauser.attach(5, pauseOrResumePulse);
        COUNTING_PULSE = true;
    }
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
    COUNTING_PULSE = false;
}

void checkIfBPMAbnormal() {
    if (BPM > (220 - cycler.yearAge)) {
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