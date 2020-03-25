from pylab import *

im = zeros((500, 500))
im[100:400, 100:400] = 140
im[200:300, 200:300]=255
figure()
gray()
imshow(im)
show()
