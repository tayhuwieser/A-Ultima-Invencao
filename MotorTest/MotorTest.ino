/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = motorShield.getMotor(1);

int currentSpeed = 0;
int currentDirection = RELEASE;
int isIncreasingSpeed = 1;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motorShield.begin(1000);
}

void loop() {
  changeSpeed();
  alternateDirection();
  motorLoop(currentDirection, currentSpeed);
  delay(10);
}

void motorLoop(int direction, int speed) {
  myMotor->run(direction);
  myMotor->setSpeed(speed);
}

// Obj: Set currentDirection variable
void alternateDirection() {
    // Read radio controls and apply to currentDirection;
    if (currentSpeed == 0) {
      if (currentDirection == RELEASE) {
        currentDirection = FORWARD;
      } else if (currentDirection == FORWARD) {
        currentDirection = BACKWARD;
      } else {
        currentDirection = RELEASE;
      }
    }
}

// Obj: Set currentSpeed variable
void changeSpeed() {
  // Read radio controls and apply to currentSpeed;
  if (isIncreasingSpeed) {
    // If speed is increasing
    if (currentSpeed < 255) {
      currentSpeed = currentSpeed + 1;
    } else {
      isIncreasingSpeed = 0;
    }
  } else {
    // If speed is decreasing
    if (currentSpeed > 0) {
      currentSpeed = currentSpeed - 1;
    } else {
      isIncreasingSpeed = 1;
    }
  }
}
