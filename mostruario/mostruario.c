/* Mostruario */

const int BUTTON = 2;
const int RED_LED = 9;
const int MOTOR = 3;
const int POTENTIOMETER = 5;
boolean partyHard;
int buttonState, ledState, motorState, potentiometerState;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(MOTOR, OUTPUT);   
  partyHard = false;
}

void loop() {
  buttonState = digitalRead(BUTTON);
  if (buttonState == 0) partyHard = !partyHard;
  if (!partyHard) ledState = potentiometerState = analogRead(POTENTIOMETER)/4;
  else ledState = potentiometerState = 255;
  analogWrite(RED_LED, ledState);
  analogWrite(MOTOR, potentiometerState);
  Serial.println(potentiometerState);
  delay(1);
}