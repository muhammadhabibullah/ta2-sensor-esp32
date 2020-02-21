
// Reset all cycling variable and set cycling status to TRUE when cycler push START button
void startCycling() {
    if((digitalRead(START_PIN) == LOW) && (!CYCLING)){
        // if ((GPS.time.isValid()) && (GPS.date.isValid()) && (currentDay != 0)) {
            CYCLING = true;
            totalElevation = 0;
            totalDistance = 0;
            startTime = millis();
            lastLat = GPS.location.lat();
            lastLong = GPS.location.lng();
            lastAltitude = GPS.altitude.meters();
            CURRENT_CHANNEL = STOPWATCH;
            // sprintf(startDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
            createCyclingDataFile();
            startCountPulse();
        // } else {
        //     CURRENT_CHANNEL = SEARCH_GPS;
        //     searchGPSMillis = millis();
        // }
    }
}

// Count all cycling metrics while cycling status is TRUE
void whileCycling() {
    if (CYCLING) {
        countDistance();
        countElevation();
        countTime();
        checkIfBPMAbnormal();
        saveCyclingData();
    }
}

// Stop counting cycling metrics, calculate cycling data and set cycling status to FALSE when cycler push STOP button
void stopCycling() {
    if((digitalRead(STOP_PIN) == LOW) && (CYCLING)){
        CYCLING = false;
        sprintf(finishDateTime, "%02d-%02d-%02dT%02d:%02d:%02d", currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond);
        stopCountPulse();
        stopBuzzer();
        calculateCyclingData();
        saveFinaleData();
    }
}

// Send cycling data from SD card when connected to internet
void sendCyclingData() {
    // jika ada data yg belum dikirim ke server
    // connectWifi();  
    // sendDataFromSD(); 
}
