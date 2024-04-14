# cv2 is computer vision library
import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

serialInst = serial.Serial(baudrate=9600, port = 'COM5')
detector = HandDetector(detectionCon=0.8, maxHands=2)
preValue = curValue = 0

def led(x):
    # time.sleep(3)
    serialInst.write(x.encode())
    print(x)
    time.sleep(0.4)

video = cv2.VideoCapture(0)
while True:
    ret, frame = video.read()
    hands, img = detector.findHands(frame)
    # print(hands)
    if hands:
        lmlist = hands[0]
        fingerUp = detector.fingersUp(lmlist)
        # print(fingerUp)
        if fingerUp == [0,0,0,0,0]:
             cv2.putText(frame, "Finger count: S", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255), 1, cv2.LINE_AA)

             curValue = 0
             if curValue != preValue:
                 preValue = curValue
                 led("0")
        if fingerUp == [0,1,0,0,0]:
            cv2.putText(frame, "Finger count: F", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 1,
                        cv2.LINE_AA)
            curValue = 1
            if curValue != preValue:
                preValue = curValue
                led("1")

        if fingerUp == [0,1,1,0,0]:
             cv2.putText(frame, "Finger count: R", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255), 1, cv2.LINE_AA)
             curValue = 2
             if curValue != preValue:
                 preValue = curValue
                 led("11")
        if fingerUp == [0,1,1,1,0]:
             cv2.putText(frame, "Finger count: L", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255), 1, cv2.LINE_AA)
             curValue = 3
             if curValue != preValue:
                 preValue = curValue
                 led("12")
        if fingerUp == [0,1,1,1,1]:
             cv2.putText(frame, "Finger count: Re", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255), 1, cv2.LINE_AA)
             curValue = 4
             if curValue != preValue:
                preValue = curValue
                led("13")
        if fingerUp == [1,1,1,1,1]:
             cv2.putText(frame, "Finger count: 5", (20, 460), cv2.FONT_HERSHEY_COMPLEX, 1, (255,255,255), 1, cv2.LINE_AA)

    cv2.imshow("Frame", frame)
    k = cv2.waitKey(1)
    if k == ord('q'):
        break
video.release()
cv2.destroyAllWindo()
