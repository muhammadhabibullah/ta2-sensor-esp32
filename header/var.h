
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
WiFiClient wifiClient;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
SoftwareSerial GPSSerial(RX2_PIN, TX2_PIN);
TinyGPSPlus GPS;
HTTPClient http;

// WIFI
bool IS_WIFI_CONNECTED = false;
const int CONNECTING_WIFI_TIMEOUT = 30;

// FILE
const char* STORED_CD_FILEPATH =  "/stored_cycling_data.csv";

// CYCLER DATA
const int CD_JSON_TOTAL_OBJECTS = 4;
const int CD_JSON_STRING_BYTES = 28;
Cycler cycler;

// BUTTON
bool IS_CYCLING = false;

// DISPLAY
int CURRENT_CHANNEL = 0;
const int CLOCK = 0;
const int STOPWATCH = 1;
const int DISTANCE = 2;
const int PACE = 3;
const int ELEVATION = 4;
const int HEART_RATE = 5;
const int SEARCH_GPS = 99;
const int LAST_CHANNEL = 5;
unsigned long searchGPSMillis;
const int SEARCH_GPS_DISPLAY_TIME = 5;
static const unsigned char u8g2_logo_wave[] U8X8_PROGMEM = {
  0xE0, 0x03, 0x18, 0x00, 0xC4, 0x01, 0x32, 0x00, 0x8A, 0x01, 0x69, 0x00, 
  0x25, 0x00, 0x95, 0x01, 0x95, 0x01, 0x01, 0x00, };

// GPS
double currentLat, currentLong, currentAltitude, lastLat, lastLong, lastAltitude;
int totalSatellite, currentSpeed;
String currentHeading;
double totalDistance, totalElevation;
TinyGPSDate currentDate;
TinyGPSTime currentTime;

// CLOCK & STOPWATCH
int currentDay = 0, currentMonth = 0, currentYear = 0, currentHour = 0, currentMinute = 0, currentSecond = 0;
char *stopwatch = "00:00:00";
char dateTimeStr[20];
char dateStr[10];
char timeStr[8];
unsigned long elapsedTime, startTime;

// String formattedDate;
// String dayStamp;
// String timeStamp;
// RTC_DATA_ATTR int readingID = 0;
// String dataMessage;
