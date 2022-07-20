import cv2
import matplotlib
from matplotlib import pyplot as plt
import numpy as np


# Simple Function to show a picture:
def imshow(title= "", image = None):
    
    cv2.imshow(title, image)

# Start:
image = cv2.imread("example.jpg")

# Bild zu Graustufenbild machen:
imageGray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

B, G, R = cv2.split(image)
#print(B.shape)
#print(G.shape)
#print(R.shape)

# Create 2 dimensional Array of zeroes in size of the Image
zeros = np.zeros(image.shape[:2], dtype = "uint8")

# Show every Color Shape of the Image
imshow("Red", cv2.merge([zeros, zeros, R]))
imshow("Green", cv2.merge([zeros, G, zeros]))
imshow("Blue", cv2.merge([B, zeros, zeros]))

# Show every Channel of the Image:
#imshow("Blue Channel", B)
#imshow("Red Channel", R)
#imshow("Green Channel", G)

#imshow("Castara, Tobago", imageGray)

# Play with the Colors:
merged = cv2.merge([B, G, R])
imshow("merged", merged)

# Blue Boost:
merged2 = cv2.merge([B + 100, G, R])
imshow("Merged Blue Boost", merged2)

# Green Boost:
merged3 = cv2.merge([B, G + 100, R])
imshow("Merged Green Boost", merged3)

# Red Boost:
merged4 = cv2.merge([B, G, R + 100])
imshow("Merged Red Boost", merged4)

hsvImage = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
imshow("HSV Image", hsvImage)

imshow("Hue", hsvImage[:, :, 0])
imshow("Saturation", hsvImage[:, :, 1])
imshow("Value", hsvImage[:, :, 2])

# Loop um das Bild dauerhaft zu zeiegn bis q gedrückt wird:
while True:
    if cv2.waitKey(0):
        break