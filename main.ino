
#include "include.h"

void setup() {
    setupSerial();
    setupInterfaceIO();
    displayHomePage();
    connectSD();
    connectWifi();
    connectBroker();
    getCyclerData();
}

void loop() {
    mqttClient.loop();
    getGPS();
    getDateTime(gps.date, gps.time, GMT);
    displayChannel();
    startCycling();
    whileCycling();
    stopCycling();
}
