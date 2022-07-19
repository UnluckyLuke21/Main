import cv2

from matplotlib import pyplot as plt

# Simple Function to show a picture:
def imshow(title= "", image = None):
    
    cv2.imshow(title, image)

    while True:

        if cv2.waitKey(1) == ord('q'):
            break

# Reading the Image:
image = cv2.imread('example.jpeg')

imshow("frame", image)

print(image.shape)

cv2.destroyAllWindows()