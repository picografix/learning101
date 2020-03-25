from PIL import Image
from pylab import *
from scipy.ndimage import filters
import imtools

im = array(Image.open('robot2.jpg').convert('L'))
def histeq(im, nbr_bins=256):
    # get image histogram
    imhist, bins = histogram(im.flatten(), nbr_bins, density=True)
    cdf = imhist.cumsum()  # cumulative distribution function
    cdf = 255 * cdf / cdf[-1]  # normalize
    # use linear interpolation of cdf to find new pixel values
    im2 = interp(im.flatten(), bins[:-1], cdf)
    return im2.reshape(im.shape), cdf
im2, cdf = histeq(im)
im3 = 1.0*filters.gaussian_filter(im, 128)
im4 = clip(128 * (1.0 *im / (im3 + 0.1)), 0, 255)



figure(figsize=(16,16))
gray()
subplot(3, 2, 1)
title('original')
imshow(im)

subplot(3, 2, 2)
title('original hist')
hist(im.flatten(), 256, density=True)

subplot(3, 2, 3)
gray()
title('histogram equalized')
imshow(im2)

subplot(3, 2, 4)
title('equalized histogram')
hist(im2.flatten(), 256, density=True)

subplot(3, 2, 5)
gray()
title('quotient')
imshow(uint8(im4))

subplot(3, 2, 6)
title('quotient graph')
hist(im4.flatten(), 256, density=True)

show()