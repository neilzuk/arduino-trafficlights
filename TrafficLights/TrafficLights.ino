/*
Name:		TrafficLights.ino
Created:	2/6/2016 4:43:44 PM
Author:	Neil
*/
// Road
int red = A0;
int amber = A1;
int green = A2;
// Ped
int pedRed = A3;
int pedGreen = A4;
int pedButton = 2;


// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(red, OUTPUT);
	pinMode(amber, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(pedButton, INPUT);
	digitalWrite(pedButton, HIGH);
	pinMode(pedRed, OUTPUT);
	pinMode(pedGreen, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	digitalWrite(red, HIGH);
	digitalWrite(pedRed, HIGH);

	bool buttonPressed = digitalRead(pedButton);
	Serial.println(buttonPressed);
	if (buttonPressed == LOW) {
		digitalWrite(red, LOW);
		digitalWrite(green, HIGH);

		digitalWrite(pedRed, LOW);
		digitalWrite(pedGreen, HIGH);
		delay(2000);
		digitalWrite(green, LOW);
		digitalWrite(pedGreen, LOW);

	}
}
