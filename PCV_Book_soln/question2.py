from PIL import Image
from pylab import *
from scipy.ndimage import filters

image = array(Image.open('robot2.jpg').convert('L'))
image1 = zeros(image.shape)
image1 = filters.gaussian_filter(image, 1)#blurring the image
image2 = 1.0*image1-image
image3 = image - 1.0*image2

figure(figsize=(16, 16))
gray()
subplot(2, 2, 1)
title('original')
imshow(uint8(image))

subplot(2, 2, 2)
title('Blur image')
imshow(uint8(image1))

subplot(2, 2, 3)
title('Unsharp')
imshow(uint8(image2))

subplot(2, 2, 4)
title('Sharpening done')
imshow(uint8(image3))

show()
"""for color image just 7 with 
for i in range(3):
    image1[:, :, i] = filters.gaussian_filter(image[:, :, i], 4)"""