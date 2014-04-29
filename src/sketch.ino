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


#include <Servo.h>
#include "Scanner.h"
#include "HcSr04.h"
#include "L298n.h"

// Ultrasonic sensor pins
#define ECHO_PIN 13 // Echo Pin
#define TRIG_PIN 4 // Trigger Pin

// Servo pins
#define SERVO_PIN 3

// Motor Control pins
#define ENABLE_A 11
#define MOTOR_A1 10
#define MOTOR_A2 9

#define ENABLE_B 6
#define MOTOR_B1 7
#define MOTOR_B2 5

Servo * motor;
HcSr04 * hcsr04;
Scanner * scanner;
L298n * l298n;

// Global vars and constants
#define SCAN_PERIOD 200
#define DISTANCE_TRESHOLD 35

long last_scan_time;

void setup() {
    Serial.begin(9600);

    motor = new Servo();
    motor->attach(SERVO_PIN);
    hcsr04 = new HcSr04(ECHO_PIN, TRIG_PIN);
    l298n = new L298n(ENABLE_A, MOTOR_A1, MOTOR_A2, ENABLE_B, MOTOR_B1, MOTOR_B2);
    scanner = new Scanner(motor, hcsr04);

}

void loop() {

    long current_time = millis();

    ScanResponse scan_responde;

    if (current_time - last_scan_time > SCAN_PERIOD) {
        scan_responde = scanner->scan();
        last_scan_time = millis();
    }


    if (scan_responde.get_distance() != 0 && scan_responde.get_distance() < DISTANCE_TRESHOLD) {
        if (scan_responde.get_position() == CENTER_POSITION) {
            l298n->forwardMotorA();
            l298n->backwardMotorB();
            delay(500);
        } else if (scan_responde.get_position() == LEFT_POSITION) {
            l298n->forwardMotorB();
            l298n->backwardMotorA();
            delay(300);
        } else if (scan_responde.get_position() == RIGHT_POSITION) {
            l298n->forwardMotorA();
            l298n->backwardMotorB();
            delay(300);
        }
    } else {
        l298n->forwardMotors();
    }
}
