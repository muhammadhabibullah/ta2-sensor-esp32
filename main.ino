
#include "include.h"

void setup() {
    setupSerial();
    setupInterfaceIO();
    displayHomePage();
    connectSD();
    connectWifi();
    connectBroker();
    getCyclerData();
    // createFile(STORED_CD_FILEPATH);
}

void loop() {
    mqttClient.loop();
    getGPS();
    getDateTime(currentDate, currentTime, GMT);
    displayChannel();
    startCycling();
    whileCycling();
    stopCycling();
}
