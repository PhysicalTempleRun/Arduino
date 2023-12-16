#include <Wire.h>
#include <SoftwareSerial.h>

const int MPU_ADDR = 0x68; // I2C통신을 위한 MPU6050의 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; // 가속도(Acceleration)와 자이로(Gyro)
double angleAcX, angleAcY, angleAcZ;
const double RADIAN_TO_DEGREE = 180 / 3.14159;

// // HC-06 블루투스 모듈을 위한 핀 설정
// const int BT_RX = 2; // HC-06 RX 핀
// const int BT_TX = 3; // HC-06 TX 핀
// SoftwareSerial bluetooth(BT_RX, BT_TX); // RX, TX

long i=0;

void setup() {
  
  initSensor();
  Serial.begin(115200); // 시리얼 통신 속도 설정 
  //bluetooth.begin(9600); // 블루투스 통신 속도 설정 
  Serial.println("arduino setup called");
}

void loop() {
  //Serial.print("\t");
  //Serial.println(i);

  getData();

  angleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * RADIAN_TO_DEGREE;
  angleAcY = atan(-AcX / sqrt(pow(AcY, 2) + pow(AcZ, 2))) * RADIAN_TO_DEGREE;

  Serial.print("angleAcX : ");
  Serial.println(angleAcX);
  checkAndPrintAngle();
  delay(100);
  i++;
}

void initSensor() {
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); 
  Wire.write(0x6B);    
  Wire.write(0);
  Wire.endTransmission(true);
}

void getData() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);   
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 14, true);  
  AcX = Wire.read() << 8 | Wire.read(); 
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();
}

void checkAndPrintAngle() {
  if (angleAcX >= 50) {

    //0.1초 있다가 다시 값 확인해봐서 그때도 기울이고 있는지 확인
    //delay(100);
    getData();
    double recheckAngleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * RADIAN_TO_DEGREE;
    
    if (recheckAngleAcX >= 50) {
      //mac과 블루투스 통신시
      Serial.println("left");
      //bluetooth.println("left");

      //윈도우와 블루투스 통신시
      //bluetooth.println("left");
      //안되면 아래걸로 해보기
         //bluetooth.write("left"); // 숫자를 문자로 변환하여 연결된 곳에 전송
       //bluetooth.write('\r'); // 캐리지 리턴 전송
       //bluetooth.write('\n'); // 라인 피드 전송
         
      delay(1000); //기울였다가 다시 제자리로 돌아가는 동안에 읽히는 값은 무시하기위함
    }
  } else if (angleAcX <= -65) {

    //0.1초 있다가 다시 값 확인해봐서 그때도 기울이고 있는지 확인
    delay(50);
    getData();
    double recheckAngleAcX = atan(AcY / sqrt(pow(AcX, 2) + pow(AcZ, 2))) * RADIAN_TO_DEGREE;

    if (angleAcX <= -65) {
      //mac과 블루투스 통신시
      Serial.println("right");
      //bluetooth.println("right");

      //윈도우와 블루투스 통신시
      //bluetooth.println("right");
      //안되면 아래걸로 해보기
         //bluetooth.write("right"); // 숫자를 문자로 변환하여 연결된 곳에 전송
       //bluetooth.write('\r'); // 캐리지 리턴 전송
       //bluetooth.write('\n'); // 라인 피드 전송
      delay(1000); //기울였다가 다시 제자리로 돌아가는 동안에 읽히는 값은 무시하기위함
    }
  }
}
