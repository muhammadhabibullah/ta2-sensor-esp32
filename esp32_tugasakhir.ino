
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TinyGPS++.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include "h_config.h"
#include "h_pin.h"
#include "h_type.h"
#include "h_var.h"

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
    // stopCycling();
    // postCyclerData();
}
