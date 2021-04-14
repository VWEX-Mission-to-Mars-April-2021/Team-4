/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/

// help

const int LEFT_FEEDBACK = 2; // Pin numbers on Rover
const int RIGHT_FEEDBACK = 3;

volatile int leftcounter = 0; // initiate counter to zero for start
volatile int rightcounter = 0; // counter could always be reset

const int RIGHT_FORWARD = 12;
const int RIGHT_REVERSE = 11;
const int RIGHT_ENABLE = 10;
const int LEFT_ENABLE = 9;
const int LEFT_FORWARD = 8;
const int LEFT_REVERSE = 7;

const int FORWARD_IN_MILLISECONDS = 5000;
const int STOP_IN_MILLISECONDS = 1000;
const int REVERSE_IN_MILLISECONDS = 2000;

const int COUNTS_PER_METRE = 435;
/*
const int LEFT_TURN_SPEED = 200;
const int RIGHT_TURN_SPEED = 200;
*/
void setup()
{
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(LEFT_FEEDBACK),LeftMotorISR,RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_FEEDBACK),RightMotorISR,RISING);
  
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(LEFT_FORWARD, OUTPUT);
  
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  
  pinMode(RIGHT_REVERSE, OUTPUT);
  pinMode(LEFT_REVERSE, OUTPUT);
  
}

void loop()
{
  // Print out left counter value until the motors reach 2 metres
  if (leftcounter >= COUNTS_PER_METRE * 2)
  {
    TurnOffMotors();
  }
  else
  {
    Serial.print("Left Counter ");
    Serial.println(leftcounter); // This is printing then a new Line after
    MoveForward();

  }
}

void MoveForward()
{
  TurnOnMotors();
  digitalWrite(RIGHT_REVERSE, LOW);
  digitalWrite(LEFT_REVERSE, LOW);
  
  digitalWrite(RIGHT_FORWARD, HIGH);
  digitalWrite(LEFT_FORWARD, HIGH);
}

void Reverse()
{ 
  TurnOnMotors();
  
  digitalWrite(RIGHT_FORWARD, LOW);
  digitalWrite(LEFT_FORWARD, LOW);
  
  digitalWrite(RIGHT_REVERSE, HIGH);
  digitalWrite(LEFT_REVERSE, HIGH);
}

void TurnOffMotors()
{  
  digitalWrite(RIGHT_ENABLE,LOW);
  digitalWrite(LEFT_ENABLE,LOW);
  digitalWrite(RIGHT_FORWARD,LOW);
  digitalWrite(LEFT_FORWARD,LOW);
  digitalWrite(RIGHT_REVERSE,LOW);
  digitalWrite(LEFT_REVERSE,LOW);
}
/*
void TurnRight()
{
  
  
  digitalWrite(RIGHT_TURN, HIGH);
  digitalWrite(LEFT_TURN, LOW);
}

void TurnLeft()
{
  digitalWrite(LEFT_TURN, HIGH);
  digitalWrite(RIGHT_TURN, LOW);
}
*/
void TurnOnMotors()
{
  digitalWrite(RIGHT_ENABLE, HIGH);
  digitalWrite(LEFT_ENABLE, HIGH);
}

void LeftMotorISR(){
  // adds one to the counter on each motor revolution
  leftcounter++;
}
void RightMotorISR() {
  // adds one to the counter on each motor revolution
  rightcounter++;
}
