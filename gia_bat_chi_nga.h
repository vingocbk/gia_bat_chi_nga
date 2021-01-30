#include "AppDebug.h"
#include "Ticker.h"

#define RF0             5
#define RF1             14
#define RF2             4
#define PIN_LOA         13
#define MODE            16
#define L1              17
#define L2              18
#define L3              19
#define L4              21
#define BUTTON_UP       26
#define BUTTON_DOWN     27
#define I1IN            34
#define I2IN            35

#define MAX_ERROR       3050
#define MIN_ERROR       2950
int I1, I2;

const int freq = 5000;
const int L1UpChannel = 0;
const int L1DownChannel = 1;
const int L2UpChannel = 2;
const int L2DownChannel = 3;
const int resolution = 8;

int Max_L1_UP = 255;
int Max_L1_DOWN = 255;
int Max_L2_UP = 250;
int Max_L2_DOWN = 255;
bool isCaution = false;

int countCurrent = 0;
int countSpeaker = 0;
//int errorCrrent = 0;
//void Current();
//Ticker tickerCurrent(Current, 50);   //every 50ms
