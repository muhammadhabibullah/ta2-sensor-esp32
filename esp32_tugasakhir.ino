
#include "include.h"

void setup() {
    setupSerial();
    displayHomePage();
    connectSD();
    connectWifi();
    getCyclerData();
    setupInterfaceIO();   
}

void loop() {
    getGPS();
    getDateTime(currentDate, currentTime, GMT);
    displayChannel();
    startCycling();
    whileCycling();
    stopCycling();
    // postCyclerData();
}
