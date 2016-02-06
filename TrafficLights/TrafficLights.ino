/*
Name:		TrafficLights.ino
Created:	2/6/2016 4:43:44 PM
Author:	Neil
*/
// settings
unsigned long waitTime = 5000; // Time the pedestrian has to wait after pressing button.
unsigned long delayedTime = 0; // Used to store the time the lights should stop the traffic for the pedestrian.
bool buttonPressed = false;
bool firstRun = true;
// Road
int red = A0;
int amber = A1;
int green = A2;
// Ped
int pedRed = A3;
int pedGreen = A4;
int pedWaitlight = A5;
int pedButton = 2;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(red, OUTPUT);
	pinMode(amber, OUTPUT);
	pinMode(green, OUTPUT);
	pinMode(pedButton, INPUT);
	digitalWrite(pedButton, HIGH); // Button signal set high so we can detect when button pressed (low).
	pinMode(pedRed, OUTPUT);
	pinMode(pedGreen, OUTPUT);
	pinMode(pedWaitlight, OUTPUT);
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
	if (pedWaiting && buttonPressed == false) {
		buttonPressed = true;
		delayedTime = millis() + waitTime;
		on(pedWaitlight);
	}

	if (buttonPressed && millis() >= delayedTime) {
		stopTraffic();
		pedAllowed();
		delay(5000);
		pedDisallowed();
		startTraffic();
		// reset button & clock;
		buttonPressed = false;
		delayedTime = 0;
	}
}

void startTraffic() {
	delay(2000);
	on(amber);
	delay(2000);
	off(red);
	off(amber);
	on(green);
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
	off(pedWaitlight);
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
