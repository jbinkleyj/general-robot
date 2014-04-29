/*
   Generic Robot with obstacle avoidance capabilities
   Copyright (C) 2014  Joao Salavisa (joao.salavisa@gmail.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
