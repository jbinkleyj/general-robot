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
#include "L298n.h"


L298n::L298n(int enable_motor_A_pin, int motor_A1_pin, int motor_A2_pin, int enable_motor_B_pin, int motor_B1_pin, int motor_B2_pin) {
    _enable_motor_A_pin = enable_motor_A_pin;
    _enable_motor_B_pin = enable_motor_B_pin;
    _motor_A1_pin = motor_A1_pin;
    _motor_A2_pin = motor_A2_pin;
    _motor_B1_pin = motor_B1_pin;
    _motor_B2_pin = motor_B2_pin;

    pinMode(_enable_motor_A_pin, OUTPUT);
    pinMode(_enable_motor_B_pin, OUTPUT);
    pinMode(_motor_A1_pin, OUTPUT);
    pinMode(_motor_A2_pin, OUTPUT);
    pinMode(_motor_B1_pin, OUTPUT);
    pinMode(_motor_B2_pin, OUTPUT);
}

void L298n::setMotorsSpeed(int percentage) {
    setMotorASpeed(percentage);
    setMotorBSpeed(percentage);
}

void L298n::setMotorASpeed(int percentage) {
    int speed = (TOP_SPEED * percentage) / 100;
    analogWrite(_enable_motor_A_pin, speed);
}

void L298n::setMotorBSpeed(int percentage) {
    int speed = (TOP_SPEED * percentage) / 100;
    analogWrite(_enable_motor_B_pin, speed);
}

void L298n::forwardMotors() {
    forwardMotorA();
    forwardMotorB();
}

void L298n::brakeMotors() {
    brakeMotorA();
    brakeMotorB();
}

void L298n::forwardMotorA() {
    digitalWrite(_motor_A1_pin, HIGH);
    digitalWrite(_motor_A2_pin, LOW);
}

void L298n::forwardMotorB() {
    digitalWrite(_motor_B1_pin, HIGH);
    digitalWrite(_motor_B2_pin, LOW);
}

void L298n::backwardMotorA() {
    digitalWrite(_motor_A1_pin, LOW);
    digitalWrite(_motor_A2_pin, HIGH);
}

void L298n::backwardMotorB() {
    digitalWrite(_motor_B1_pin, LOW);
    digitalWrite(_motor_B2_pin, HIGH);
}

void L298n::brakeMotorA() {
    digitalWrite(_motor_A1_pin, HIGH);
    digitalWrite(_motor_A2_pin, HIGH);
}

void L298n::brakeMotorB() {
    digitalWrite(_motor_B1_pin, HIGH);
    digitalWrite(_motor_B2_pin, HIGH);
}


