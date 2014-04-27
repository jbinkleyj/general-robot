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


// Global vars and constants
#define SCAN_PERIOD 200
#define DISTANCE_TRESHOLD 35

long last_scan_time;

void setup() {
    Serial.begin(9600);

    motor = new Servo();
    hcsr04 = new HcSr04(ECHO_PIN, TRIG_PIN);

    // Setup ultrasonic pin state
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Attach servo
    motor->attach(SERVO_PIN);

    // Setup motor pins state
    pinMode(ENABLE_A, OUTPUT);
    pinMode(MOTOR_A1, OUTPUT);
    pinMode(MOTOR_A2, OUTPUT);

    pinMode(ENABLE_B, OUTPUT);
    pinMode(MOTOR_B1, OUTPUT);
    pinMode(MOTOR_B2, OUTPUT);
    enableMotors();

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
            turnRight(500);
        } else if (scan_responde.get_position() == LEFT_POSITION) {
            turnLeft(300);
        } else if (scan_responde.get_position() == RIGHT_POSITION) {
            turnRight(300);

        }
    } else {
        forward(0);
    }


}

// Isolate this crappy code
void motorAOn()
{
    digitalWrite(ENABLE_A, HIGH);
}

void motorBOn()
{
    digitalWrite(ENABLE_B, HIGH);
}

//disable motors
void motorAOff()
{
    digitalWrite(ENABLE_B, LOW);
}

void motorBOff()
{
    digitalWrite(ENABLE_A, LOW);
}

//motor A controls
void motorAForward()
{
    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, LOW);
}

void motorABackward()
{
    digitalWrite(MOTOR_A1, LOW);
    digitalWrite(MOTOR_A2, HIGH);
}

//motor B contorls
void motorBForward()
{
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, LOW);
}

void motorBBackward()
{
    digitalWrite(MOTOR_B1, LOW);
    digitalWrite(MOTOR_B2, HIGH);
}

//Define High Level Commands

void enableMotors()
{
    motorAOn();
    motorBOn();
}

void disableMotors()
{
    motorAOff();
    motorBOff();
}

void forward(int time)
{
    motorAForward();
    motorBForward();
}

void backward(int time)
{
    motorABackward();
    motorBBackward();
    delay(time);
}

void turnLeft(int time)
{
    motorABackward();
    motorBForward();
    delay(time);
}

void turnRight(int time)
{
    motorAForward();
    motorBBackward();
    delay(time);
}

void motorABrake()
{
    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, HIGH);
}

void motorBBrake()
{
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, HIGH);
}

void brake(int time)
{
    motorABrake();
    motorBBrake();

}
