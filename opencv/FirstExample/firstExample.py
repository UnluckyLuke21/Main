import numpy

import cv2

from matplotlib import pyplot as plt

print("Starting opencv ", cv2.__version__)

image = cv2.imread('./images/castara.jpeg')
plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
plt.show()