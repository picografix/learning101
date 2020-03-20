import cv2
import numpy as np

min_HSV = np.array([0, 58, 30], dtype = "uint8")
max_HSV = np.array([33, 255, 255], dtype = "uint8")

image = cv2.imread("learning4.jpg")
imageHSV = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
skinRegionHSV = cv2.inRange(imageHSV, min_HSV, max_HSV)
skinHSV = cv2.bitwise_and(image, image, mask = skinRegionHSV)

img_gray = cv2.cvtColor(skinHSV, cv2.COLOR_BGR2GRAY)

ret, thresh = cv2.threshold(img_gray,20,255,0)

contours,heirarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

cv2.drawContours(skinHSV, contours, -1, (225,0,0), 2)
cv2.imshow('Skin_color', skinHSV)

cv2.waitKey(0)
cv2.destroyAllWindows()