import numpy as np
import imageio
import imagemorpher
from skimage import io
from multiprocessing import Pool


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


def do_morph(args):
    return imagemorpher.morph(args[0], args[1], args[2], args[3])

def make_gif(image1, image2):
    image1 = np.array(image1)
    image2 = np.array(image2)

    images = []
    num = 8
    args = zip([image1]*num, [image2]*num, list(np.linspace(0, 1, num)), [False]*num)
    pool = Pool(8)  # 8 procs
    images = pool.map(do_morph, args)
    # for alpha in np.linspace(0, 1, num=8):
    #     images.append(imagemorpher.morph(image1, image2, alpha, rgb=False))

    return images


if __name__ == "__main__":
    face1 = io.imread('data/face3.jpg')
    face2 = io.imread('data/face1.jpg')

    images = make_gif(face1, face2)

    save_gif(images, "data/test.gif")
