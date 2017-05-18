# include <stdio.h>
# include <time.h>
//# include "E101.h" 
//assuming 0 refers to front sensor
//assuming 1 refers to right sensor
int turn90(String Dir) {
  if(Dir=="right"){
  set_motor(1, 35); //callibrate this number
  set_motor(2, -35); //and this
  }else if(Dir=="left"){
    set_motor(1, -35); //callibrate this number
    set_motor(2, 35); //and this
  }
  
  if(fSensor>minWallDist && rSensor>minWallDist){
    turning = false; 
  }
}
int fCenter(){//goforward and center it - we know in front of us is clear
	int tolerance = 50;//range either side which the avc can be which is acceptable
	int errorVal = center - rSensor;//if neg turn right
	if(errorVal < -tolerance){//want to turn right
		//this senario is where we are to far to the left
		//we have negative error value
		//we want to increase left wheel speed -> by minusing a negative errorValue
		//and decrease right wheel speed -> by adding a negative errorValue
		left_motor(1, 35 -(errorVal));//we known this wont work - just showing logic
      		right_motor(2, 35 + (errorVal));	
	}else if(errorVal>tolerance){
		left_motor(1, 35 -(errorVal));//we known this wont work - just showing logic
      		right_motor(2, 35 + (errorVal));
	}else{
		left_motor(1, 35);//we known this wont work - just showing logic
      		right_motor(2, 35);
		//perhaps could try something like this -> where the error value matters less if within tolerance
		left_motor(1, 35 -(errorVal*0.3));//we known this wont work - just showing logic
      		right_motor(2, 35 + (errorVal*0.3));
		
	}
	
}
int main(){
  //assume quad4 code has been called and sensors are within walls
  init();
  //declare variables
  int fSensor;
  int rSensor;
  //front stuff
  int minVal = 20;//minimum value the sensor will read_analog
  int maxVal = 600;//maximum value the sensor will read_analog
  int sensorToSpeed = 255/200;//note divisor can be chaged to maxVal
  boolean turning = false;
  
  
  
  int minWallDist = 20;//minimum distance avc can be to wall - find through trial and error
  int centerVal = 10;//the value that means robot is in center of walls
  
  //right sensor
  int rPrev = centerVal;
  //running
  while(true){
    //camera stuff
    //if camera sees red - call a function which runs until were through the gate
    fSensor = read_analog(0);//front sensor
    rSensor = read_analog(1);//right sensor
    
    if(fSensor < minVal){
      fSensor = minVal;      
    }else if(fSensor > maxVal){
      fSensor = maxVal;      
    }
    
    if(fSensor>minWallDist + 30){//still need to check if centered
      //go forward
      //could also include further away faster it can go - relates to how far away it is
      //(fSensor-minWallDist)*sensorToSpeed

      fCenter()
    }else if(fSensor>minWallDist){//accounting for the time it will take to stop
      set_motor(1, 10);
      set_motor(2, 10); 
    }else{
      set_motor(1, 0);
      set_motor(2, 0);
      //decide where to turn
    }
    
    //this if statement only gets called if theres a right corner
    if(rSensor-rPrev > 500){//the number needs to be callibrated - it shows a rapid change in right sensor values
      //turn 90right - calibrated
      //boolean turning variable 
      turning = true;
      while(turning){
	turn90("right");
      }
      //were now done turning
      //start going forward
      set_motor(1, 30); //assuming this is left
      set_motor(2, 30); //assuming this is right
      // turn 90 then go straight until right sensor hits the wall
    }
    
    if(rSensor < minWallDist && fSensor < minWallDist){//check if we need to turn left
      turning = true;
      while(turning){
	turn90("left");
      }
      
    }
    
    rPrev = rSensor;//remember value for the next time
  }
  
}

/*Next time
 * we need to find out what the center value is - i.e see what the sensor value is when we place the robot in the middle
 * we need to write a function to center the robot
 * we need to write code for recognising the red tape before the gate
 * Find out values of the front sensor when were are as close as possible to the wall - to know this we will need to test the robots turning ability.
 * calibrate 90deg turn
 **/
