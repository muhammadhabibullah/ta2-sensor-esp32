
// Update current location using GPS
void getGPS() {
    totalSatellite = gps.satellites.value();

    if (gps.location.isValid() == 1) {
  
        currentLat = gps.location.lat();
        currentLong = gps.location.lng();
        currentAltitude = gps.altitude.meters();
        currentSpeed = gps.speed.kmph();
        currentHeading = getMataAngin(gps.course.value());
    }
    
    smartDelay(1000);
  
    // if (millis() > 5000 && GPS.charsProcessed() < 10) {
    //   // Serial.println(F("No GPS detected: check wiring."));
    // }
}

// Make GPS not checking location rapidly 
static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while (Serial1.available())
        gps.encode(Serial1.read());
    } while (millis() - start < ms);
}
