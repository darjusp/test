#include <Encoder.h>

const int buttonPinA = 8;
const int buttonPinB = 9;
const int buttonPinC = 10;
const int buttonPinD = 11;
const int buttonPinCent = 12;
const int ledPin =  13;

// variables will change:
int buttonStateA = 0;
int buttonStateB = 0;
int buttonStateC = 0;
int buttonStateD = 0;
int buttonStateCent = 0;
int buttonStatus = 0; // 0 - neutral, 1 - pressed, 2 - released
int buttonWhich = 0;

int buttonState;
int lastButtonState = 0;
boolean buttonNotReleased = false;
unsigned long lastPressedTime = 0;
unsigned long debounceDelay = 10;
unsigned long longPush = 1000;

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
  if ((lastButtonState == 0) && (buttonWhich > 0) && (buttonStatus == 0) && (buttonNotReleased == false)) {
    // button was pressed
    buttonStatus = 1;
    lastPressedTime = millis();
  }
  
  if ((millis() - lastPressedTime) > longPush && (buttonStatus == 1)) {
    // its long press lets imitate button release
    buttonStatus = 2;
    buttonWhich = 0;
    buttonNotReleased = true;
  }

  if ((lastButtonState > 0) && (buttonWhich == 0) && (buttonStatus == 1) ) {
    // button released from normal press
    if (buttonNotReleased == true){
      buttonNotReleased = false;
    }else{
    // button was released
      buttonStatus = 2;
    }
  }
  if (lastButtonState == 0){
    // button released from long press
    buttonNotReleased = false;
  }
  
  if (((millis() - lastPressedTime) > debounceDelay) && buttonStatus == 2) {
  //if (buttonReleased==true) {
    switch (lastButtonState) {
      case 1:
        if ((millis() - lastPressedTime) > longPush) {
          Serial.println("Long A Button");
        } else {
          Serial.println("A Button");
          digitalWrite(ledPin, HIGH);
        }
        buttonStatus = 0;
        break;
      case 2:
        if ((millis() - lastPressedTime) > longPush) {
          Serial.println("Long B Button");
        } else {
          Serial.println("B Button");
          digitalWrite(ledPin, HIGH);
        }
        buttonStatus = 0;
        break;
      case 3:
        if ((millis() - lastPressedTime) > longPush) {
          Serial.println("Long C Button");
        } else {
          Serial.println("C Button");
          digitalWrite(ledPin, HIGH);
        }
        buttonStatus = 0;
        break;
      case 4:
        if ((millis() - lastPressedTime) > longPush) {
          Serial.println("Long D Button");
        } else {
          Serial.println("D Button");
          digitalWrite(ledPin, HIGH);
        }
        buttonStatus = 0;
        break;
      case 5:
        if ((millis() - lastPressedTime) > longPush) {
          Serial.println("Long Center Button");
        } else {
          Serial.println("Center Button");
          digitalWrite(ledPin, HIGH);
        }
        buttonStatus = 0;
        break;
      default:
        // turn LED off:
        Serial.println("default");
        digitalWrite(ledPin, LOW);
        buttonStatus = 0;
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
