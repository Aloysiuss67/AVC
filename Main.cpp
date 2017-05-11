#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left so that the +ve direction is forward
//assume motor 2 is on the right so that the -ve direction is forward

char colourCutOff = 80; //this will need to be tested and changed, it is the point where a number is either black or white9
int sum = 0;
int i= 0;
double scale = 0.3;  // will need to change, so basic for now
int count=1;
char pix = 0;
char pixCheck = 0;

int main (){ //main program
  init();
 
  while (true){ //keeps running (for now)
  
    take_picture();
   // display_picture(1,0);
    
    // test code for going straight if line ahead occurs 
    
    
    for (i = 120; i <200; i = i + 10){
		pixCheck = get_pixel (20, i, 3);
		if (pixCheck < colourCutOff){    //sets colour value to true black if closer to black in colour
          pixCheck = 0;
        } 
		if( pixCheck >=  colourCutOff) {
			pixCheck = 1;
		}
		sum = sum + (int)pixCheck;
	}
	printf("%i \n", sum);
	if (sum > 2){
		set_motor(2, 40);
		set_motor(1, 40);
		sum=0;
	}
	
	
	
	if (sum <=  3){ //change sum to  sum <= 3
		sum = 0;
     
     // test only code for intial turn on the robot if no white line is ahead anymore 
     
		set_motor(2, 50); //right
		set_motor(1, -50); //left
        sleep1(0, 300);
     
     
     
     
      for (i = 0; i<320; i = i +20){
      pix = get_pixel (120, i, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (pix < colourCutOff){ //sets colour value to true black if closer to black in colour
          pix = 0;
        }
        if (pix > colourCutOff){ //sets colour to true white if closer to white
          pix = 1;
	  count++;
        }  
      sum = sum + ((i-160)*(int)pix)/count; // and i assume we'll have to cast some variables here

      // printf("%d pre\n", sum);
      }
      //printf("%i count\n", count);
      //printf("%i pix \n", ((i-160)*(int)pix));
     // printf("%i pix wo cast,\n", ((i-160)*pix));
      //printf("%i divide by count ,\n", ((i-160)*(int)pix)/count);
     
      //sleep1(1,0);
             count = 1;
             
  
   
   //printf("%d pre\n", sum);
   
  sum =(int)((double)sum * scale);
   if (sum > 45){
sum = 45;
}
	if (sum < -45){
		sum = -45;
	
}
	printf("%d\n", sum);
   set_motor(1, 37 + (sum)); // if sum is positive, line is on the right, therefore we must turn right
   set_motor(2, 37  - sum); // if sum is negative, line is on the left, therefore we must turn left   
   sleep1(0, 50);
  }
}
sum = 0;
return(0);}
