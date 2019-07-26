#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

void moveToLeft(int ids[], int count) {
    for (int servoIndex = 0; servoIndex < count; servoIndex += 1) {
        int servoId = ids[servoIndex];
        pwm.setPWM(servoId, 0, pulseWidth(30));
    }
}

void moveToRight(int ids[], int count) {
    for (int servoIndex = 0; servoIndex < count; servoIndex += 1) {
        int servoId = ids[servoIndex];
        pwm.setPWM(servoId, 0, pulseWidth(160));
    }
}

void moveToCenter(int ids[], int count) {
    for (int servoIndex = 0; servoIndex < count; servoIndex += 1) {
        int servoId = ids[servoIndex];
        pwm.setPWM(servoId, 0, pulseWidth(105));
    }
}

void endMovement(int ids[], int count) {
    for (int servoIndex = 0; servoIndex < count; servoIndex += 1) {
        int servoId = ids[servoIndex];
        pwm.setPWM(servoId, 0, 0);
    }
}

void loop() {
    int servoIds[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    moveToRight(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
    delay(3000);
    moveToCenter(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
    delay(1500);
    moveToLeft(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
    delay(3000);
    moveToCenter(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
    delay(500);
    endMovement(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
    delay(1000);


    
    for (int servoIndex = 0; servoIndex < (sizeof(servoIds) / sizeof(servoIds[0])); servoIndex += 1) {
        int servoId = servoIds[servoIndex];
int arr[] = {servoId};
moveToCenter(arr, 1);
delay(500);
moveToLeft(arr, 1);
delay(1000);
moveToRight(arr, 1);
delay(1000);
moveToCenter(arr, 1);
delay(500);
endMovement(servoIds, (sizeof(servoIds) / sizeof(servoIds[0])));
delay(500);
    }

pwm.setPWM(12, 0, pulseWidth(30));
delay(500);
pwm.setPWM(12, 0, pulseWidth(140));
delay(3000);
pwm.setPWM(12, 0, pulseWidth(30));
delay(500); 
pwm.setPWM(12, 0, 0);
delay(500);


}


int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 20, 160, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 
