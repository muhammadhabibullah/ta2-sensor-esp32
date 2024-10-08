
// Get current date and time using GPS
void getDateTime(TinyGPSDate &d, TinyGPSTime &t, int gmt) {
    int gmtDiff = 0;
    if (gmt >= 0) {
        gmtDiff = 24 - gmt;
    }
    // TODO: add if GMT is less than zero
    
    if (d.isValid()) {
      
        currentDay = d.day();
        currentMonth = d.month();
        currentYear = d.year();

        if (gmt > 0) {
            if (t.hour() >= gmtDiff) {
              
                currentDay = currentDay + 1;

                // JAN / MAR / MAY / JUL / AUG / OCT / DEC
                if ((currentMonth == 1) || (currentMonth == 3) || (currentMonth == 5) || (currentMonth == 7) || (currentMonth == 8) || (currentMonth == 10) || (currentMonth == 12)) {
                    if (currentDay == 32){
                        currentDay = 1;
                        currentMonth = currentMonth + 1;
                    }
                }

                // FEB 
                else if (currentMonth == 2){

                    // LEAP OF YEAR
                    if (currentYear % 4 == 0){
                        if (currentDay == 30){
                            currentDay = 1;
                            currentMonth = currentMonth + 1;
                        }
                    }

                    else { 
                        if (currentDay == 29){
                            currentDay = 1;
                            currentMonth = currentMonth + 1;
                        }
                    }
                }

                // APR / JUN / SEP / NOV
                else {
                    if (currentDay == 31){
                        currentDay = 1;
                        currentMonth = currentMonth + 1;
                    }
                }

                // HAPPY NEW YEAR
                if (currentMonth == 13) {
                    currentMonth = 1;
                    currentYear = currentYear + 1;
                }
            }
        }
        // TODO: add if GMT is less than zero
    }
    
    if (t.isValid()){
        
        if (gmt > 0) {
            if (t.hour() >= gmtDiff) {
                currentHour = t.hour() - gmtDiff;
            }
            else {
                currentHour = t.hour() + gmt;
            }
            currentMinute = t.minute();
            currentSecond = t.second();
        }
        // TODO: add if GMT is less than zero
    }
}
