#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             60

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

void loop() {
    
pwm.setPWM(0, 0, pulseWidth(130));
delay(10);
pwm.setPWM(0, 0, 0);
delay(1500);
pwm.setPWM(0, 0, pulseWidth(60));
delay(10); 
pwm.setPWM(0, 0, 0);
delay(500);


}


int pulseWidth(int angle) {
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 
