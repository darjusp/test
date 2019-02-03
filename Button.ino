#include <Encoder.h>

const int buttonPinA = 9; 
const int buttonPinB = 10; 
const int buttonPinC = 4; 
const int buttonPinD = 5;
const int buttonPinCent = 7;
const int ledPin =  13;

// variables will change:
int buttonStateA = 0;
int buttonStateB = 0; 
int buttonStateC = 0;
int buttonStateD = 0;
int buttonStateCent = 0;  
int buttonWhich = 0;

int buttonState;
int lastButtonState = LOW;  

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100; 

int oldPosition = 0;
// Initialize encoder pins
Encoder myEnc(2, 3);
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(buttonPinC, INPUT);
  pinMode(buttonPinD, INPUT);
  pinMode(buttonPinCent, INPUT);
  Serial.begin (9600);
}

void loop() {
  // read the state of the pushbutton value:
  // Switch Buttons
  buttonStateA = digitalRead(buttonPinA);
  buttonStateB = digitalRead(buttonPinB);
  buttonStateC = digitalRead(buttonPinC);
  buttonStateD = digitalRead(buttonPinD);
  buttonStateCent = digitalRead(buttonPinCent);
  buttonWhich = 0;
  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateCent == HIGH) {
    buttonWhich = 5;
  }
  if (buttonStateA == HIGH) {
    buttonWhich = 1;
  }
  if (buttonStateB == HIGH) {
    buttonWhich = 2;
  }
  if (buttonStateC == HIGH) {
    buttonWhich = 3;
  }
  if (buttonStateD == HIGH) {
    buttonWhich = 4;
  }

  if (buttonWhich != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    switch (buttonWhich){
      case 1:
        Serial.println("A Button");
        digitalWrite(ledPin, HIGH);
        break;
      case 2:
        Serial.println("B Button");
        digitalWrite(ledPin, HIGH);
        break;
      case 3:
        Serial.println("C Button");
        digitalWrite(ledPin, HIGH);
        break;
      case 4:
        Serial.println("D Button");
        digitalWrite(ledPin, HIGH);
        break;
      case 5:
        Serial.println("Center Button");
        digitalWrite(ledPin, HIGH);
        break;
      default:
        // turn LED off:
        digitalWrite(ledPin, LOW);
        break;
    }
  }
  lastButtonState = buttonWhich;
  // Rotate Button
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  
}
