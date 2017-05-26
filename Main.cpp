
#include <stdio.h>
#include <time.h>
#include "E101.h"

//assume motor 1 is on the left
//assume motor 2 is on the right

char colourCutOff = 90; //this will need to be tested and changed, it is the point where a number is either black or white9
char RGBCutOff = 220;
int sum = 0;
int sumTwo = 0;
int i= 0;
double scale = 0.19;  // will need to change, so basic for now
int count=1;
char pix = 0;
char pixLeft = 0;
int countL= 1;
int countR = 1;
int countJ = 1;
char pixRight = 0;
int junction = 0;
int gateNo = 0;
int leftT = 3;
bool quad4 = false;
char bluePix = 0;
char greenPix = 0;
char redPix = 0;
int countRedPix = 0;

int driveForward(){
	set_motor(1, 38 + (sum)); // left motor, bracket to ensure correct polarity 
	set_motor(2, 48  - (sum)); // right motor, bracket to ensure correct polarity
	sleep1(0, 50);
	sumTwo = 0;
	sum = 0;
	count = 1;
	return(0);
}

int left(){ // reverses, while turning slightly left
	driveForward();
	sleep1(0, 8000);
	set_motor(1, -60); //left
	set_motor(2, 60); //right
	sleep1(0, 25000);
	count = 1;
	countR = 1;
	countL = 1;
	return(0);
}

int right(){
	driveForward();
	sleep1(0, 8000);
	set_motor(1, 68); //left
	set_motor(2, -68); //right
	sleep1(0, 40000);
	count = 1;
	countR = 1;
	countL = 1;
	return(0);
}
int gate (){
   //connects to server with the ip address 192.168.1.2
   char serv[24] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
   connect_to_server(serv, 1024);
   //sends a message to the connected server
   char message[24] = {'P','l','e','a','s','e'};
   send_to_server(message);
   //receives message from the connected server
   receive_from_server(message);
   send_to_server(message);
return 0;}


int main (){ //main program
  init();
 
  while (quad4==false){ //keeps running (for now)
  if (gateNo == 0) {
	  gateNo = 1;
	  gate ();
	  sleep1(1, 2000);
  } //else
    take_picture();
	count = 1; 
	
	  for (i = 100; i < 220; i = i +15){
		  bluePix = get_pixel (239, i, 2);
		  greenPix = get_pixel (239, i, 1);
		  redPix = get_pixel (239, i, 0);
		  if (redPix > RGBCutOff && bluePix < RGBCutOff && greenPix < RGBCutOff){
			  countRedPix++;
		  } 
	  }
	  if (countRedPix > 3){
		  set_motor(1, 0);
		  set_motor(2, 0);
		  return(0);
	  }
	
      for (i = 19; i<320; i = i +20){
      pix = get_pixel (239, i, 3); //gets the pixels on the middle row, we might want to change this depending on camera mounting
        if (pix < colourCutOff){ //sets colour value to true black if closer to black in colour
          pix = 0;
        // printf("0");
        }
        if (pix >=  colourCutOff){ //sets colour to true white if closer to white
          pix = 1;
		  count++;
	//	  printf("1");
        }  
      
      sum = sum + ((i-160)*(int)pix)/count; // and i assume we'll have to cast some variables here
     }
    //printf("\n");
	if (count > 15){
		junction = 1;
	
	}
	
   	if (junction == 0){
    sum =(int)((double)sum * scale);
		
   	if (sum > 45){
	sum = 45;
	}
	if (sum < -45){
	sum = -45;
	}
	
   	driveForward();
	}
	
	if (junction == 1){
		for (i = 0; i<80; i = i +3){
			pixLeft = get_pixel (i, 1, 3);
			if (pixLeft < colourCutOff){ //sets colour value to true black if closer to black in colour
            }
			if (pixLeft >=  colourCutOff){ //sets colour to true white if closer to white
			countL++;
			} 
		}
		for (i = 0; i<80; i = i +3){
			pixRight = get_pixel (i, 319, 3);
			if (pixRight < colourCutOff){ //sets colour value to true black if closer to black in colour
            }
			if (pixRight >=  colourCutOff){ //sets colour to true white if closer to white
			countR++;
			} 
		}
		
		if (countL > 3 && countR > 3){
			if (countJ == 1){
				sum = 0;
				driveForward();
				sleep1(3, 100000);
				countJ = 2;
			}
			if (countJ == 2){ 
			left();
			}
		}
		else if (countL > countR){
			if (leftT <= 2) {
			driveForward();
			sleep1(1, 90000);
			leftT++;
			}
			else {
			left();
			//printf("left");
			}
		}
		else if (countR > countL){
			right();
			//printf("right");
		}
		else{
	
		(sum =(int)((double)sum * scale));
		sum = sum;
		
		if (sum > 45){
		sum = 45;
		}
		if (sum < -45){
		sum = -45;
		}
		driveForward();
		//printf("passed");
		}
		
	}
}	

return(0);}
