#include <Adafruit_NeoPixel.h>

// Define the pin for NeoPixel and the number of pixels
#define PIN            6
#define NUMPIXELS      256  // 16x16 matrix

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int alphaA[72]={145,142,113, 146,141,114,172,147,115,171,148,116,107,170,106,85,182,169,105,86,183,168,104,87,184,167,152,135,120,103,88,71,185,166,89,70,197,186,165,90,69,58,196,186,165,90,69,58,196,187,68,59,195,188,67,60,221,194,189,66,61,34,225,222,193,190,161,94,65,62,33,30};
int alphaB[73]={
  206,177,174,145,142,113,110,81,
  205,178,109,82,77,
  204,179,108,83,76,
  203,180,84,75,
  202,181,85,74,
  201,182,105,86,73,
  200,183,168,151,136,119,104,87,
  199,184,167,103,88,
  198,185,89,70,
  197,186,69,58,
  196,187,68,59,
  195,188,67,60,
  194,189,98,93,66,
  193,190,161,158,129,126,97,94
 };

 int alphaC[44]={
  145,142,113,110,
  173,109,82,77,
  204,179,83,76,
  203,180,75,
  213,202,
  214,201,
  215,200,
  216,199,
  217,198,
  218,197,186,
  196,187,
  195,188,163,
  162,157,
  129,126,97,93,66,67,60,59,58
 };

int alphaD[68]={
  238,177,174,145,142,113,110,
  210,205,178,114,109,82,
  204,179,83,76,
  203,180,84,75,
  202,181,74,53,
  201,182,73,54,
  200,183,72,55,
  199,184,71,56,
  198,185,70,57,
  197,186,69,58,
  196,187,91,68,
  195,188,92,67,
  194,189,162,125,98,93,
  225,222,193,190,161,158,129,126,97
};

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(2); 
}

void loop() {
  strip.clear();
  displayLetterA();
  delay(5000);   // Delay for a bit before changing patterns

  strip.clear();
  displayLetterB();
  delay(5000); 

  strip.clear();
  displayLetterC();
  delay(5000); 

  strip.clear();
  displayLetterD();
  delay(5000); 
  
  strip.clear();
  displayLetterC();
  delay(5);  // Adjust this for speed of color change
}

void displayLetterA() {
  for(int i=0;i<sizeof(alphaA)/sizeof(alphaA[0]);i++){
    strip.setPixelColor(alphaA[i],255,0,0);
    strip.show();  // Update the strip with new data
    
  }
}

void displayLetterB() {
  //sizeof slaphaB라고 하면 오류(led조각들이 띄엄띄엄 떠다님)
  for(int i=0;i<sizeof(alphaB)/sizeof(alphaB[0]);i++){
    strip.setPixelColor(alphaB[i],255,0,0); 
    strip.show();  // Update the strip with new data
  }

}

void displayLetterC() {
  for(int i=0;i<sizeof(alphaC)/sizeof(alphaC[0]);i++){
    strip.setPixelColor(alphaC[i],255,0,0);
    strip.show();  // Update the strip with new data
    
  }
}

void displayLetterD() {
  for(int i=0;i<sizeof(alphaD)/sizeof(alphaD[0]);i++){
    strip.setPixelColor(alphaD[i],255,0,0);
    strip.show();  // Update the strip with new data
  }
}
