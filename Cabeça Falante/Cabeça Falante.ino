#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int RC_RECEIVER_PIN1 = 14;

int servoCh1 = 0;

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  setupReceiver1();
}

void loop() {
  readReceiver1();
  servo1Loop();
  delay(10);
}

void setupReceiver1() {
    pinMode(RC_RECEIVER_PIN1, INPUT);
    Serial.begin(9600);
}

void readReceiver1() {
    int analogValue = pulseIn(RC_RECEIVER_PIN1, HIGH, 50000);
    servoCh1 = map(analogValue, 20, 160, 1020, 1080);
}

void servo1Loop() {
  pwm.setPWM(1, 0, servoCh1);
}

int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 20, 160, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 
