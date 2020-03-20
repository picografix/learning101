import cv2
import numpy as np

min_HSV = np.array([0, 58, 30], dtype = "uint8")
max_HSV = np.array([33, 255, 255], dtype = "uint8")

image = cv2.imread("learning4.jpg")
imageHSV = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
skinRegionHSV = cv2.inRange(imageHSV, min_HSV, max_HSV)

skinHSV = cv2.bitwise_and(image, image, mask = skinRegionHSV)

cv2.imshow('Skin_color', skinHSV)

cv2.waitKey(0)
cv2.destroyAllWindows()