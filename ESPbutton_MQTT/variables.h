#define PCA_ADDR 0x41 // PCA9536 I2C address
#define INP_REG 0
#define OUT_REG 1
#define POI_REG 2
#define CNF_REG 3

bool PCA = false; // if we found PCA on the bus then monitor PCA buttons

uint8_t butoane = 0;      // holds new button state info
uint8_t butoane_last = 0; // holds last button state info

float bat = 0;
// measure your ESP VCC voltage with a good multimeter
// should be around 3.30V
#define MEASURED 3.30
// enter the ESP reported voltage
// this will fluctuate from ESP to ESP
// i've seen up to 3.39V reported
#define REPORTED 3.30
#define FACTOR 1024 * MEASURED / REPORTED
// use MQTT to send yourself a reminder to change/recharge batteries when voltage drops below 3.0-2.9V

///////////////////////////////////////////////////////////////////////
// MQTT variables
///////////////////////////////////////////////////////////////////////
// will hold device mac for mqtt idetification
char mac[6];
char HOSTNAME[10];
// define topics based on mac
const char PREFIX[] = LOC "/";
const char WILL[] = "/status";
const char PUB[] = "/out";
const char SUB[] = "/in";
char MQTT_WILL_TOPIC[40];
char MQTT_PUB_TOPIC[40];
char MQTT_SUB_TOPIC[40];