
void displayHomePage(){
  
    u8g2.begin();
    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_helvB12_tf);
        u8g2.setCursor(20, 20);
        u8g2.print("BERSEPEDA");
        u8g2.setFont(u8g2_font_nine_by_five_nbp_tf);
        u8g2.setCursor(0, 60);
        u8g2.print("Loading");
        u8g2.setFont(u8g2_font_glasstown_nbp_tf);
        u8g2.setCursor(40, 60);
        u8g2.print(" . . . . . ");  
    } while (u8g2.nextPage());
    
}

void displayChannel() {

    if (digitalRead(CHANNEL_PIN) == LOW) {
        CURRENT_CHANNEL = ++CURRENT_CHANNEL;
    }

    if((CURRENT_CHANNEL>LAST_CHANNEL) && (CURRENT_CHANNEL != SEARCH_GPS_CHANNEL)){
        CURRENT_CHANNEL = CLOCK_CHANNEL;
    }
    
    switch (CURRENT_CHANNEL) {
        case CLOCK_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print Clock");
            // printClock(GPS.date, GPS.time);
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case STOPWATCH_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print Stopwatch");
            // printStopwatch();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case DISTANCE_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print Distance");
            // printDistance(LAT, LONG);
        } while ( u8g2.nextPage() );
        delay(10);
        break;
          
        case PACE_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print pace");
            // printPace();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case ELEVATION_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print Elevation");
            // printElevation();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
  
        case HEART_RATE_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print HR");
            // printHeartRate();
        } while ( u8g2.nextPage() );
        delay(10);
        break;

        case SEARCH_GPS_CHANNEL:
        u8g2.firstPage();
        do {
            Serial.println("Print Search GPS");
            // printSearchGPS();  
        } while ( u8g2.nextPage() );
        delay(10);
        
        if ((millis() - searchGPSMillis)/1000 > SEARCH_GPS_DISPLAY_TIME) {
          CURRENT_CHANNEL = 0;
        }
        break;
    }
    
}
