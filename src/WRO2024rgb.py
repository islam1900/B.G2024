import cv2
import numpy as np
from gpiozero import LED

raspir = LED (16)
raspil = LED (20)
area=0
red_area=0
green_area=0
position=0
color='n'
turn='f'


redlower = np.array([0, 0, 80])
redupper = np.array([70, 69, 165])

greenlower = np.array([39, 70, 19])
greenupper = np.array([100, 120, 50])


webcam = cv2.VideoCapture(0)

def detect(mask, min_area, G, R):
    mask_contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    pos=0
    area=0
    if len(mask_contours) !=0:
        largest_contour = max(mask_contours, key=cv2.contourArea)
        if cv2.contourArea(largest_contour) > min_area:
            x, y, w, h = cv2.boundingRect(largest_contour)
            cv2.rectangle(bgr, (x, y), (x + w, y + h), (0, G, R), 2)
            pos=((x+(x+w))/2)/1920*100
            area= cv2.contourArea(largest_contour)
    return pos, area

while True:
    _, bgr = webcam.read()
    
    bgr = bgr[0:480, 0:1920]
    
    bgr = cv2.rotate(bgr, cv2.ROTATE_180)
    mask=cv2.inRange(bgr, redlower, redupper) 
    red_pos, red_area = detect(mask, 5000, 0, 255)            #1700 is the area of the smallest red detection distance
    mask=cv2.inRange(bgr, greenlower, greenupper) 
    green_pos, green_area = detect(mask, 5000, 255, 0)  
    cv2.imshow("window", bgr)
    cv2.rectangle(bgr, (959,239), (961, 241), (255,0 , 0), 2)

    
    
    if green_area>red_area :
        position=green_pos
        color='g'
    elif red_area>green_area :
        position=red_pos
        color='r'
    else :
        position=0
        color='n'
        
    if color=='r':
        if position > 30 :
            turn = 'r'
        else :
            turn = 'f'
    
    elif color=='g':
        if position <70 :
            turn='l'
        else :
            turn = 'f'
    else :
        turn = 'f'
    if turn =='r':
        raspir.on()
        raspil.off()
    elif turn =='l':
        raspil.on()
        raspir.off()
    else:
        raspir.off()
        raspil.off()
    
    print("R: ", int(red_pos), "   G:", int(green_pos), "    turn: ", turn)   
    key =cv2.waitKey(1)