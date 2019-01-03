#ifndef Robot_h
#define Robot_h

#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>

/////////////////////
// Setup functions //
/////////////////////

// `initialize()` starts the robot. It should be called in `setup().`
void initialize();

// `calibrate(balance)` can be used to change the amount of power going to both
// motors, which may help if the robot is drifting to the left or the right. If
// `balance` is higher than 0.5, the left wheel will get more power, which could
// correct a robot that is drifting left. If `balance` is less than 0.5, more
// power will be put into the right wheel.
//
// You will need to perform experiments to find the right value of `balance` for
// your robot.
void calibrate(float balance);

////////////////////////
// Movement functions //
////////////////////////


// `moveForward()` makes the robot move forward. It will continue moving forward
// until `moveBackward()` or `moveStop()`
void moveForward();

// `moveForward()` makes the robot move backward. It will continue moving
// backward until `moveForward()` or `moveStop()` is called.
void moveBackward();

// `moveStop()` makes the robot stop. It will remain stopped until
// `moveForward()` or `moveBackward()` is called.
void moveStop();

// `turnLeft(duration)` makes the robot turn left for `duration` milliseconds
// (so, e.g., turnLeft(1000) turns left for 1 second). You will need to do
// experiments to figure out what `duration` is needed to make your robot turn
// at different angles.
void turnLeft(int duration);

// `turnRight(duration)` makes the robot turn left for `duration` milliseconds
// (so, e.g., turnLeft(1000) turns left for 1 second). You will need to do
// experiments to figure out what `duration` is needed to make your robot turn
// at different angles.
void turnRight(int duration);

// `getDistance()` returns the distance to the nearest object in centimeters. You will need to
// do experiments to figure out how accurate your robot's sensor is.
int getDistance();

// `lookForward()` makes the ultrasonic sensor on the robot look to its right
// and returns the distance to the nearest wall in centimeters. You will need to
// do experiments to figure out how accurate your robot's sensor is.
int lookRight();

// `lookForward()` makes the ultrasonic sensor on the robot look to its left and
// returns the distance to the nearest wall in centimeters. You will need to
// do experiments to figure out how accurate your robot's sensor is.
int lookLeft();

// `lookAngle(angle)` makes the ultrasonic sensor on your robot look in any
// direction and returns the distance to the nearest wall in centimeters. The
// robot will turn its sensor to `angle` degrees from the right, meaning that
// `lookAngle(0)` will look to the right, `lookAngle(180)` will look to the
// left and `lookAngle(90)` will look forward. You will need to do experiments
// to figure out how accurate your robot's sensor is.
int lookAngle(int angle);

#endif
