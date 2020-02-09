
void getGPS() {

    currentDate = GPS.date;
    currentTime = GPS.time;
  
    totalSatellite = GPS.satellites.value();
    Serial.print("Total Satellite = ");
    Serial.println(totalSatellite, 6);
        
    if (GPS.location.isValid() == 1) {
  
        currentLat = GPS.location.lat();
        Serial.print("LAT = ");
        Serial.println(currentLat, 6);
        currentLong = GPS.location.lng();
        Serial.print("LONG = ");
        Serial.println(currentLong, 6);
        currentAltitude = GPS.altitude.meters();
        Serial.print("ALT = ");
        Serial.println(currentAltitude, 6);
        currentSpeed = GPS.speed.kmph();
        Serial.print("SPEED = ");
        Serial.println(currentSpeed, 6);
    
        currentHeading = GPS.cardinal(GPS.course.value());
    }
    
    smartDelay(1000);
  
    if (millis() > 5000 && GPS.charsProcessed() < 10) {
      Serial.println(F("No GPS detected: check wiring."));
    }
}


static void smartDelay(unsigned long ms) {
    unsigned long start = millis();
    do {
        while (GPSSerial.available())
        GPS.encode(GPSSerial.read());
    } while (millis() - start < ms);
}
