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
return(0);}

int steerRight (){ // will need to be adjusted to turn at the right rate
  init();
  
  set_motor(1, 50);
  set_motor(2, -60); 
return(0);}

int steerLeft (){ // will need to be adjusted to turn at the right rate
  init();
  
  set_motor(1, 60);
  set_motor(2, -50);
return(0);}

int main (){ //main program
  init();
  
  while (true){ //keeps running (for now)
  
    take_picture();
    int sum = 0;
    int iLeft;
    int iRight;
   
      for (iLeft=0, iLeft<=160, iLeft++){
      l = get_pixel (iLeft, 120, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (l < colourCutOff){ //sets colour value to true black if closer to black in colour
          l = 0
        }
        if (l > colourCutOff){ //sets colour to true white if closer to white
          l = 255
        }  
      sum = sum + i*w;
      }
   
      for (iRight=161, iRight<320, iRight++){
       r = get_pixel (iRight, 120, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (r < colourCutOff){ //sets colour value to true black if closer to black in colour
          r = 0
        }
        if (r > colourCutOff){ //sets colour to true white if closer to white
          r = 255
        }  
      sum = sum - i*r;
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
  return(0);}
