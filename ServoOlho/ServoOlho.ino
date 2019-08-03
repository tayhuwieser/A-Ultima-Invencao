#include <Servo.h>

Servo eyeServo;
long servoPos;
long servoBPos;
long delayDur;
long delay2Dur;

void setup() {
  Serial.begin(115200);
  eyeServo.attach(6);
  randomSeed(analogRead(0));
  eyeServo.write(180);
  delay(1500);  
}

void loop() {
  servoPos = random(135 , 160);
  Serial.println(servoPos);
  
  servoBPos = random(160, 180);
  Serial.println(servoBPos);

  delayDur = random(100, 2000);
  Serial.println(delayDur);

  delay2Dur = random(500, 1500);
  Serial.println(delay2Dur);
  
  eyeServo.write(servoPos);
  delay(delayDur);
  eyeServo.write(servoBPos);
  delay(delay2Dur);

}
