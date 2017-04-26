import cv2
import dlib
from skimage import io
import matplotlib.pyplot as plt

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor('data/shape_predictor_68_face_landmarks.dat')  # get from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2

face = io.imread('./data/face1.jpg')

gray = cv2.cvtColor(face, cv2.COLOR_BGR2GRAY)
rects = detector(gray, 0)
plt.imshow(face)
for k, d in enumerate(rects):
    shape = predictor(gray, d)
    for point in shape.parts():
        plt.plot(point.x, point.y, 'o')

plt.show()