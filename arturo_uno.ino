#include <Servo.h>
#include <IRremote.h>

int IR_PIN = 2;
int shoulder_pin = 3;//
int degree = 90;
unsigned long previous_button;

Servo shoulder ; // initialize servo 
IRrecv receiver(IR_PIN);
decode_results results;

void sh_cw() {
  shoulder.write(degree+3);
  previous_button = results.value;
  // Serial.println(previous_button, HEX); was used for debugging
}
void sh_ccw() {
  shoulder.write(degree-3);
  previous_button = results.value; //1. attach the last code to a variable (also true for sh(cw)
  // Serial.println(previous_button, HEX); was used for debugging
}

void setup() {
  // put your setup code here, to run once
  shoulder.attach(shoulder_pin);
  shoulder.write(degree);                // when on, 90 degrees will be default position
  pinMode(shoulder_pin, OUTPUT);
  pinMode(IR_PIN, INPUT);
  digitalWrite(IR_PIN,HIGH);
  digitalWrite(shoulder_pin, HIGH);
  receiver.enableIRIn();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  degree = shoulder.read();
  if(receiver.decode(&results)) {
    Serial.println(results.value, HEX);
     
      if(results.value == 0xFFFFFFFF) {
         results.value = previous_button;  
          //before we go to chcek button presses, see if a button is being repeated, if so, highjack results.value with previous button press
         
         //Serial.println(results.value, HEX); // used to debug 

          }
    switch(results.value) {
      case 0xFF42BD: sh_ccw(); break; // 7
      case 0xFF52AD: sh_cw(); break;// 9
      case 0xFF6897: shoulder.write(0); // 0
    }
        Serial.println(degree);
        receiver.resume();
  }
}
