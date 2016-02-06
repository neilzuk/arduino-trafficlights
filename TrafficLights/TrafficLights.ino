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

bool buttonPressed = false;
bool firstRun = true;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(red, OUTPUT);
	pinMode(amber, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(pedButton, INPUT);
	digitalWrite(pedButton, HIGH);
	pinMode(pedRed, OUTPUT);
	pinMode(pedGreen, OUTPUT);
	on(red);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (firstRun) {
		pedDisallowed();
		startTraffic();
		firstRun = false;
	}

	bool pedWaiting = digitalRead(pedButton) == LOW;
	if (pedWaiting)
		buttonPressed = true;

	if (buttonPressed) {
		stopTraffic();
		pedAllowed();
		delay(5000);
		pedDisallowed();
		startTraffic();
		// reset button
		buttonPressed = false;
	}
}

void startTraffic() {
	delay(2000);
	digitalWrite(amber, HIGH);
	delay(2000);
	digitalWrite(red, LOW);
	digitalWrite(amber, LOW);
	digitalWrite(green, HIGH);
}

void stopTraffic() {
	off(green);
	on(amber);
	delay(2000);
	on(red);
	off(amber);
}

void pedAllowed() {
	on(pedGreen);
	off(pedRed);
}

void pedDisallowed() {
	on(pedRed);
	off(pedGreen);
}

void on(int light) {
	digitalWrite(light, HIGH);
}

void off(int light) {
	digitalWrite(light, LOW);
}
