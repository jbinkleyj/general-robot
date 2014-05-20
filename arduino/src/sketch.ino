#include "Servo.h"
#include "Wire.h"

#include "Hmc5883l.h"
#include "L298n.h"

#define DEBUG 1
#define RUNNING_TIME 8000
#define TOP_SPEED 255

// Motor Control pins
#define ENABLE_A 11
#define MOTOR_A1 8
#define MOTOR_A2 12

#define ENABLE_B 3
#define MOTOR_B1 5
#define MOTOR_B2 7


#define SERVO_PAN   9
#define SERVO_TILT 10


Servo panServo;
Servo tiltServo;

//

int time = 0;

char serialBuffer[4];

void setup() {
    Wire.begin();
    Serial.begin(115200);
    
    panServo.attach(SERVO_PAN);
    tiltServo.attach(SERVO_TILT);
    
     panServo.write(90);
     tiltServo.write(180);
}

void loop() {

    if (Serial.available() >= 4) {
        Serial.readBytesUntil('#', serialBuffer, 4);
        Serial.println("Got 4 bytes");
    }


    if (serialBuffer[0] == 'S') {
        unsigned char panServoAngle = serialBuffer[1];
        unsigned char tiltServoAngle = serialBuffer[2];
        panServo.write(panServoAngle);
        tiltServo.write(tiltServoAngle);
        serialBuffer[0] = '#';
    }
}
