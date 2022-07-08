import cv2

print(cv2.__version__)

image = cv2.imread("./images/abraham.jpg")

cv2.imshow('frame', image)