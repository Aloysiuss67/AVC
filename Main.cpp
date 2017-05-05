#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left so that the +ve direction is forward
//assume motor 2 is on the right so that the -ve direction is forward

int colourCutOff = 110; //this will need to be tested and changed, it is the point where a number is either black or white90

int forward (){
 init();
  
  set_motor(1, 50);
  set_motor(2, -50);
}

int steerRight (){ // will need to be adjusted to turn at the right rate
  init();
  
  set_motor(1, 50);
  set_motor(2, -60); 
}

int steerLeft (){ // will need to be adjusted to turn at the right rate
  init();
  
  set_motor(1, 60);
  set_motor(2, -50);
}

int main (){ //main program
  init();
  
  while (true){ //keeps running (for now)
  
    take_picture();
    int sum = -160;
    int i;
      for (i=0, i<320, i++){
      w = get_pixel (i, 120, 3);
        if (w < colourCutOff){ //sets colour value to true black if closer to black in colour
          w = 0
        }
        if (w > colourCutOff){ //sets colour to true white if closer to white
          w = 255
        }  
      sum = sum + i*w:
      } 
    
    if (sum > 0){  // if the white line to the right, it should turn right until in the middle
      steerRight(); 
    }
    if (sum < 0){ // if the white line to the left, it should turn left until in the middle
      steerLeft();
    }
    else {
     forward(); 
    }
  }
 
