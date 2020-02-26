
void countDistance() {
    double distanceBetweenTwoPoints = 
    (double)TinyGPSPlus::distanceBetween(
    currentLat,
    currentLong,
    lastLat,
    lastLong ) / 1000.0;

    if (distanceBetweenTwoPoints <= 10) {
        totalDistance = totalDistance + distanceBetweenTwoPoints;
    }
    
    lastLat = currentLat;
    lastLong = currentLong;

    Serial.print("Total distance: ");
    Serial.println(totalDistance);
}

void countElevation() {
    double elevationBetweenTwoPoints = currentAltitude - lastAltitude;
    if (elevationBetweenTwoPoints < 0)  || (elevationBetweenTwoPoints > 3){
      elevationBetweenTwoPoints = 0;
    }
    
    totalElevation = totalElevation + elevationBetweenTwoPoints;
    
    lastAltitude = currentAltitude; 

    Serial.print("Total elevation: ");
    Serial.println(totalElevation);
}

void countTime() {
    elapsedTime = (millis() - startTime) / 1000; 

    unsigned short elapsedSeconds, elapsedMinutes, elapsedHours;
    secondsToHMS(elapsedTime, elapsedHours, elapsedMinutes, elapsedSeconds);
    
    sprintf(stopwatch, "%02d:%02d:%02d ", elapsedHours, elapsedMinutes, elapsedSeconds);
    Serial.print("Stopwatch: ");
    Serial.println(stopwatch);
}

static void secondsToHMS(const uint32_t seconds, uint16_t &h, uint16_t &m, uint16_t &s ){
    uint32_t t = seconds;
    s = t % 60;
    t = (t - s)/60;
    m = t % 60;
    t = (t - m)/60;
    h = t;
}
