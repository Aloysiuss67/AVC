#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left so that the +ve direction is forward
//assume motor 2 is on the right so that the -ve direction is forward

/** 
code below allows use to test and adjust for travelling in a straight line 
*/

int count = 1;

int forward(){
  init();
  set_motor(1, 50); //make this faster if car is drifting LEFT
  set_motor(2, -50); //make this faster if drifting RIGHT
  sleep(8, 0); //runs for 8 seconds
  stop(0);
return 0;}

int main(){
  init();
    while (count = 1){ //will keep running unless we change the count
      forward();
      sleep(5,0); //gives 5 seconds to reset the car
  }
return 0;}
