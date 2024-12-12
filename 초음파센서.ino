#define PIEZO_PIN 3

const int trigger = 6;
const int echo = 7;
float distance;
float dist_inches;


void setup() {
  Serial.begin(9600);
  // settings for ultrasonic sensor
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);


  pinMode(PIEZO_PIN, OUTPUT);
}


void loop() {
  // Trigger the sensor to start measurement
  // Set up trigger
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);


  // Start Measurement
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);


  // Acquire and convert to inches
  distance = pulseIn(echo, HIGH);
  distance = distance * 0.017;


  if (distance > 40) {
    tone(PIEZO_PIN, 1000);
    delay(200);
    noTone(PIEZO_PIN);
  }


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
