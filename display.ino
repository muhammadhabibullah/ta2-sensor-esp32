
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
        u8g2.print("Memuat");
        u8g2.setFont(u8g2_font_glasstown_nbp_tf);
        u8g2.setCursor(40, 60);
        u8g2.print(" . . . . . ");  
    } while (u8g2.nextPage());
}

// Display cycling information based on current channel on OLED
void displayChannel() {
    if (((digitalRead(STOP_PIN) == LOW) && (!CYCLING)) || ((digitalRead(START_PIN) == LOW) && (CYCLING))) {
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

            case SENDING_DATA:
            displaySendingDataPage();
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
        sprintf(timeStr, "%02d:%02d:%02d", currentHour, currentMinute, currentSecond);
        printInformation(timeStr);
    }
    if (!d.isValid()) {
        printSubInformation(F("******** "));
    } else {
        sprintf(dateStr, "%02d/%02d/%02d", currentMonth, currentDay, currentYear);
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
    char bpmStr[15];
    sprintf(bpmStr, "%d", BPM);
    printInformation(bpmStr);
    printInformationUnit("bpm");
    if (OVER_BPM) {
        printSubInformation("Detak jantung Anda over!");
    } else if (LOW_BPM) {
        printSubInformation("Detak jantung Anda pelan!");
    }
}

// Display searching GPS page while GPS doesn't get a satellite signal yet on OLED
void displaySearchGPSPage() {
    printTitle("MEMUAT", 35, 10);
    printSubInformation("Tidak ada sinyal GPS!");
    printTotalSatellite();
}

// Display sending cycling data page
void displaySendingDataPage() {
    printTitle("MENGIRIM", 30, 10);
    printSubInformation("Mengirim data bersepeda...");
}
