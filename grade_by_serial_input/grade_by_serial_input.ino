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
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(2); 
}


void loop() {
  if (Serial.available() > 0)
  {
    int val= Serial.parseInt(); //Read an int value
    Serial.read(); //Read \n
    
    printGrade(val);
}
}

void rainbowSpecificPixels(int alphaX[], int numPixels) {
  static int firstPixelHue = 0;

  for (int i = 0; i < numPixels; i++) {
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(alphaX[i], strip.gamma32(strip.ColorHSV(pixelHue)));
  }

  strip.show();
  firstPixelHue += 256; // 무지개 색상을 천천히 이동
  if (firstPixelHue >= 65536) {
    firstPixelHue = 0; // 색상 범위를 넘어가면 0으로 재설정
  }
}

void printGrade(int val) {
  int* currentArray;
  int arraySize;

  // 알파벳 배열 선택
  switch(val) {
    case 1:
      currentArray = alphaA;
      arraySize = sizeof(alphaA) / sizeof(alphaA[0]);
      break;
    case 2:
      currentArray = alphaB;
      arraySize = sizeof(alphaB) / sizeof(alphaB[0]);
      break;
    case 3:
      currentArray = alphaC;
      arraySize = sizeof(alphaC) / sizeof(alphaC[0]);
      break;
    case 4:
      currentArray = alphaD;
      arraySize = sizeof(alphaD) / sizeof(alphaD[0]);
      break;
    default:
      // 잘못된 입력 처리
      return;
  }

  // 패턴 표시
  while(1) {
    rainbowSpecificPixels(currentArray, arraySize);
    delay(20);

    if(Serial.available()) {
      char input = Serial.read();
      if(input == 'q') {
        strip.clear();
        strip.show(); // LED 상태 업데이트
        break;
      }
    }
  }
}
