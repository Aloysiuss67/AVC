#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left so that the +ve direction is forward
//assume motor 2 is on the right so that the -ve direction is forward

char colourCutOff = 110; //this will need to be tested and changed, it is the point where a number is either black or white9
int sum = 0;
int i;
double scale = 0.2;  // will need to change, so basic for now

int main (){ //main program
  init();
 
  while (true){ //keeps running (for now)
  
    take_picture();
    display_picture(1,0);
     
      for (i = 0, i<=320, i = i +20){
      char pix = get_pixel (i, 120, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (pix < colourCutOff){ //sets colour value to true black if closer to black in colour
          pix = 0;
        }
        if (pix > colourCutOff){ //sets colour to true white if closer to white
          pix = 1;
        }  
      sum = sum + ((i-160)*(int)pix)/160; // and i assume we'll have to cast some variables here
       
       printf("%d\n", sum);
      }
   
   // two types of steering
   
   sum = (double)sum * scale;
   
   set_motor(1, 80 + sum); // if sum is positive, line is on the right, therefore we must turn right
   set_motor(2, -80 - sum); // if sum is negative, line is on the left, therefore we must turn left
   
  return(0);}
}
