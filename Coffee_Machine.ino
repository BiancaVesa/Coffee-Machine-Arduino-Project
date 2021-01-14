#include <Servo.h>
const int BUTTON1 = 6;     // button for espresso is set on pin 6
const int BUTTON2 = 13;    // button for double espresso is set on pin 13
const int BUTTON3 = 12;     // button for cappuccino is set on pin 
const int PUMP1 = 7;       // the water pump is set on pin 7
const int PUMP2 = 10;       // the milk pump is set on pin 
const int RED = 2;         // the red led is set on pin 2
const int GREEN = 3;       // the green led is set on pin 3
const int BLUE = 4;        // the blue led is set on pin 4
const int BUZZER = 11;     // the buzzer is set on pin 11

int ESPRESSO = 0;          // stores the state of BUTTON1
int DOUBLE_ESPRESSO = 0;   // stores the state of BUTTON2
int CAPPUCCINO = 0;        // stores the state of BUTTON3
int readyCoffee = 0;       // flag to signal that the coffee is ready
int idle = 1;              // flag to signal that the machine is in idle mode

Servo myservo;             // create servo object to control a servo

int initial_pos = 0;       // variable to store the servo initial position

void setup()
{
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  noTone(BUZZER);               // the buzzer will ring only when the coffee is ready

  // the pumps will start only when one of the buttons is pressed
  digitalWrite(PUMP1, LOW);
  digitalWrite(PUMP2, LOW);

  myservo.attach(9);            // attaches the servo on pin 9 to the servo object
  myservo.write(initial_pos);   // bring the servo arm back to the initial position, to prepare the next coffee
}

void loop()
{

  // the blue led is on to signal that the machine is in idle mode 
  if (idle == 1) {
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
  }

  // read the state of each button
  ESPRESSO = digitalRead(BUTTON1);
  DOUBLE_ESPRESSO = digitalRead(BUTTON2);
  CAPPUCCINO = digitalRead(BUTTON3);

  // if the button corresponding to the espresso is pressed ..
  if (ESPRESSO == HIGH)
  {
    // .. start the coffee making process
    espresso();
  }
  else {
    digitalWrite(PUMP1, LOW);
  }


  // if the button corresponding to the double espresso is pressed ..
  if (DOUBLE_ESPRESSO == HIGH)
  {
    // .. start the coffee making process
    double_espresso();
  }
  else {
    digitalWrite(PUMP1, LOW);
  }

  
  // if the button corresponding to the cappuccino is pressed ..
  if (CAPPUCCINO == HIGH)
  {
    // .. start the coffee making process
    cappuccino();
  }
  else {
    digitalWrite(PUMP1, LOW);
    digitalWrite(PUMP2, LOW);
  }

  // when the coffee is ready, prepare the machine for the next one
  if (readyCoffee == 1) {
    ready_coffee();
  }
}


void espresso() {
  idle = 0;                   // the machine switches from idle mode
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, HIGH);    // red led signals that a coffee is being prepared
  digitalWrite(GREEN, LOW);

  for (int pos = 0; pos <= 180; pos ++) // servo arm goes from 0 degrees to 180 degrees to put the coffee in the mug
  {
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(PUMP1, HIGH);   // start pumping water for 3 seconds
  delay(6000);
  digitalWrite(PUMP1, LOW);    // stop pumping water
  
  readyCoffee = 1;             // the coffee is ready
}


void double_espresso() {
  idle = 0;                   // the machine switches from idle mode
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, HIGH);    // red led signals that a coffee is being prepared
  digitalWrite(GREEN, LOW);

  for (int pos = 0; pos <= 180; pos ++) // servo arm goes from 0 degrees to 180 degrees to put the coffee in the mug
  {
    myservo.write(pos);
    delay(15);
  }

  digitalWrite(PUMP1, HIGH);   // start pumping water for 5 seconds
  delay(12000);
  digitalWrite(PUMP1, LOW);    // stop pumping water

  readyCoffee = 1;             // the coffee is ready
}


void cappuccino() {
  idle = 0;                   // the machine switches from idle mode
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, HIGH);    // red led signals that a coffee is being prepared
  digitalWrite(GREEN, LOW);

  digitalWrite(PUMP2, HIGH);   // start pumping milk for 3 seconds
  delay(3000);
  digitalWrite(PUMP2, LOW);    // stop pumping milk

  readyCoffee = 1;             // the coffee is ready
}


void ready_coffee() {
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);    // green led signals that the coffee is ready

  tone(BUZZER, 2000);           // the buzzer also signals that the coffee is ready
  delay(4000);
  noTone(BUZZER);

  delay(5000);                  // wait 5 seconds

  myservo.write(initial_pos);   // then prepare the machine for the next coffee by bringing the arm back to its initial position
  
  idle = 1;                     // machine enters idle mode
  readyCoffee = 0;
}
