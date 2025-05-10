#include <Servo.h>
const int redGround = 7;
const int blueGround = 8;
const int trigPin = 2;
const int echoPin = 3;
const int redLED = 4;
const int blueLED = 5;
const int servoPin = 6;
const int buzzer = 12;
Servo barrier;
long duration;
int distance;
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(redGround,OUTPUT);
  pinMode(blueGround,OUTPUT);
  barrier.attach(servoPin);
  barrier.write(0);

  digitalWrite(redGround, LOW);
  digitalWrite(blueGround, LOW);

  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, LOW);
  digitalWrite(buzzer, LOW);
  Serial.println("System initialized. Red LED ON. Waiting for object...");
}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);
  if (distance > 0 && distance <= 15) {
    Serial.println("Object detected!");
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);

    for (int i = 0; i < 10; i++) {
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
    }

    barrier.write(90);
    delay(5000);
    barrier.write(0);

    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.println("Resetting to idle: Red ON, Blue OFF, Buzzer OFF");
  } else {

    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
    digitalWrite(buzzer, LOW);
    barrier.write(0);
    Serial.println("No object - Red LED ON, Buzzer OFF");
  }
  delay(500);
}
