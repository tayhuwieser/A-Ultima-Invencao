

//the following are all ~PWM caspable ports
int rc_receiver_pin = 19;
int direction = 0; // 0 is centered, -1 is left, +1 is right
int velocity = 0;

void setup()
{
    setupReceiver();
}

void loop()
{
    readReceiver();
    printValues();
}

void setupReceiver() {
    pinMode(rc_receiver_pin, INPUT);
    Serial.begin(9600);
}

void readReceiver() {
    // analogValue é um valor que vem do receiver 1000 -> 2000
    int analogValue = pulseIn(rc_receiver_pin, HIGH, 50000);

    
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
}


void printValues() {
    Serial.print("Direction: ");
    Serial.println(direction == 1 ? "RIGHT" : (direction == -1 ? "LEFT" : "CENTER"));
    Serial.print("Velocity: ");
    Serial.println(velocity);
}
