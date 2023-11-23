#include "HX711.h"
#include <string.h>


// HX711 circuit wiring
const int leftFoot_LOADCELL_DOUT = 2;
const int leftFoot_LOADCELL_SCK = 3;

const int rightFoot_LOADCELL_DOUT = 4;
const int rightFoot_LOADCELL_SCK = 5;

HX711 leftFootHX, rightFootHX;

const int arraySize = 4;
bool leftPrev[arraySize] = { 1, 1, 1, 1 };
bool rightPrev[arraySize] = { 1, 1, 1, 1 };
unsigned long lastUpdatedTimeMillis = 0;

long limit = 240000;

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

bool isStep(long scale) {
  return scale > limit;
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
}

String prevStatus = "stop";
String currentStatus = "stop";

void loop() {
  if (leftFootHX.is_ready() || rightFootHX.is_ready()) {
    bool curLeftIsStep = isStep(leftFootHX.read());
    bool curRightIsStep = isStep(rightFootHX.read());

    if (leftPrev[3] != curLeftIsStep || rightPrev[3] != curRightIsStep) {
      shiftArray(leftPrev, arraySize);
      shiftArray(rightPrev, arraySize);
      leftPrev[3] = isStep(leftFootHX.read());
      rightPrev[3] = isStep(rightFootHX.read());
      lastUpdatedTimeMillis = millis();
    }
    // Serial.println("");

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

    if (prevStatus != currentStatus) {
      Serial.println(currentStatus);
      prevStatus = currentStatus;
    }

  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
}
