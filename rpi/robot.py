#!/usr/bin/python
import cv2
import numpy as np
import time
import os
import math
import serial

capture = cv2.VideoCapture(0)
capture.set(3, 320)
capture.set(4, 240)

hsv_min = np.array((0, 43, 81))
hsv_max = np.array((10, 255, 255))

frames = 0
start_time = time.time()
Cx,Cy,W,H,X,Y=0,0,0,0,0,0
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

        cv2.rectangle(frame,(X,Y),(X+W,Y+H),[0,23,255],2)
        print Cx, Cy
        cv2.imshow("image", frame)
        #cv2.imshow("th", thresholded)
        frames += 1
        if frames % 10 == 0:
            currtime = time.time()
            numsecs = currtime - start_time
            fps = frames / numsecs
            print "average FPS:", fps

cv2.DestroyAllWindows()
