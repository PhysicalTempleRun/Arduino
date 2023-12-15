#include "HX711.h"
#include <string.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


// HX711 circuit wiring
const int leftFoot_LOADCELL_DOUT = 2;
const int leftFoot_LOADCELL_SCK = 3;

const int rightFoot_LOADCELL_DOUT = 4;
const int rightFoot_LOADCELL_SCK = 5;

HX711 leftFootHX, rightFootHX;

//led 관련 상수
const int LEFT_LED_PIN = 6;
const int RIGHT_LED_PIN = 7;
const int LED_COUNT = 60;
Adafruit_NeoPixel leftStrip(LED_COUNT, LEFT_LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightStrip(LED_COUNT, RIGHT_LED_PIN, NEO_GRB + NEO_KHZ800);



const int arraySize = 4;
bool leftPrev[arraySize] = { 1, 1, 1, 1 };
bool rightPrev[arraySize] = { 1, 1, 1, 1 };
unsigned long lastUpdatedTimeMillis = 0;

long leftLimit = 500000;
long rightLimit = 600000;

void shiftArray(bool arr[], int size) {
  for (int i = 0; i < size - 1; i++) {
    arr[i] = arr[i + 1];
  }
}

void printArray(bool arr[], int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i]) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    Serial.print(" ");
  }
  Serial.println("");
}

bool isLeftStep(long scale) {
  if(leftPrev[3]==0) return scale > leftLimit-1000;
  return scale > leftLimit;
}

bool isRightStep(long scale) {
  //Serial.println(scale);
  if(rightPrev[3]==0) return scale < rightLimit + 1000;
  return scale < rightLimit;
}

int firstPixelHueBy256 = 0;

void rainbow(Adafruit_NeoPixel* strip) {
  strip->rainbow(firstPixelHueBy256*256*20);
  strip->show();
  firstPixelHueBy256++;
}

void deem(Adafruit_NeoPixel* strip) {
  strip->clear();
  strip->show();
}


bool isStart() {
  if (leftPrev[3] != leftPrev[2]
      && rightPrev[3] != rightPrev[2]
      && leftPrev[3] != rightPrev[3]) {
    return true;
  }
  return false;
}

bool isStop() {
  return millis() - lastUpdatedTimeMillis > 2000;
}

bool isJump() {
  if (leftPrev[3] == 0 && rightPrev[3] == 0) {
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(9600);
  leftFootHX.begin(leftFoot_LOADCELL_DOUT, leftFoot_LOADCELL_SCK);
  rightFootHX.begin(rightFoot_LOADCELL_DOUT, rightFoot_LOADCELL_SCK);

  leftStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  leftStrip.show();            // Turn OFF all pixels ASAP
  leftStrip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

  rightStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  rightStrip.show();            // Turn OFF all pixels ASAP
  rightStrip.setBrightness(50);
}

String prevStatus = "stop";
String currentStatus = "stop";

void loop() {
  if (leftFootHX.is_ready() || rightFootHX.is_ready()) {
    bool curLeftIsStep = isLeftStep(leftFootHX.read());
    bool curRightIsStep = isRightStep(rightFootHX.read());

    if (leftPrev[3] != curLeftIsStep || rightPrev[3] != curRightIsStep) {
      shiftArray(leftPrev, arraySize);
      shiftArray(rightPrev, arraySize);
      leftPrev[3] = isLeftStep(leftFootHX.read());
      rightPrev[3] = isRightStep(rightFootHX.read());
      lastUpdatedTimeMillis = millis();
    }
    // Serial.println("");

    if(leftPrev[3]==1) {
      rainbow(&leftStrip);
    } else {
      deem(&leftStrip);
    }

    if(rightPrev[3]==1) {
      rainbow(&rightStrip);
    } else {
      deem(&rightStrip);
    }

    bool start = isStart();
    bool stop = isStop();
    bool jump = isJump();

    if (stop) {
      currentStatus = "stop";
    } else if (start) {
      currentStatus = "start";
    } else if (jump) {
      currentStatus = "jump";
    }

    // Serial.print("left : ");
    // printArray(leftPrev,4);
    // Serial.print("right : ");
    // printArray(rightPrev,4);

    if(prevStatus == "start" && currentStatus == "start") {
      Serial.println("start");
    }
    else if (prevStatus != currentStatus) {
      Serial.println(currentStatus);
      prevStatus = currentStatus;
    }

  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
}
