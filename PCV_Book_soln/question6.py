from PIL import Image
from pylab import *
from scipy.ndimage import measurements, morphology

im = array(Image.open('shapes_and_colors.png').convert('L'))
im = 1*(im<128)
labels, nbr_objects = measurements.label(im)
figure()
gray()
imshow(labels)
show()
figure()
gray()
hist(labels.flatten())
axis([0, 50, 0, 1000])
show()