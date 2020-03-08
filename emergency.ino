
void checkIfEmergency() {
    if ((currentSpeed - gps.speed.kmph()) >= maxSpeedChange) {
        if (!DRASTIC_SPEED_CHANGE) {
            emergencyConfirmationTime = millis();
            DRASTIC_SPEED_CHANGE = true;
        }
    } else {
        if ((DRASTIC_SPEED_CHANGE) && ((millis() - emergencyConfirmationTime)/1000 > EMERGENCY_WARNING_DISPLAY_TIME)) {
            DRASTIC_SPEED_CHANGE = false;
            CURRENT_CHANNEL = CLOCK;
        }
    }
}