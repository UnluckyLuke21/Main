import cv2
import numpy as np
import os

print(cv2.__version__)

# Set the platform to wayland


cap = cv2.VideoCapture(0)

# Load the pre-trained model and configuration file
#net = cv2.dnn.readNetFromCaffe('deploy.prototxt', 'res10_300x300_ssd_iter_140000.caffemodel')

# Load the Input Image

# Open Webcam:
#cap = cv2.VideoCapture(0)

# Check if the Webcam is opened correctly
if not cap.isOpened():
    print("Error: Could not open Webcam.")
    exit()

while True:
    # Capture Frame by Frame
    ret, frame = cap.read() # If cap.read() works coretly ret is True

    if not ret:
        print("Error: Can not receive frame. Exiting...")
        break

    cv2.imshow("Webcam", frame)

    # Exit Stream:
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# Prepare the image for object recognition
#blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 1.0, (300, 300), (104.0, 177.0, 123.0))