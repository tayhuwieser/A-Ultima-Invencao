#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int RC_RECEIVER_PIN1 = 8;
int RC_RECEIVER_PIN2 = 9;
int RC_RECEIVER_PIN3 = 10;
int RC_RECEIVER_PIN4 = 11;
int RC_RECEIVER_PIN5 = 12;
int RC_RECEIVER_PIN6 = 13;
int RC_RECEIVER_PIN8 = 7;

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  setupReceiver();
}

void setupReceiver() {
  pinMode(RC_RECEIVER_PIN1, INPUT);
  pinMode(RC_RECEIVER_PIN2, INPUT);
  pinMode(RC_RECEIVER_PIN3, INPUT);
  pinMode(RC_RECEIVER_PIN4, INPUT);
  pinMode(RC_RECEIVER_PIN5, INPUT);
  pinMode(RC_RECEIVER_PIN6, INPUT);
  pinMode(RC_RECEIVER_PIN8, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool isEnabled = readIsEnableSwitch();
  loopMotor1(isEnabled);
  loopMotor2(isEnabled);
  loopMotor3(isEnabled);
  loopMotor4(isEnabled);
  loopMotor5(isEnabled);
  loopMotor6(isEnabled);
  loopMotor7(isEnabled);
  delay(10);
}

bool readIsEnableSwitch() {
  int analogValue = pulseIn(RC_RECEIVER_PIN8, HIGH, 50000);
  if (analogValue > 1600) {
    return false;
  } else {
    return true;
  }
}

void loopMotor1(bool isEnabled) {
  int defaultAngle = 60;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN1);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 40, 90, defaultAngle);
  setServoAngle(1, angleValue);
}

void loopMotor2(bool isEnabled) {
  int defaultAngle = 30;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN2);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 35, 25, defaultAngle);
  setServoAngle(2, angleValue);
}

void loopMotor3(bool isEnabled) {
  int defaultAngle = 115;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN3);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 95, 135, defaultAngle);
  setServoAngle(3, angleValue);
}

void loopMotor4(bool isEnabled) {
  int defaultAngle = 50;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN4);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 30, 70, defaultAngle);
  setServoAngle(4, angleValue);
}

void loopMotor5(bool isEnabled) {
  int defaultAngle = 110;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN5);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 110, 160, defaultAngle);
  setServoAngle(5, angleValue);
}

void loopMotor6(bool isEnabled) {
  int defaultAngle = 30;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN6);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 90, 30, defaultAngle);
  setServoAngle(6, angleValue);
}

void loopMotor7(bool isEnabled) {
  int defaultAngle = 100;
  int receiverValue = readReceiverValue(RC_RECEIVER_PIN6);
  int angleValue = isEnabled == false ? defaultAngle : convertReceiverValueToAngle(receiverValue, 30, 100, defaultAngle);
  setServoAngle(7, angleValue);
}

int readReceiverValue(int receiverPinNumber) {
  // Lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 0 à 1000.
  // SE FOR INVALIDO (DESLIGADO) RETORNA -1.

  int analogValue = pulseIn(receiverPinNumber, HIGH, 50000);

  if (analogValue == 0) {
    return -1;
  } else {
    return map(analogValue, 1020, 1880, 0, 1000);
  }
}

void setServoAngle(int servoNumber, int angleValue) {
  // Recebe o numero do Servo e o angulo que ele deve ir
  int valorConvertido = convertAngleToPulseWidth(angleValue);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(servoNumber, 0, valorConvertido);
}

int convertReceiverValueToAngle(int receiverValue, int minValue, int maxValue, int defaultValue) {
  int angleValue = defaultValue;
  if (receiverValue != -1) {
    angleValue = map(receiverValue, 0, 1000, minValue, maxValue);
  }
    return angleValue;
}

int convertAngleToPulseWidth(int angle) {
  // Recebe valor de 0 ate 180 e transforma no valor pra uso no pwm
  int pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}
