#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield motorShield = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = motorShield.getMotor(1);

int currentSpeed = 0;
int currentDirection = RELEASE;

//the following are all ~PWM caspable ports
int rc_receiver_pin = 19;

void setup()
{
    setupReceiver();
    setupMotorS();
}


void loop()
{
    readReceiver();
//    motorLoop(currentDirection, currentSpeed);
    printValues();
    delay(10); 
}

void setupReceiver() {
    pinMode(rc_receiver_pin, INPUT);
    Serial.begin(9600);
}
void setupMotorS() {
    motorShield.begin(1000);
}

void motorLoop(int direction, int speed) {
  myMotor->run(direction);
  myMotor->setSpeed(speed);
}

void readReceiver() {
    // analogValue é um valor que vem do receiver 1000 -> 2000
    int analogValue = pulseIn(rc_receiver_pin, HIGH, 50000);

    int direction = 0; // 0 is centered, -1 is left, +1 is right
    int velocity = 0;
    int MARGIN = 30;

    int NO_SIGNAL = 0;
    int MID = 1470;
    int RIGHT = 1880;
    int LEFT = 1060;

    // Mapping controller analog value (INPUT)
    if (analogValue == NO_SIGNAL) {
        direction = 0;
        velocity = 0;
    }
    else if (analogValue > (MID + MARGIN))
    {
        direction = 1;
        velocity = map(analogValue, (MID + MARGIN), RIGHT, 0, 255);
    }
    else if (analogValue < (MID - MARGIN))
    {
        direction = -1;
        velocity = map(analogValue, (MID - MARGIN), LEFT, 0, 255);
    }
    else
    {
        direction = 0;
        velocity = 0;
    };
    currentSpeed = velocity;
    if (direction == 0) {
        currentDirection = RELEASE;
    }
    else if (direction == -1) {
        currentDirection = BACKWARD;
    }
    else if (direction == 1) {
        currentDirection = FORWARD;
    }
}


void printValues() {
    Serial.print("Direction: ");
    Serial.println(currentDirection == FORWARD ? "FORWARD" : (currentDirection == BACKWARD ? "BACKWARD" : "RELEASE"));
    Serial.print("Velocity: ");
    Serial.println(currentSpeed);
}
