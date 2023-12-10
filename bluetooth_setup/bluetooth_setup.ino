#include <SoftwareSerial.h>

const int nPin_BTTx = 2; //전송

const int nPin_BTRx = 3; //수신

SoftwareSerial BTSerial(nPin_BTTx, nPin_BTRx); // RX, TX

void setup() {

  Serial.begin(9600);

  BTSerial.begin(9600);

  Serial.println("START"); 

}

//AT쳐도 시리얼 모니터에 OK안나오면 시리얼 모니터 설정 "No Line Ending"으로 바꾸기
//AT+NAME보드이름 : 블루투스 모듈이름 변경 ex)AT+NAMEmybt;
//AT+PIN비밀번호 : 블루투스 비밀번호 변경 ex) AT+PIN0000

void loop() {

  if (BTSerial.available())

        Serial.write(BTSerial.read());

  if (Serial.available())

        BTSerial.write(Serial.read());

}