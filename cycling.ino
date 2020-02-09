
void startCycling() {

    if((digitalRead(START_STOP_PIN) == LOW) && (IS_CYCLING == false)){
        if ((GPS.time.isValid()) && (GPS.date.isValid())) { //  && (currentDay != 0)
            IS_CYCLING == true;
            totalElevation = 0;
            totalDistance = 0;
            startTime = millis();
            lastLat = GPS.location.lat();
            lastLong = GPS.location.lng();
            lastAltitude = GPS.altitude.meters();
            CURRENT_CHANNEL = STOPWATCH_CHANNEL;
        } else {
            CURRENT_CHANNEL = SEARCH_GPS_CHANNEL;
            searchGPSMillis = millis();
        }
    }
    
}

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

void stopCycling() {

    if((digitalRead(START_STOP_PIN) == LOW) && (IS_CYCLING == true)){
        //   calculateCyclingData();
        //   saveFinaleData();
    }
    
}
void sendCyclingData() {
    // jika ada data yg belum dikirim ke server
    // connectWifi();  
    // sendDataFromSD(); 
}
