from PIL import Image
from pylab import *
from scipy.ndimage import filters

#this is for just applying gaussian blur


"""image = array(Image.open('robot2.jpg').convert('L'))

figure(figsize=(10,10))    #defines  a rectangle/square of size 10
gray()                     # don’t use color
subplot(2, 2, 1)           #uses pylab library to draw image and marks its position accordingly
title('robot')             #gives title to figure
imshow(image)

for i in range(3):
    subplot(2, 2, i+2)
    title('sigma='+str(2*i))
    image1 = filters.gaussian_filter(image, 2*i)
    imshow(image1)

show()"""

#showing image contours.....

image = array(Image.open('robot2.jpg').convert('L'))

figure(figsize=(10,10))    #defines  a rectangle/square of size 10
gray()                     # don’t use color
subplot(2, 2, 1)           #uses pylab library to draw image and marks its position accordingly
title('robot')             #gives title to figure
imshow(image)

for i in range(3):
    subplot(2, 2, i+2)
    title('sigma='+str(2*i))
    image1 = filters.gaussian_filter(image, 2*i)
    #imshow(image1)
    imagex = zeros(image1.shape)
    filters.sobel(image1, 1, imagex)
    imagey = zeros(image1.shape)
    filters.sobel(image1, 0, imagey)
    imagexy = sqrt(imagex ** 2 + imagey ** 2)
    imshow(imagexy)

show()
# as you can see as sigma value increases contours are getting more inappropriate (wider) they cant provide with good smmooth contours......