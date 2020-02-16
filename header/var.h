
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
WiFiClient wifiClient;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
// SoftwareSerial GPSSerial(RX2_PIN, TX2_PIN);
TinyGPSPlus GPS;
HTTPClient http;
Ticker pulseCounter, pulsePauser;

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
bool CYCLING = false;

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
char stopwatch[32];
char dateTimeStr[20];
char dateStr[32];
char timeStr[8];
unsigned long elapsedTime, startTime;

// BPM
bool PAUSING_PULSE = false;
bool LOW_BPM = false;
bool OVER_BPM = false;
// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM = 0;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

volatile int rate[10];                    // array to hold last ten IBI values
volatile unsigned long sampleCounter = 0; // used to determine pulse timing
volatile unsigned long lastBeatTime = 0;  // used to find IBI
volatile int P =512;                      // used to find peak in pulse wave, seeded
volatile int T = 512;                     // used to find trough in pulse wave, seeded
volatile int thresh = 512;                // used to find instant moment of heart beat, seeded
volatile int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
volatile boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
volatile boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM

// BUZZER
unsigned int frequency = 1000;
unsigned int beeps = 3;

// String formattedDate;
// String dayStamp;
// String timeStamp;
// RTC_DATA_ATTR int readingID = 0;
// String dataMessage;
