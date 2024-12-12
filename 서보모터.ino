#include <Servo.h>

// 서보모터 핀 정의
#define SERVO1_PIN 3
#define SERVO2_PIN 5

// 서보모터 객체 생성
Servo servo1;
Servo servo2;

// 서보1 위치 설정값
const int servo1_lockPos = 15;     // 서보1 잠금 위치
const int servo1_unlockPos = 105;  // 서보1 잠금 해제 위치

// 서보2 위치 설정값
const int servo2_lockPos = 105;     // 서보2 잠금 위치
const int servo2_unlockPos = 15;  // 서보2 잠금 해제 위치

const int delayTime = 500; // 동작 간 대기 시간

void setup() {
  // 시리얼 통신 초기화
  Serial.begin(9600);
  
  // 서보모터 핀 연결
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // 초기 위치로 설정 (잠금 위치)
  servo1.write(servo1_lockPos);
  servo2.write(servo2_lockPos);
  
  Serial.println("서보모터 제어 시작");
  Serial.println("1: 잠금 해제");
  Serial.println("2: 잠금");
}

void loop() {
  // 시리얼 통신으로 명령 받기
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch(command) {
      case '1':
        moveServos(servo1_unlockPos, servo2_unlockPos);
        Serial.println("잠금 해제됨");
        break;
        
      case '2':
        moveServos(servo1_lockPos, servo2_lockPos);
        Serial.println("잠금 설정됨");
        break;
        
      default:
        Serial.println("잘못된 명령입니다. 1 또는 2를 입력하세요.");
        break;
    }
  }
}

// 두 서보모터를 각각 다른 각도로 제어하는 함수
void moveServos(int position1, int position2) {
  servo1.write(position1);
  servo2.write(position2);
  delay(delayTime);  // 서보모터가 이동할 시간 대기
}


