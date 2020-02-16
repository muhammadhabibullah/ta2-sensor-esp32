
// Reset all cycling variable and set cycling status to TRUE when cycler push START button
void startCycling() {
    if((digitalRead(START_PIN) == LOW) && (!IS_CYCLING)){
        if ((GPS.time.isValid()) && (GPS.date.isValid())) { //  && (currentDay != 0)
            IS_CYCLING = true;
            totalElevation = 0;
            totalDistance = 0;
            startTime = millis();
            lastLat = GPS.location.lat();
            lastLong = GPS.location.lng();
            lastAltitude = GPS.altitude.meters();
            CURRENT_CHANNEL = STOPWATCH;
            startCountPulse();
        } else {
            CURRENT_CHANNEL = SEARCH_GPS;
            searchGPSMillis = millis();
        }
    }
}

// Count all cycling metrics while cycling status is TRUE
void whileCycling() {
    if (IS_CYCLING) {
        countDistance();
        countElevation();
        countTime();
        //   saveRawData();
        //   checkIfBPMAbnormal();
    }
}

// Stop counting cycling metrics, calculate cycling data and set cycling status to FALSE when cycler push STOP button
void stopCycling() {
    if((digitalRead(STOP_PIN) == LOW) && (IS_CYCLING)){
        IS_CYCLING = false;
        stopCountPulse();
        //   calculateCyclingData();
        //   saveFinaleData();
    }
}

// Send cycling data from SD card when connected to internet
void sendCyclingData() {
    // jika ada data yg belum dikirim ke server
    // connectWifi();  
    // sendDataFromSD(); 
}
