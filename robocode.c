#include <NewPing.h>

#define sonarNum  2
// Ultrasonic Sensor Control 

const int sensorTop_Trig = 4; // insert pin trig pin on Top ultrasonic sensor is connected to 
const int sensorTop_Echo = 3 ;// insert pin that echo pin on Bottom ultrasonic sensor connected to 
const int sensorMax = 150; // max distance for ultrasonic sensor
const int sensorBottom_Trig = 13;
const int sensorBottom_Echo = 12;

double distanceTop;
double distanceBottom;


NewPing sonar[sonarNum] = {                             //sets the amount of sensors to two 
  NewPing(sensorTop_Trig, sensorTop_Echo, sensorMax),     //sets up the Top sensor
  NewPing(sensorBottom_Trig, sensorBottom_Echo, sensorMax), //sets up the bottom sensor 
};


// Motor Control 
const int motorOne_InputTwo = 5; 
const int motorOne_InputOne = 6;
const int motorOne_Enable = 9;
const int motorTwo_Enable = 10;
const int motorTwo_InputOne = 7;
const int motorTwo_InputTwo = 8;

void setup() {
  Serial.begin(9600);  
  for(int i= 5; i<=10; i++){
    pinMode(i, OUTPUT);
  }
  
digitalWrite(motorOne_Enable, HIGH);
digitalWrite(motorTwo_Enable, HIGH);

}
  

void loop() {
 distanceTop = sonar[0].ping_cm();       //reads the value from the top sensor
 distanceBottom = sonar[1].ping_cm();   //reads the value from the bottom sensor
 int x = distanceTop-distanceBottom;
 Serial.println(x);

 panMotion();                            // initiates the panning motion

 Serial.print("TOP ");
 Serial.println(distanceTop);
 Serial.print("BOTTOM ");
 Serial.println(distanceBottom);
if(x>=2 && x<=6 && distanceTop != 0){
  while ((distanceBottom<80 || distanceBottom>90) && distanceTop != 0){
    Serial.println("While-in");
    distanceTop = sonar[0].ping_cm();       //reads the value from the top sensor
    distanceBottom = sonar[1].ping_cm();   //reads the value from the bottom sensor
    Serial.println("========================WHILE VARS===================");
    Serial.print("TOP ");
    Serial.println(distanceTop);
    Serial.print("BOTTOM ");
    delay(50);
    Serial.println(distanceBottom);
    if(distanceBottom<25) forward();
    else if(distanceBottom>35) reverse();
  }
  stopBot();
/*
  delay(500);
  reverse();
  delay(990);
  stopBot();
  */
  delay(3000);
  shootyShoot();
} 

//if(distanceBottom<205 && distanceBottom>195) shootyShoot();

/*
 while ( 2 < x < 3  ) {   
   stopBot();                         //stops the bot when condition 
   
   if(distanceBottom > 205) {         //if the bot is far away, it moves forward
   forward();
 }
   else {                              //if the bot is close, it moves backward
     while(distanceBottom < 195) { 
       reverse();
      }
}
   shootyShoot();
}
*/
}

void forward() {   // defines a function that makes both motors turn forward
   digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, HIGH);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, HIGH);
  delay(10); 
}

void reverse() { // defines a function that makes both wheels go backwards
  digitalWrite(motorOne_InputOne, HIGH);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, HIGH);
  digitalWrite(motorTwo_InputTwo, LOW);
  delay(10);
}

void panMotion() {                           //defines function that makes the robot turn in a cirlce
  digitalWrite(motorOne_InputOne, HIGH);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, HIGH);
  delay(10);
}

void stopBot() {                            //defines function that stops all the motors of the bot
   digitalWrite(motorOne_InputOne, LOW);
  digitalWrite(motorOne_InputTwo, LOW);
  digitalWrite(motorTwo_InputOne, LOW);
  digitalWrite(motorTwo_InputTwo, LOW);
  delay(10);

}

void shootyShoot() {}
