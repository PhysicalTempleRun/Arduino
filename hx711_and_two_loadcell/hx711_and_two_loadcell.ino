#include "HX711.h"

// HX711 circuit wiring
const int leftFoot_LOADCELL_DOUT = 2;
const int leftFoot_LOADCELL_SCK = 3;

const int rightFoot_LOADCELL_DOUT = 4;
const int rightFoot_LOADCELL_SCK = 5;

HX711 leftFootHX, rightFootHX;

void setup() {
  Serial.begin(9600);
  leftFootHX.begin(leftFoot_LOADCELL_DOUT, leftFoot_LOADCELL_SCK);
  rightFootHX.begin(rightFoot_LOADCELL_DOUT, rightFoot_LOADCELL_SCK);
}

void loop() {

  if (leftFootHX.is_ready() || rightFootHX.is_ready()) {
    long leftFoot_reading = leftFootHX.read();
    long rightFoot_reading = rightFootHX.read();
    //Serial.print("left reading: ");
    Serial.print(leftFoot_reading);
    //Serial.print("right reading: ");
    Serial.print(" ");
    Serial.println(rightFoot_reading);
    //Serial.println();
  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
  
}