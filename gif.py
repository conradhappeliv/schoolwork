#from images2gif import writeGif
#from PIL import Image  #not sure if we need this one
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from skimage import io
import cv2
import os

def build_gif(imgs, show_gif=True, save_gif=True, title='gifs'):
	fig = plt.figure()
	ax = fig.add_subplot(111)
	ax.set_axis_off()

	ims = map(lambda x: (ax.imshow(x), ax.set_title(title)), imgs)
	im_ani = animation.ArtistAnimation(fig, ims, interval=800, repeat_delay=0, blit=False)

	if save_gif:
		im_ani.save('animation.gif', writer='imagemagick')

	if show_gif:
		plt.show()

	return

imgs = []
path = 'C:/Users/alcam/Desktop/giftest'
dirs = os.listdir(path)
for file in dirs:
	img = cv2.imread(file)
	imgs.append(img)
build_gif(imgs)

#filename is output file, images is an array
#def make_gif(filename, images):
#	gif = writeGif(filename, images, duration=0.2)
#	return gif

#imgs = []
#for 
#for myFile in files:
#    image = cv2.imread (myFile)
#    X_data.append (image)

#filename = "my_gif.GIF"
#makegif(filename, X_data)


