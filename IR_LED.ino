#include<IRremote.h>

#define IR_PIN 4    //These pins refer to where on the arduino are your parts connected
#define LED_PIN 11  //In this instance, my LED is connected to pin 11
#define BUDDY_LED 10

IRrecv irrecv(IR_PIN);    // We name our dog (IR PIN) "irrecv" and we tell our pet to fetch info from (IR_PIN)
decode_results results;   // We name the results from our code "results

void flicker() {
  if(digitalRead(LED_PIN) == LOW) {
    digitalWrite(BUDDY_LED, HIGH);
  }
  else  {
    digitalWrite(BUDDY_LED, LOW);
  }
}

void simple_on() {
      digitalWrite(LED_PIN, HIGH);   //this tells our pin to turn on for a second and off, but it is in a void, so we have to call upon this function in loop()
      flicker();
      delay(1000);
      digitalWrite(LED_PIN, LOW);
      flicker();
      }    

void flash_on() {
        digitalWrite(LED_PIN, HIGH);  //this will go on and off forever bc of recursion
        flicker();
        delay(100);
        digitalWrite(LED_PIN, LOW);
        flicker();
        delay(100);                   //spam down button for rave
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);                   //we need to set our pins, we are receving info from IR, so IR is input
  pinMode(IR_PIN, INPUT);
  digitalWrite(IR_PIN, HIGH);
  irrecv.enableIRIn();                        //this says to begin receivng infromation from IR
}

void loop() {
  if(irrecv.decode(&results)) {               //if we find a result, use switch to compare the button presses
    switch(results.value) {
      case 0xFF18E7: simple_on(); break;      // up botton triggers simple_(on)
      case 0xFF4AB5: flash_on(); break;       // down button triggers flash_on
   }
  irrecv.resume();                            //after receiving signal, continue to receive more signals
  // put your main code here, to run repeatedly:

  }
}
