
// Reset all cycling variable and set cycling status to TRUE when cycler push START/STOP button
void startCycling() {

    if((digitalRead(START_STOP_PIN) == LOW) && (IS_CYCLING == false)){
        if ((GPS.time.isValid()) && (GPS.date.isValid())) { //  && (currentDay != 0)
            IS_CYCLING == true;
            totalElevation = 0;
            totalDistance = 0;
            stopwatch = "00:00:00";
            startTime = millis();
            lastLat = GPS.location.lat();
            lastLong = GPS.location.lng();
            lastAltitude = GPS.altitude.meters();
            CURRENT_CHANNEL = STOPWATCH;
        } else {
            CURRENT_CHANNEL = SEARCH_GPS;
            searchGPSMillis = millis();
        }
    }
    
}

// Count all cycling metrics while cycling status is TRUE
void whileCycling() {
    
    if (IS_CYCLING == true) {
        countDistance();
        countElevation();
        countTime();
        //   countBPM(); // count every 5 secs??
        //   saveRawData();
        //   checkIfBPMAbnormal();
    }
    
}

// Stop counting cyicling metrics, calculate cycling data and set cycling status to FALSE when cycler push START/STOP button
void stopCycling() {

    if((digitalRead(START_STOP_PIN) == LOW) && (IS_CYCLING == true)){
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
