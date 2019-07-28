#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int RC_RECEIVER_PIN1 = 14;

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
  int receiver1Value = readReceiver1();
  servo1Loop(receiver1Value);
  delay(10);
}

void setupReceiver1() {
    pinMode(RC_RECEIVER_PIN1, INPUT);
    Serial.begin(9600);
}

int readReceiver1() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN1, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue = 0)
    {
      pwm.setPWM(1, 0, 1500);
    }
    else
    {
      return map(analogValue, 1020, 1880, 120, 150 );
    } 
}

void servo1Loop(int value1) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor1Convertido = pulseWidth(value1);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(1, 0, valor1Convertido);
}

int pulseWidth(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 
