#define PRESSURE_PIN A0    // 압력센서 연결 핀
#define BUZZER_PIN 8      // 부저 연결 핀
#define THRESHOLD 30     // 압력 임계값 (0-1023 사이, 조정 가능)
#define CHECK_INTERVAL 1000 // 압력 체크 주기 (밀리초)

unsigned long lastCheckTime = 0;  // 마지막 체크 시간
bool isAlarmOn = false;          // 알람 상태

// 부저 소리 패턴 설정
const int beepDuration = 800;    // 비프음 지속 시간
const int beepInterval = 1000;   // 비프음 간격
unsigned long lastBeepTime = 0;  // 마지막 비프음 시간

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PRESSURE_PIN, INPUT);
  
  Serial.begin(9600);
  Serial.println("압력 감지 시스템이 시작되었습니다.");
  Serial.println("임계값: " + String(THRESHOLD));
}

void loop() {
  unsigned long currentTime = millis();
  
  // 설정된 주기마다 압력 체크
  if (currentTime - lastCheckTime >= CHECK_INTERVAL) {
    int pressureValue = analogRead(PRESSURE_PIN);
    Serial.println("현재 압력값: " + String(pressureValue));
    
    // 압력이 임계값보다 낮으면 알람 활성화
    if (pressureValue < THRESHOLD) {
      isAlarmOn = true;
      Serial.println("경고: 압력이 너무 낮습니다!");
    } else {
      isAlarmOn = false;
      noTone(BUZZER_PIN);  // 부저 끄기
      Serial.println("정상: 적정 압력이 감지됩니다.");
    }
    
    lastCheckTime = currentTime;
  }
  
  // 알람이 활성화된 상태에서 부저 제어
  if (isAlarmOn) {
    if (currentTime - lastBeepTime >= beepInterval) {
      // 비프음 재생
      tone(BUZZER_PIN, 1000);  // 1kHz 소리
      delay(beepDuration);
      noTone(BUZZER_PIN);
      
      lastBeepTime = currentTime;
    }
  }
}

// 부저 멜로디 재생 함수 (선택적 사용)
void playAlarmMelody() {
  // 경고음 멜로디
  int melody[] = {1000, 800, 1000, 800};  // 주파수
  int durations[] = {200, 200, 200, 200}; // 음 길이
  
  for (int i = 0; i < 4; i++) {
    tone(BUZZER_PIN, melody[i]);
    delay(durations[i]);
    noTone(BUZZER_PIN);
    delay(100);  // 음 사이 간격
  }
}
