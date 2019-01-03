#include "Robot.h"

//our L298N control pins
const int LeftMotorForward = 5;
const int LeftMotorBackward = 4;
const int RightMotorForward = 3;
const int RightMotorBackward = 2;

//sensor pins
#define trig_pin A1 //digital input 8
#define echo_pin A2 //digital input 9

#define maximum_distance 200
boolean movingForward = false;
boolean movingBackward = false;
int distance = 100;
// Max possible motor speed mapped to 8 bits (0-255 in integer).
// 255 is full power (5V), 0 is no power (0V)
const int max_speed = 255;
// calibration constant between (1-0) for the ratio of torque
// between left and right wheel.  0.5 is an even split
float calibration = 0.5;
// High speed setting. Currently makes motor speed 2.5V (ie 0.5*255)
float high_speed = 0.5;
float low_speed = 0.0;

int left_wheel_high = static_cast<unsigned int>(max_speed * high_speed * calibration);
int right_wheel_high = static_cast<unsigned int>(max_speed * high_speed * (1-calibration));

int left_wheel_low = static_cast<unsigned int>(max_speed * low_speed * calibration);
int right_wheel_low = static_cast<unsigned int>(max_speed * low_speed * (1-calibration));

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


int readPing(){
    delay(70);
    int cm = sonar.ping_cm();
    if (cm==0){
        cm=250;
    }
    return cm;
}

void initialize() {
    Serial.begin(9600);

    pinMode(RightMotorForward, OUTPUT);
    pinMode(LeftMotorForward, OUTPUT);
    pinMode(LeftMotorBackward, OUTPUT);
    pinMode(RightMotorBackward, OUTPUT);

    servo_motor.attach(11); //our servo pin

    servo_motor.write(90);
    delay(2000);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
    distance = readPing();
    delay(100);
}

void calibrate(float c) {
    calibration = c;

    left_wheel_high =
        static_cast<unsigned int>(max_speed * high_speed * calibration);
    right_wheel_high =
        static_cast<unsigned int>(max_speed * high_speed * (1-calibration));
    left_wheel_low =
        static_cast<unsigned int>(max_speed * low_speed * calibration);
    right_wheel_low =
        static_cast<unsigned int>(max_speed * low_speed * (1-calibration));
}

void moveForward() {
    movingBackward=false;

    if (!movingForward) {

        movingForward=true;

        analogWrite(LeftMotorForward, left_wheel_high);
        analogWrite(RightMotorForward, right_wheel_high);

        analogWrite(LeftMotorBackward, left_wheel_low);
        analogWrite(RightMotorBackward, right_wheel_low);
    }
}

void moveBackward() {
    movingForward=false;

    if (!movingBackward) {

        movingBackward = true;

        digitalWrite(LeftMotorBackward, left_wheel_high);
        digitalWrite(RightMotorBackward, right_wheel_high);

        digitalWrite(LeftMotorForward, left_wheel_low);
        digitalWrite(RightMotorForward, left_wheel_low);
    }
}

void moveStop() {
    digitalWrite(RightMotorForward, LOW);
    digitalWrite(LeftMotorForward, LOW);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW);

    movingForward = false;
    movingBackward = false;
}

void turnRight(int duration) {
    digitalWrite(LeftMotorBackward, left_wheel_high);
    digitalWrite(RightMotorForward, right_wheel_high);

    digitalWrite(LeftMotorForward, left_wheel_low);
    digitalWrite(RightMotorBackward, right_wheel_low);

    delay(duration);

    if (movingForward) {
        moveForward();
    } else if (movingBackward) {
        moveBackward();
    } else {
        moveStop();
    }
}

void turnLeft(int duration) {
    digitalWrite(LeftMotorForward, left_wheel_high);
    digitalWrite(RightMotorBackward, right_wheel_high);

    digitalWrite(LeftMotorBackward, left_wheel_low);
    digitalWrite(RightMotorForward, right_wheel_low);

    delay(duration);

    if (movingForward) {
        moveForward();
    } else if (movingBackward) {
        moveBackward();
    } else {
        moveStop();
    }
}

int getDistance() {
    readPing();
}

int lookAngle(int angle) {
    if (angle < 0) { angle = 0; }
    if (angle > 180) { angle = 180; }

    servo_motor.write(angle);
    delay(500);
    int distance = readPing();
    delay(100);
    servo_motor.write(90);
    return distance;
}

int lookRight() {
    lookAngle(10);
}

int lookLeft() {
    lookAngle(170);
}
