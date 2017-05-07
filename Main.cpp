#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left so that the +ve direction is forward
//assume motor 2 is on the right so that the -ve direction is forward

char colourCutOff = 110; //this will need to be tested and changed, it is the point where a number is either black or white90

//the next 20 lines might not be needed 

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
  double scale = 0.2; // will need to change, so basic for now
  
  while (true){ //keeps running (for now)
  
    take_picture();
    int sum = 0;
    int i;
    
     
      for (i=0, i<=320, i++){
      char pix = get_pixel (i, 120, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (pix < colourCutOff){ //sets colour value to true black if closer to black in colour
          pix = 0;
        }
        if (pix > colourCutOff){ //sets colour to true white if closer to white
          pix = 1;
        }  
      sum = sum + (i-160)*(int)pix; // and i assume we'll have to cast some variables here
      }
   
   // two types of steering
   
   (int)sum = (double)sum * scale;
   
   set_motor(1, 80 + sum); // if sum is positive, line is on the right, therefore we must turn right
   set_motor(2, -80 - sum); // if sum is negative, line is on the left, therefore we must turn left
    
   // below is an alternative turning method 
   
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
