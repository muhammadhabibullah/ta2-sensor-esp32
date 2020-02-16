
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
