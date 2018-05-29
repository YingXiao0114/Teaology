#include <CapacitiveSensor.h> //conductive ink
#include "HX711.h" //load cell

//Light Sensor
#define LIGHTSENSOR01PIN A1 //Ambient light sensor for teascoop, reading
#define LIGHTSENSOR02PIN A2 //Ambient light sensor for fork,         reading

//Load Cell and Weight Sensor
#define calibration_factor -7050.0 
//LOADCELL01 TEAPOT - this sensor is under the teatop
#define DOUT01  10
#define CLK01  9
//LOADCELL02 TEACUP - this sensor is under the teacup!!!
#define DOUT02  5
#define CLK02  4

HX711 scale01(DOUT01, CLK01);
HX711 scale02(DOUT02, CLK02);

//TWO HANDS PICK UP THE CUP - Conductive tap
CapacitiveSensor cs_7_8 = CapacitiveSensor(7,8);
CapacitiveSensor cs_12_13 = CapacitiveSensor(12,13); 
unsigned long csSum;


int x1; // Tea scoop
int x2; // Fork
int x3; //Teapot
int x4; //Teacup
int x5; //Hands

float readingA2;

int pre = 0;
int cur = 0;
int diff = 0;

void setup() {
  Serial.begin(9600);

  // Ambient light sensor | TEA SCOOP
  pinMode(LIGHTSENSOR01PIN, INPUT);

  // Ambient light sensor | FORK
  pinMode(LIGHTSENSOR02PIN, INPUT);

  // LOADCELL01
  scale01.set_scale(calibration_factor);
  scale01.tare();

  //LOADCELL02
  scale02.set_scale(calibration_factor);
  scale01.tare();
}

void loop() {
  TeaScoop();
  Fork();
  Teapot();
  Teacup();
  Hands();
//  
  Serial.print(x1);
  Serial.print(",");
  Serial.print(x2);
  Serial.print(",");
  Serial.print(x3);
  Serial.print(",");
  Serial.print(x4);
  Serial.print(",");
  Serial.println(x5);

}

void TeaScoop (){
   float readingA1 = analogRead(LIGHTSENSOR01PIN);

//THIS LINE IS FOR TESTING
//   x1 = readingA1;

//WHEN PICK UP THE TEASCOOP


  if (readingA1 < 50){
    x1 = 0;   //the teapot is on the tray
  } else{
    x1 = 1;   //user picks up the teapot, start the animation
  }   
}

void Fork (){
  pre = cur;
  cur = readingA2;
  readingA2 = analogRead(LIGHTSENSOR02PIN);

  diff = cur - pre;
//  Serial.println(diff);
  if(diff< -900){
    x2 = 1;
    }
  else if(diff > 900 && diff < 1000){
    x2 = 2;
    }
//  else{
//    x2 = 0;
//    }

//  Serial.println(x2);

//  Serial.println(x2);
  //THIS LINE IS FOR TESTING
//  x2 = readingA2;
  
//  if (readingA2 > 1000){
//    x2 = 0;   //the fork is on the tray
//  } else{
//    x2 = 1;   //user picks up the fork, start the animation
//  }   
}

void Teapot (){
//  if (scale01.get_units() > 30){
//    x3 = 1;
//  } else {
//    x3 =0; 
//  }
  //THIS CODE IS FOR TESTING
  x3 = scale01.get_units();
}

void Teacup (){
  if (scale02.get_units() > 50){
    x4 = 1;
  } else {
    x4 =0; 
  }
  
  //THIS CODE IS FOR TESTING
//   x4 = scale02.get_units(); 
}

void Hands (){
  long cs01 = cs_7_8.capacitiveSensor(80);
  long cs02 = cs_12_13.capacitiveSensor(80);

  if (cs01 > 1000 && cs02 > 1000) {
    x5 = 1;
  } else {
    x5 = 0;
  }
}



