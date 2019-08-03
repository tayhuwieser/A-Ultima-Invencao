#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int RC_RECEIVER_PIN1 = 8;
int RC_RECEIVER_PIN2 = 9;
int RC_RECEIVER_PIN5 = 12;
int RC_RECEIVER_PIN6 = 13;


#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  setupReceivers();
}

void loop() {
  int receiver1Value = readReceiver1();
  servo1Loop(receiver1Value);

  int receiver2Value = readReceiver2();
  servo2Loop(receiver2Value);

  int receiver5Value = readReceiver5();
  servo5Loop(receiver5Value);

  int receiver6Value = readReceiver6();
  servo6Loop(receiver6Value);

  int receiver7Value = readReceiver7();
  servo7Loop(receiver7Value);
  
  delay(10);
}

void setupReceivers() {
    pinMode(RC_RECEIVER_PIN1, INPUT);
    pinMode(RC_RECEIVER_PIN2, INPUT);
    pinMode(RC_RECEIVER_PIN5, INPUT);
    pinMode(RC_RECEIVER_PIN6, INPUT);
    Serial.begin(9600);
}


int readReceiver1() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN1, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue == 0)
    {
      return 60;
    }
    else
    {
      return map(analogValue, 1020, 1880, 40, 80 );
    } 
}
void servo1Loop(int angle1) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor1Convertido = pulse1Width(angle1);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(1, 0, valor1Convertido);
}

int pulse1Width(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 

int readReceiver2() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN2, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue == 0)
    {
      return 40;
    }
    else
    {
      return map(analogValue, 1060, 1880, 50, 30 );
    } 
}

void servo2Loop(int angle2) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor2Convertido = pulse2Width(angle2);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(2, 0, valor2Convertido);
}

int pulse2Width(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 

int readReceiver5() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN5, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue == 0)
    {
      return 130;
    }
    else
    {
      return map(analogValue, 1060, 1880, 120, 150 );
    } 
}
void servo5Loop(int angle5) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor5Convertido = pulse5Width(angle5);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(5, 0, valor5Convertido);
}

int pulse5Width(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

int readReceiver6() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN6, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue == 0)
    {
      return 130;
    }
    else
    {
      return map(analogValue, 1020, 1880, 135, 40 );
    } 
}
void servo6Loop(int angle6) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor6Convertido = pulse6Width(angle6);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(6, 0, valor6Convertido);
}

int pulse6Width(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 

int readReceiver7() {
    //lê o sinal do controle (de 1020 à 1880) e converte p/ um valor de 120 à 150
    int analogValue = pulseIn(RC_RECEIVER_PIN6, HIGH, 50000);
    Serial.println(analogValue);
    if (analogValue == 0)
    {
      return 40;
    }
    else
    {
      return map(analogValue, 1020, 1880, 40, 130 );
    } 
}
void servo7Loop(int angle7) {
  //recebe valor do readReceiver1 e manda pro pulseWidth
  int valor7Convertido = pulse7Width(angle7);
  // recebe valor convertido e aplica no servo
  pwm.setPWM(7, 0, valor7Convertido);
}

int pulse7Width(int angle) {
  // Recebe valor de x à y e transforma no valor pra uso no pwm
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
} 
