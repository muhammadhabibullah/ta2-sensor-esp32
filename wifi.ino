
// Initialize WLAN connection
void connectWifi() {
  
    Serial.print("Connecting to ");
    Serial.println(WLAN_SSID);
    WiFi.begin(WLAN_SSID, WLAN_PASS);
    unsigned long startConnectingWifiMillis = millis();
    while ((WiFi.status() != WL_CONNECTED) && ((millis() - startConnectingWifiMillis)/1000 <= CONNECTING_WIFI_TIMEOUT)) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    if (WiFi.status() == WL_CONNECTED) {
        IS_WIFI_CONNECTED = true;
        Serial.println("WiFi connected!");
    } else {
        IS_WIFI_CONNECTED = false;
        Serial.print("No ");
        Serial.print(WLAN_SSID);
        Serial.println(" wifi found!");
    }
    
    timeClient.begin();
    timeClient.setTimeOffset(25200);
    
}
