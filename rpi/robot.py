#!/usr/bin/python
import cv2
import numpy as np
import time
import os
import math
import serial
from datetime import datetime
import wiringpi2 as wiringpi

SCREEN_WIDTH = 320
SCREEN_HEIGHT = 240

GREEN_PIN = 5
RED_PIN = 4
# SERIAL SETUP

port = serial.Serial("/dev/ttyUSB0", baudrate=115200, timeout=3.0)

panServoAngle = 90
tiltServoAngle = 180

capture = cv2.VideoCapture(0)
capture.set(3, SCREEN_WIDTH)
capture.set(4, SCREEN_HEIGHT)

hsv_min = np.array((0, 43, 81))
hsv_max = np.array((10, 255, 255))

frames = 0
start_time = time.time()
Cx, Cy, W, H, X, Y = 0, 0, 0, 0, 0, 0
lastServoUpdate = datetime.now()
wiringpi.wiringPiSetup()
wiringpi.pinMode(GREEN_PIN, 1)
wiringpi.pinMode(RED_PIN, 1) 

while True:
   # Grab one frame from camera
    ret, frame = capture.read()

    if frame is not None:
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
        thresholded = cv2.inRange(hsv_frame, hsv_min, hsv_max)
        contours,hierarchy = cv2.findContours(thresholded,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)

        maxdiag = 0;

        for cnt in contours:
            x,y,w,h = cv2.boundingRect(cnt)
            cx,cy = x+w/2, y+h/2
            if (math.sqrt(w*w+h*h)>maxdiag) :
                maxdiag=math.sqrt(w*w+h*h)
                Cx,Cy,W,H,X,Y=cx,cy,w,h,x,y

        #cv2.rectangle(frame,(X,Y),(X+W,Y+H),[0,23,255],2)
        #cv2.imshow("image", frame)
        if maxdiag > 10:
            wiringpi.digitalWrite(GREEN_PIN, 1)
            wiringpi.digitalWrite(RED_PIN, 0)
            if Cx < SCREEN_WIDTH/2-20:
                panServoAngle -= 2
                panServoAngle = max(0, panServoAngle)
            if Cx > SCREEN_WIDTH/2+20:
                panServoAngle += 2
                panServoAngle = min(180, panServoAngle)

            if Cy < SCREEN_HEIGHT/2-20:
                tiltServoAngle += 2
                tiltServoAngle = min(180, tiltServoAngle)
            if Cy > SCREEN_HEIGHT/2+20:
                tiltServoAngle -= 2
                tiltServoAngle = max(0, tiltServoAngle)

            print Cx, maxdiag, panServoAngle
            port.write('S')
            port.write(chr(panServoAngle))
            port.write(chr(tiltServoAngle))
            port.write('#')
        else:
            wiringpi.digitalWrite(GREEN_PIN, 0)
            wiringpi.digitalWrite(RED_PIN, 1)

        frames += 1
        if frames % 10 == 0:
            currtime = time.time()
            numsecs = currtime - start_time
            fps = frames / numsecs
            print "average FPS:", fps

cv2.DestroyAllWindows()
