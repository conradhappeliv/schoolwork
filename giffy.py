import numpy as np
import cv2
import imageio
import imagemorpher
from skimage import io


def save_gif(images, filename, reverse=True):
    dly_amt = .1
    durations = []
    durations.append(1)
    durations += [dly_amt]*(len(images)-2)
    durations.append(1)
    if reverse:
        for img in reversed(images[1:-1]):
            images.append(img)
            durations.append(dly_amt)
    imageio.mimsave(filename, images, subrectangles=True, palettesize=32, duration=durations, loop=0)


def make_gif(image1, image2):
    image1 = np.array(image1)
    image2 = np.array(image2)

    image1gray = cv2.cvtColor(image1, cv2.COLOR_RGB2GRAY)
    image2gray = cv2.cvtColor(image2, cv2.COLOR_RGB2GRAY)

    np.linspace(1, 0)
    images = []
    for alpha in np.linspace(0, 1, num=8):
        images.append(imagemorpher.morph(image1gray, image2gray, alpha))

    return images


if __name__ == "__main__":
    face1 = io.imread('data/face1.jpg')
    face2 = io.imread('data/face3.jpg')

    images = make_gif(face1, face2)

    save_gif(images, "data/test.gif")
