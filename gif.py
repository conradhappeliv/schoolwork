from images2gif import writeGif
from PIL import Image  #not sure if we need this one

#filename is output file, images is an array
def make_gif(filename, images):
writeGif(filename, images, duration=0.2)
