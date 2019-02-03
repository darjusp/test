// constants won't change. They're used here to set pin numbers:
const int buttonPinA = 2; 
const int buttonPinB = 3; 
const int buttonPinC = 4; 
const int buttonPinD = 5;// the number of the pushbutton pin
const int buttonPinCent = 7;// the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonStateA = 0;         // variable for reading the pushbutton status
int buttonStateB = 0; 
int buttonStateC = 0;         // variable for reading the pushbutton status
int buttonStateD = 0;
int buttonStateCent = 0;  
int buttonWhich = 0;

int buttonState;
int lastButtonState = LOW;  

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100; 

int val;
int encoder0PinA = 9;
int encoder0PinB = 10;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);
  pinMode(buttonPinC, INPUT_PULLUP);
  pinMode(buttonPinD, INPUT_PULLUP);
  pinMode(buttonPinCent, INPUT_PULLUP);
  pinMode (encoder0PinA, INPUT_PULLUP);
  pinMode (encoder0PinB, INPUT_PULLUP);
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
  if (buttonStateA == LOW) {
    buttonWhich = 1;
  }
  if (buttonStateB == LOW) {
    buttonWhich = 2;
  }
  if (buttonStateC == LOW) {
    buttonWhich = 3;
  }
  if (buttonStateD == LOW) {
    buttonWhich = 4;
  }
  if (buttonStateCent == LOW) {
    buttonWhich = 5;
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
  
  // Rotate button
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      Serial.println("Volume Down");
      encoder0Pos--;
    } else {
       if (digitalRead(encoder0PinA) == HIGH) {
        Serial.println("Volume UP");
        encoder0Pos++;
       }
    }
    Serial.println(encoder0Pos);
  }
  encoder0PinALast = n;
}
