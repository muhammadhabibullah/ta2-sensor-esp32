
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

    if((CURRENT_CHANNEL>LAST_CHANNEL) && (CURRENT_CHANNEL != SEARCH_GPS)){
        CURRENT_CHANNEL = CLOCK;
    }
    
    switch (CURRENT_CHANNEL) {
        case CLOCK:
        u8g2.firstPage();
        do {
            displayClock();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case STOPWATCH:
        u8g2.firstPage();
        do {
            // Serial.println("Print Stopwatch");
            displayStopwatch();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case DISTANCE:
        u8g2.firstPage();
        do {
            // Serial.println("Print Distance");
            displayDistance();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
          
        case PACE:
        u8g2.firstPage();
        do {
            // Serial.println("Print pace");
            displayPace();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
        
        case ELEVATION:
        u8g2.firstPage();
        do {
            // Serial.println("Print Elevation");
            displayElevation();
        } while ( u8g2.nextPage() );
        delay(10);
        break;
  
        case HEART_RATE:
        u8g2.firstPage();
        do {
            // Serial.println("Print HR");
            displayHeartRate();
        } while ( u8g2.nextPage() );
        delay(10);
        break;

        case SEARCH_GPS:
        u8g2.firstPage();
        do {
            // Serial.println("Print Search GPS");
            displaySearchGPSPage();  
        } while ( u8g2.nextPage() );
        delay(10);
        
        if ((millis() - searchGPSMillis)/1000 > SEARCH_GPS_DISPLAY_TIME) {
          CURRENT_CHANNEL = 0;
        }
        break;
    }
    
}

void displayClock() {
    printTitle("JAM", 50, 10);
    printInformation(timeStr, 20, 42);
    printSubInformation(dateStr, 0, 64);
    printTotalSatellite();
}

void displayStopwatch() {
    printTitle("STOPWATCH", 50, 10);
    printInformation(stopwatch, 25, 10);
    if (cycler.target.finishTime != 0) {
        int timeTarget = getTargetPercentage(STOPWATCH);
        String timeTargetStr = "Target: " + String(timeTarget) + "%";
        printSubInformation(timeTargetStr, 0, 60);
    }
}

void displayDistance() {
    printTitle("JARAK TEMPUH", 10, 10);
    String totalDistanceStr = String(totalDistance) + " km";
    printInformation(totalDistanceStr, 25, 10);
    if (cycler.target.distance != 0) {
        int distanceTarget = getTargetPercentage(DISTANCE);
        String distanceTargetStr = "Target: " + String(distanceTarget) + "%";
        printSubInformation(distanceTargetStr, 0, 60);
    }
    printTotalSatellite();
}

void displayPace() {
    printTitle("KECEPATAN", 22, 10);
    String speedStr = String(currentSpeed) + " km/jam";
    printInformation(speedStr, 25, 10);
    String headingStr = "Direction: " + currentHeading;
    printSubInformation(headingStr, 0, 60);
    printTotalSatellite();
}

void displayElevation() {
    printTitle("KETINGGIAN", 20, 10);
    String totalElevationStr = String(totalElevation) + " m";
    printInformation(totalElevationStr, 25, 10);
    if (cycler.target.elevation != 0) {
        int elevationTarget = getTargetPercentage(ELEVATION);
        String elevationTargetStr = "Target: " + String(elevationTarget) + "%";
        printSubInformation(elevationTargetStr, 0, 60);
    }
    printTotalSatellite();
}

void displayHeartRate() {
    printTitle("DETAK JANTUNG", 5, 10);
}

void displaySearchGPSPage() {
    printTitle("LOADING", 20, 10);
    printSubInformation("Searching GPS signal . . . . . .", 0, 60);
    printTotalSatellite();
}

void printTitle(String title, int xCursor, int yCursor) {
    u8g2.setFont(u8g2_font_crox1cb_tf);
    u8g2.setCursor(xCursor, yCursor);
    u8g2.print(title);
    u8g2.drawLine(0,12,128,12);
}

void printInformation(String info, int xCursor, int yCursor) {
    u8g2.setFont(u8g2_font_t0_22b_tn);
    u8g2.setCursor(xCursor, yCursor);
    u8g2.print(info);
}

void printSubInformation(String info, int xCursor, int yCursor) {
    u8g2.setFont(u8g2_font_nine_by_five_nbp_tf);
    u8g2.setCursor(xCursor, yCursor);
    u8g2.print(info);
}

void printTotalSatellite() {
    u8g2.setFont(u8g2_font_courB08_tn);
    u8g2.setCursor(105, 64);
    u8g2.print(totalSatellite, 5);
    u8g2.drawXBMP(118, 54, 10, 10, u8g2_logo_wave);
}
