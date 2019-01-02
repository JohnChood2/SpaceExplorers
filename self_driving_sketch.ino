#include <Robot.h>

void setup(){
  initialize();
  calibrate(0.6);
}

void loop(){
  moveForward();
  
  int distance = lookForward();
  
  if (distance <= 10){
    moveStop();
    delay(300);
    int distanceRight = lookRight();
    delay(300);
    int distanceLeft = lookLeft();
    delay(300);
    
    if (distanceRight > 20) {
      turnRight(750);
      moveStop();
    }
    else{
      turnLeft(750);
      moveStop();
    }
  }
}
