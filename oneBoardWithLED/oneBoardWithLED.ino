
#include "HX711.h"
#include <string.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


// HX711 circuit wiring
const int leftFoot_LOADCELL_DOUT = 2;
const int leftFoot_LOADCELL_SCK = 3;

HX711 leftFootHX;

//led 관련 상수
const int LEFT_LED_PIN = 6;
const int LED_COUNT = 60;
Adafruit_NeoPixel leftStrip(LED_COUNT, LEFT_LED_PIN, NEO_GRB + NEO_KHZ800);


const int arraySize = 4;

unsigned long lastUpdatedTimeMillis = 0;

long limit = 300000;

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

void setup() {
  Serial.begin(9600);
  leftFootHX.begin(leftFoot_LOADCELL_DOUT, leftFoot_LOADCELL_SCK);

  leftStrip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  leftStrip.show();            // Turn OFF all pixels ASAP
  leftStrip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)

}

bool leftPrev = 1;
int firstPixelHueBy256 = 0;

void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
      leftStrip.rainbow(firstPixelHueBy256*256*20);
      leftStrip.show(); // Update strip with new contents
      //delay(wait);  // Pause for a moment
      firstPixelHueBy256++;
  
}

void loop() {
  if (leftFootHX.is_ready()) {
        
    leftPrev = isStep(leftFootHX.read());
  
    if(leftPrev==1){
      Serial.println("on");
      Serial.println(firstPixelHueBy256);
      rainbow(5);
    } else {
      Serial.println("off");
      leftStrip.clear();
      leftStrip.show();
     // delay(5);
    }

  } else {
    Serial.println("HX711 not found.");
  }

  delay(100);
}
