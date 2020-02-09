
#include "include.h"

void setup() {
    setupSerial();
    setupInterfaceIO();
    displayHomePage();
    connectSD();
    connectWifi();
    getCyclerData();
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
