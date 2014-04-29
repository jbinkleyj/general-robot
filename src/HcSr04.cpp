#include <Arduino.h>
#include "HcSr04.h"

HcSr04::HcSr04(int echoPin, int triggerPin) {
    _echoPin = echoPin;
    _triggerPin = triggerPin;

    pinMode(_triggerPin, OUTPUT);
    pinMode(_echoPin, INPUT);
}


long HcSr04::read_distance() {

	long duration, distance;

	digitalWrite(_triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(_triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(_triggerPin, LOW);
	duration = pulseIn(_echoPin, HIGH);

	// Duration in microseconds
	distance = duration / 58.2;

	return distance;
	
}
