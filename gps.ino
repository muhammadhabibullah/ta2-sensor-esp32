
// Update current location using GPS
void getGPS() {
    totalSatellite = gps.satellites.value();

    if (gps.location.isValid() == 1) {
  
        currentLat = gps.location.lat();
        Serial.print("LAT = ");
        Serial.println(currentLat, 6);
        currentLong = gps.location.lng();
        Serial.print("LONG = ");
        Serial.println(currentLong, 6);
        currentAltitude = gps.altitude.meters();
        Serial.print("ALT = ");
        Serial.println(currentAltitude, 6);
        currentSpeed = gps.speed.kmph();
        Serial.print("SPEED = ");
        Serial.println(currentSpeed, 6);
    
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
