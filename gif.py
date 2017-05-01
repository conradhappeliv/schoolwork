from images2gif import writeGif
#from PIL import Image  #not sure if we need this one
import numpy as np
from skimage import io
import cv2
import glob

#filename is output file, images is an array
def make_gif(filename, images):
	gif = writeGif(filename, images, duration=0.2)
	return gif

X_data = []
files = glob.glob ("C:/Users/alcam/Desktop/giftest/*.PNG")
for myFile in files:
    image = cv2.imread (myFile)
    X_data.append (image)

filename = "my_gif.GIF"
makegif(filename, X_data)