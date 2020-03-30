import cv2

method = cv2.TM_SQDIFF_NORMED

small_image = cv2.imread('robot2_armorplate.jpg')
large_image = cv2.imread('robot2.jpg')

result = cv2.matchTemplate(small_image, large_image, method)

mn,_,mnLoc,_ = cv2.minMaxLoc(result)

MPx,MPy = mnLoc

trows,tcols = small_image.shape[:2]


cv2.rectangle(large_image, (MPx,MPy),(MPx+tcols,MPy+trows),(0,255,0),2)

cv2.imshow('output',large_image)

cv2.waitKey(0)