import numpy as np
import cv2
import imageio
import imagemorpher
from skimage import io
import matplotlib.pyplot as plt

def make_gif(images,filename):
    # with imageio.get_writer(filename,mode='I') as writer:
        # for image in images:
            # writer.append_data(image)
    imageio.mimsave(filename,images)

if __name__ == "__main__":
    face1 = io.imread('data/face1.jpg')
    face2 = io.imread('data/face2.jpg')
    face1gray = cv2.cvtColor(face1, cv2.COLOR_RGB2GRAY)
    face2gray = cv2.cvtColor(face2, cv2.COLOR_RGB2GRAY)

    plt.imshow(imagemorpher.morph(face1gray,face2gray,1))

    np.linspace(1,0)
    images = []
    for alpha in np.linspace(0,1,num=60):
        images.append(imagemorpher.morph(face1gray,face2gray,alpha))
    # for delay in np.linspace(0,1,num=10):
    #     images.append(face2gray)
    for alpha in np.linspace(1,0,num=60):
        images.append(imagemorpher.morph(face1gray,face2gray,alpha))
    # for delay in np.linspace(0,1,num=10):
        # images.append(face1gray)
    make_gif(images,"data/test.gif")
