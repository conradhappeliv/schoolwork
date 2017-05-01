import imageio
import imagemorpher.py

def make_gif(images,filename):
    with imageio.get_writer(filename,mode='I') as writer:
        for image in images:
            writer.append_data(image)

face1 = io.imread('data/face1.jpg')
face2 = io.imread('data/face2.jpg')
face1gray = cv2.cvtColor(face1, cv2.COLOR_RGB2GRAY)
face2gray = cv2.cvtColor(face2, cv2.COLOR_RGB2GRAY)

for alpha in xrange()
