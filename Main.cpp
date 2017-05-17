#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left
//assume motor 2 is on the right

char colourCutOff = 80; //this will need to be tested and changed, it is the point where a number is either black or white9
int sum = 0;
int sumTwo = 0;
int i= 0;
double scale = 0.3;  // will need to change, so basic for now
int count=1;
char pix = 0;
char pixCheck = 0;
int growingError = 0;

int driveForward(){
	set_motor(1, 35 + (sum)); // left motor, bracket to ensure correct polarity 
	set_motor(2, 35 - (sum)); // right motor, bracket to ensure correct polarity
	sleep1(0, 100);
	sumTwo = 0;
	sum = 0;
	count = 1;
	growingError = 0;
	return(0);
}

int find(){ // reverses, while turning slightly left
	set_motor(1, -70); //left
	set_motor(2, -40); //right
	sleep1(0, 300000);
	//growingError = growingError + 20000;
	count = 1;
	sumTwo= 0;
	sum = 0;
	return(0);
}

int main (){ //main program
  init();
 
  while (true){ //keeps running (for now)
  
    take_picture();
   // display_picture(1,0);
   
    for (i = 100; i <220; i = i + 4){ // test code for going straight if line ahead occurs
		pixCheck = get_pixel (1, i, 3);
		if (pixCheck < colourCutOff){    //sets colour value to true black if closer to black in colour
          	  pixCheck = 0;
        	} 
		if( pixCheck >=  colourCutOff) {
		  pixCheck = 1;
		}
		sumTwo = sumTwo + (int)pixCheck;
    }
	  printf("%i \n", sumTwo);
		
	  if (sumTwo > 2){ //if white line exists infront robot will continue to drive straight
	    printf("forward");
		driveForward();
	  }
	
	if (sumTwo <=  2){ // figures out which way to adjust
     // test only code for intial turn on the robot if no white line is ahead anymore 
	
     
      for (i = 0; i<320; i = i +20){
      pix = get_pixel (239, i, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
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
	//printf("%i count \n", count);
       if (count > 15){ // if lots of white pixel exist, we are at a junction
	      printf("junction"); 
	       find();
       }
		
	if (count < 3){  // if very few pixels exist, we have lost the line
		printf("lost");
		find();
	}
		
	if (count <= 15 && count >= 3){ // adjust to the line
   	//printf("%d pre\n", sum);
   	
    	sum =(int)((double)sum * scale);
		
   	if (sum > 45){
	sum = 0;
	set_motor(1, 45);
	set_motor(2, -45);
	sleep1(0, 10000);
	printf("turned right");
	return(0);
	}
	if (sum < -45){
	sum = 0;
	set_motor(1, -45);
 	set_motor(2, 45);
	sleep1(0, 10000);
	printf("turned left");
	return(0);	
	}
	//printf("%d\n", sum);
   	driveForward();
	printf("adjusted");
	}
  }
}
//sum = 0; i think this isnt needed now
return(0);}
