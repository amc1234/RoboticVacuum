/****************************************************************************
   Project: Robotic Vacuum
   By: Andrea M and Steven Pheng
   Date: December 12th, 2018

   Code by: Andrea M

   Compatible with an Android app called Ardroid which lets you control Arduino 
   pins through a Bluetooth module. App and template code by: Anurag Goel.

   androidPin2 -> Vacuum
   androidPin3 -> Motor1 State (direction)
   androidPin4 -> Motor1 Speed
   androidPin5 -> Motor2 State (direction)
   androidPin6 -> Motor2 Speed
***************************************************************************/
#define START_CMD_CHAR '*'
#define END_CMD_CHAR '#'
#define DIV_CMD_CHAR '|'
#define CMD_DIGITALWRITE 10
#define CMD_ANALOGWRITE 11
#define CMD_TEXT 12
#define CMD_READ_ARDROID 13
#define MAX_COMMAND 20  
#define MIN_COMMAND 10  
#define IN_STRING_LENGHT 40
#define MAX_ANALOGWRITE 255
#define PIN_HIGH 3
#define PIN_LOW 2

#include <Wire.h>
#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//Declaring motors
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

//Declaring motor speed variables and set to zero
int motorSpeed1 = 0;
int motorSpeed2 = 0;

//Declaring variable for motor direction: forward, backwards, or stopped(release)
uint8_t motorState1 = RELEASE;
uint8_t motorState2 = RELEASE;

//Declaring constant variables for pins used
const int VACUUM_PIN = 2;
const int MOTOR_1_PIN = 3;
const int MOTOR_1_SPEED_PIN = 4;
const int MOTOR_2_PIN = 5;
const int MOTOR_2_SPEED_PIN = 6;

String inText;  //String to receive data from app

//Initializing all required functions
void read_bluetooth();                  //Reads Bluetooth data sent by app
void set_vacuum(int pin_value);         //Turns on or off the vacuum
bool units_to_boolean(int pin_value);   //Converts digital units received from pins to a boolean value
void set_motor(uint8_t motorState, int pin_value, int pin_num, int motorSpeed); //Sets the direction and speed of the motor
uint8_t units_to_state(int pin_value);  //Converts analog units received from pins to a direction
void pin_chosen(int pin_num, int pin_value); //Depending on the pin chosen then do the following code

void setup() {
  Serial.begin(9600);
  Serial.flush();
  AFMS.begin();
}

void loop()
{
  read_bluetooth(); //Reads Bluetooth data sent by app
}                   //read_bluetooth(); calls pin_chosen(int pin_num, int pin_value);

void pin_chosen(int pin_num, int pin_value){
  switch (pin_num){
    case 3: //Motor 1 direction
      motorState1 = units_to_state(pin_value); //From read pin, check what direction it is set to
      set_motor(motorState1, pin_value, MOTOR_1_PIN, motorSpeed1); //Set motor direction
      break;
    case 4: //Motor 1 speed
      motorSpeed1 = pin_value;  //From read pin, check what speed it is set to
      set_motor(motorState1, pin_value, MOTOR_1_PIN, motorSpeed1); //Set motor speed
      break;
    case 5: //Motor 2 direction
      motorState2 = units_to_state(pin_value); //From read pin, check what direction it is set to
      set_motor(motorState2, pin_value, MOTOR_2_PIN, motorSpeed2); //Set motor direction
      break;
    case 6: //Motor 2 speed
      motorSpeed2 = pin_value;  //From read pin, check what speed it is set to
      set_motor(motorState2, pin_value, MOTOR_2_PIN, motorSpeed2);  //Set motor speed
      break;
  }
}

void read_bluetooth(){
 
  Serial.flush();
  int ard_command = 0;
  int pin_num = 0;
  int pin_value = 0;

  char get_char = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag 
  get_char = Serial.read();
  if (get_char != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming command type
  ard_command = Serial.parseInt(); // read the command
  // parse incoming pin# and value  
  pin_num = Serial.parseInt(); // read the pin
  pin_value = Serial.parseInt();  // read the value
  // 1) GET TEXT COMMAND FROM ARDROID
  if (ard_command == CMD_TEXT){   
    inText =""; //clears variable for new input   
    while (Serial.available())  {
   char c = Serial.read();
  
     //gets one byte from serial buffer
      delay(5);
      if (c == END_CMD_CHAR) { // if we the complete string has been read
        Serial.println(inText);
        break;
      }              
      else {
        if (c !=  DIV_CMD_CHAR) {
          inText += c; 
          delay(5);
        }
      }
    }
  }

  // 2) GET digitalWrite DATA FROM ARDROID
  if (ard_command == CMD_DIGITALWRITE){  
    if (pin_value == PIN_LOW) pin_value = LOW;
    else if (pin_value == PIN_HIGH) pin_value = HIGH;
    else return; // error in pin value. return. 
    if (pin_num == VACUUM_PIN)  //If the pin read is the vacuum pin
      set_vacuum(pin_value);    //Turn on or off the vacuum depending on read value
    return;  // return from start of loop()
  }

  // 3) GET analogWrite DATA FROM ARDROID
  if (ard_command == CMD_ANALOGWRITE) {  
    analogWrite(pin_num, pin_value); 
    pin_chosen(pin_num, pin_value); //Depending on the pin chosen then do the following code
    return;  // Done. return to loop();
  }

  // 4) SEND DATA TO ARDROID
  if (ard_command == CMD_READ_ARDROID) { 
    // char send_to_android[] = "Place your text here." ;
    // Serial.println(send_to_android);   // Example: Sending text
    Serial.print(" Analog 0 = "); 
    Serial.println(analogRead(A0));  // Example: Read and send Analog pin value to Arduino
    return;  // Done. return to loop();
  }
}

uint8_t units_to_state(int pin_value){    //Converts analog units received from pins to a direction. Analog pins each have 255 units
  if (pin_value <= (255/3))   //If value is in the bottom third set direction to backwards
    return BACKWARD;
  else if (pin_value >= ((255/3)*2))  //If value is in the top third set direction to forwards
    return FORWARD;
  else                                  //Else set to release(stopped)
    return RELEASE;
}

void set_motor(uint8_t motorState, int pin_value, int pin_num, int motorSpeed){ //Sets the direction and speed of the motor
  if (pin_num == MOTOR_1_PIN){  //If motor 1 is chosen
    myMotor1->setSpeed(motorSpeed); //Set speed for motor 1
    myMotor1->run(motorState);      //Set direction for motor 1
  }
  if (pin_num == MOTOR_2_PIN){  //If motor 2 is chosen
    myMotor2->setSpeed(motorSpeed); //Set speed for motor 2
    myMotor2->run(motorState);      //Set direction for motor 2
  }
}

bool units_to_boolean(int pin_value){ //Converts digital units received from pins to a boolean value. Digital pins each have 1024 units
  return pin_value <= (1024/2);  //If value is less than half return 0
}

void set_vacuum(int pin_value){
  digitalWrite(VACUUM_PIN, units_to_boolean(pin_value));  //Turn on or off the vacuum depending on read value
}
