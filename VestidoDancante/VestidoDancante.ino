#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = motorShield.getMotor(1);
Adafruit_DCMotor *motor3 = motorShield.getMotor(3);

int m1currentSpeed = 0;
int m1currentDirection = RELEASE;

int m3currentSpeed = 0;
int m3currentDirection = RELEASE;

//the following are all ~PWM caspable ports
int RC_RECEIVER_PIN1 = 14;
int RC_RECEIVER_PIN3 = 15;
int RC_RECEIVER_PIN4 = 16;

void setup()
{
    setupReceivers();
    setupMotorS();
}


void loop()
{
    
    readReceiver1();
    readReceiver3();
    bool isEnabled = readIsEnableSwitch();
    motor1Loop(isEnabled, m1currentDirection, m1currentSpeed);
    motor3Loop(isEnabled, m3currentDirection, m3currentSpeed);
    printValues();
    delay(10);
    
}

bool readIsEnableSwitch() {
  int analogValue = pulseIn(RC_RECEIVER_PIN4, HIGH, 50000);
  if (analogValue < 1500) {
    return false;
  } else {
    return true;
  }
}

void setupReceivers() {
    pinMode(RC_RECEIVER_PIN1, INPUT);
    pinMode(RC_RECEIVER_PIN3, INPUT);
    pinMode(RC_RECEIVER_PIN4, INPUT);
    Serial.begin(9600);
}

void setupMotorS() {
    motorShield.begin(1000);
}

void motor1Loop(bool isEnabled, int motor1direction, int motor1speed) {
  if (isEnabled == false) {
    motor1->run(0);
    motor1->setSpeed(0);
  }
  else
  {
    motor1->run(motor1direction);
    motor1->setSpeed(motor1speed);
}
}
void motor3Loop(bool isEnabled, int motor3direction, int motor3speed) {
  if (isEnabled == false) {
    motor3->run(0);
    motor3->setSpeed(0);
  }
  else
  {
    motor3->run(motor3direction);
    motor3->setSpeed(motor3speed);
  }
}

void readReceiver1() {
    // analogValue é um valor que vem do receiver 1000 -> 2000
    int analogValue = pulseIn(RC_RECEIVER_PIN1, HIGH, 50000);

    int motor1direction = 0; // 0 is centered, -1 is left, +1 is right
    int motor1velocity = 0;
    int MARGIN = 30;

    int NO_SIGNAL = 0;
    int MID = 1470;
    int RIGHT = 1880;
    int LEFT = 1020;

    // Mapping controller analog value (INPUT)
    if (analogValue == NO_SIGNAL) {
        motor1direction = 0;
        motor1velocity = 0;
    }
    else if (analogValue > (MID + MARGIN))
    {
        motor1direction = 1;
        motor1velocity = map(analogValue, (MID + MARGIN), RIGHT, 0, 255);
    }
    else if (analogValue < (MID - MARGIN))
    {
        motor1direction = -1;
        motor1velocity = map(analogValue, (MID - MARGIN), LEFT, 0, 255);
    }
    else
    {
        motor1direction = 0;
        motor1velocity = 0;
    };

    m1currentSpeed = motor1velocity;
    if (motor1direction == -1) {
        m1currentDirection = BACKWARD;
    }
    else if (motor1direction == 1) {
        m1currentDirection = FORWARD;
    }
    else {
        m1currentDirection = RELEASE;
    }
}


void readReceiver3() {
    // analogValue é um valor que vem do receiver 1000 -> 2000
    int analogValue = pulseIn(RC_RECEIVER_PIN3, HIGH, 50000);

    int motor3direction = 0; // 0 is centered, -1 is left, +1 is right
    int motor3velocity = 0;
    int MARGIN = 30;

    int NO_SIGNAL = 0;
    int MID = 1450;
    int RIGHT = 1880;
    int LEFT = 1020;

    // Mapping controller analog value (INPUT)
    if (analogValue == NO_SIGNAL) {
        motor3direction = 0;
        motor3velocity = 0;
    }
    else if (analogValue > (MID + MARGIN))
    {
        motor3direction = 1;
        motor3velocity = map(analogValue, (MID + MARGIN), RIGHT, 0, 255);
    }
    else if (analogValue < (MID - MARGIN))
    {
        motor3direction = -1;
        motor3velocity = map(analogValue, (MID - MARGIN), LEFT, 0, 255);
    }
    else
    {
        motor3direction = 0;
        motor3velocity = 0;
    };

    m3currentSpeed = motor3velocity;
    if (motor3direction == -1) {
        m3currentDirection = BACKWARD;
    }
    else if (motor3direction == 1) {
        m3currentDirection = FORWARD;
    }
    else {
        m3currentDirection = RELEASE;
    }
}

void printValues() {
    Serial.print("M1Direction: ");
    Serial.println(m1currentDirection == FORWARD ? "FORWARD" : (m1currentDirection == BACKWARD ? "BACKWARD" : "RELEASE"));
    Serial.print("M1Velocity: ");
    Serial.println(m1currentSpeed);
    Serial.print("M3Direction: ");
    Serial.println(m3currentDirection == FORWARD ? "FORWARD" : (m3currentDirection == BACKWARD ? "BACKWARD" : "RELEASE"));
    Serial.print("M3Velocity: ");
    Serial.println(m3currentSpeed);
}
