
// Display home page of sensor system interface on OLED
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

// Display cycling information based on current channel on OLED
void displayChannel() {
    if (((digitalRead(STOP_PIN) == LOW) && (!IS_CYCLING)) || ((digitalRead(START_PIN) == LOW) && (IS_CYCLING))) {
        CURRENT_CHANNEL = ++CURRENT_CHANNEL;
    }

    if((CURRENT_CHANNEL>LAST_CHANNEL) && (CURRENT_CHANNEL != SEARCH_GPS)){
        CURRENT_CHANNEL = CLOCK;
    }

    u8g2.firstPage();
    do {
        switch (CURRENT_CHANNEL) {
            case CLOCK:
            displayClock(GPS.date, GPS.time);
            break;

            case STOPWATCH:
            displayStopwatch();
            break;

            case DISTANCE:
            displayDistance();
            break;

            case PACE:
            displayPace();
            break;

            case ELEVATION:
            displayElevation();
            break;

            case HEART_RATE:
            displayHeartRate();
            break;

            case SEARCH_GPS:
            displaySearchGPSPage();
            if ((millis() - searchGPSMillis)/1000 > SEARCH_GPS_DISPLAY_TIME) {
                CURRENT_CHANNEL = 0;
            }
            break;
        }
    } while ( u8g2.nextPage() );
    delay(10);
}

// Display time on OLED
void displayClock(TinyGPSDate &d, TinyGPSTime &t) {
    printTitle("JAM", 50, 10);
    if (!t.isValid()) {
        printInformation(F("******** "));
    } else {
        printInformation(timeStr);
    }
    if (!d.isValid()) {
        printSubInformation(F("******** "));
    } else {
        printSubInformation(dateStr);
    }
    printTotalSatellite();
}

// Display stopwatch on OLED
void displayStopwatch() {
    printTitle("STOPWATCH", 25, 10);
    printInformation(stopwatch);
    if (cycler.target.finishTime != 0) {
        int timeTarget = getTargetPercentage(STOPWATCH);
        String timeTargetStr = "Target: " + String(timeTarget) + "%";
        printSubInformation(timeTargetStr);
    }
}

// Display total distance on OLED
void displayDistance() {
    printTitle("JARAK TEMPUH", 10, 10);
    char totalDistanceStr[15];
    sprintf(totalDistanceStr, "%.1f", totalDistance);
    printInformation(totalDistanceStr);
    printInformationUnit("km");
    if (cycler.target.distance != 0) {
        int distanceTarget = getTargetPercentage(DISTANCE);
        String distanceTargetStr = "Target: " + String(distanceTarget) + "%";
        printSubInformation(distanceTargetStr);
    }
    printTotalSatellite();
}

// Display current pace on OLED
void displayPace() {
    printTitle("KECEPATAN", 22, 10);
    char speedStr[15];
    sprintf(speedStr, "%d", currentSpeed);
    printInformation(speedStr);
    printInformationUnit("km/jam");
    printSubInformation(currentHeading);
    printTotalSatellite();
}

// Display total elevation on OLED
void displayElevation() {
    printTitle("KETINGGIAN", 20, 10);
    char totalElevationStr[15];
    sprintf(totalElevationStr, "%.1f m", totalElevation);
    printInformation(totalElevationStr);
    printInformationUnit("m");
    if (cycler.target.elevation != 0) {
        int elevationTarget = getTargetPercentage(ELEVATION);
        String elevationTargetStr = "Target: " + String(elevationTarget) + "%";
        printSubInformation(elevationTargetStr);
    }
    printTotalSatellite();
}

// Display current heart rate on OLED
void displayHeartRate() {
    printTitle("DETAK JANTUNG", 5, 10);
}

// Display searching GPS page while GPS doesn't get a satellite signal yet on OLED
void displaySearchGPSPage() {
    printTitle("LOADING", 35, 10);
    printSubInformation("No GPS signal!");
    printTotalSatellite();
}

// Print title on the top of OLED
void printTitle(String title, int xCursor, int yCursor) {
    u8g2.setFont(u8g2_font_crox1cb_tf);
    u8g2.setCursor(xCursor, yCursor);
    u8g2.print(title);
    u8g2.drawLine(0,12,128,12);
}

// Print main information on the center of OLED
void printInformation(String info) {
    u8g2.setFont(u8g2_font_t0_22b_tn);
    u8g2.setCursor(20, 42);
    u8g2.print(info);
}

// Print sub-information on the bottom-left of OLED
void printSubInformation(String info) {
    u8g2.setFont(u8g2_font_nine_by_five_nbp_tf);
    u8g2.setCursor(0, 60);
    u8g2.print(info);
}

// Print information unit beside the information
void printInformationUnit(String unit) {
    u8g2.setFont(u8g2_font_glasstown_nbp_tf);
    u8g2.setCursor(90, 42);
    u8g2.print(unit);
}

// Print total satellite signal on the bottom-right of OLED
void printTotalSatellite() {
    u8g2.setFont(u8g2_font_courB08_tn);
    u8g2.setCursor(105, 64);
    u8g2.print(totalSatellite, 5);
    u8g2.drawXBMP(118, 54, 10, 10, u8g2_logo_wave);
}
