#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <math.h>

//our L298N control pins
const int LeftMotorForward = 5;
const int LeftMotorBackward = 4;
const int RightMotorForward = 3;
const int RightMotorBackward = 2;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;
const int max_speed = 255; //Max possible motor speed mapped to 8 bits (0-255 in integer). 255 is full power (5V), 0 is no power (0V)
float calibration = 0.5; // calibration constant between (1-0) for the ratio of torque between left and right wheel.  0.5 is an even split
float high_speed = 0.50; // High speed setting. Currently makes motor speed 2.5V (ie 0.5*255)
float low_speed = 0.0; 

int left_wheel_high = static_cast<unsigned int>(max_speed * high_speed * calibration);
int right_wheel_high = static_cast<unsigned int>(max_speed * high_speed * (1-calibration));

int left_wheel_low = static_cast<unsigned int>(max_speed * low_speed * calibration);
int right_wheel_low = static_cast<unsigned int>(max_speed * low_speed * (1-calibration));

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

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

void loop(){

  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (distance <= distanceLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  // analogWrite(LeftMotorForward,left_wheel_low);
  // analogWrite(RightMotorForward,right_wheel_low); 

  // analogWrite(LeftMotorBackward,left_wheel_low);
  // analogWrite(RightMotorBackward,right_wheel_low);
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

  if(!goesForward){

    goesForward=true;
    
    analogWrite(LeftMotorForward,left_wheel_high);
    analogWrite(RightMotorForward,right_wheel_high);

    analogWrite(LeftMotorBackward,left_wheel_low);
    analogWrite(RightMotorBackward,right_wheel_low);
    
    //digitalWrite(LeftMotorForward, HIGH);
    //digitalWrite(RightMotorForward, HIGH);
  
    //digitalWrite(LeftMotorBackward, LOW);
    //digitalWrite(RightMotorBackward, LOW); 
  }
}

void moveBackward(){

  goesForward=false;

  //analogWrite(LeftMotorBackward,left_wheel_high);
  //analogWrite(RightMotorBackward,right_wheel_high);

  //analogWrite(LeftMotorForward,left_wheel_low);
  //analogWrite(RightMotorForward,right_wheel_low);
  
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}

void turnRight(){

  digitalWrite(LeftMotorForward, left_wheel_high);
  digitalWrite(RightMotorBackward, right_wheel_high);
  
  digitalWrite(LeftMotorBackward, left_wheel_low);
  digitalWrite(RightMotorForward, right_wheel_low);
  
  delay(500);
  
  digitalWrite(LeftMotorForward, left_wheel_high);
  digitalWrite(RightMotorForward, right_wheel_high);
  
  digitalWrite(LeftMotorBackward, left_wheel_low);
  digitalWrite(RightMotorBackward, right_wheel_low);
 
  
  
}

void turnLeft(){

  digitalWrite(LeftMotorBackward, left_wheel_high);
  digitalWrite(RightMotorForward, right_wheel_high);
  
  digitalWrite(LeftMotorForward, left_wheel_low);
  digitalWrite(RightMotorBackward, right_wheel_low);

  delay(500);
  
  digitalWrite(LeftMotorForward, left_wheel_high);
  digitalWrite(RightMotorForward, right_wheel_high);
  
  digitalWrite(LeftMotorBackward, left_wheel_low);
  digitalWrite(RightMotorBackward, right_wheel_low);
}
