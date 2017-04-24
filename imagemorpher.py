import cv2
import dlib
from skimage import io

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor('data/shape_predictor_68_face_landmarks.dat')  # get from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
win = dlib.image_window()

face = io.imread('./data/face1.jpg')

gray = cv2.cvtColor(face, cv2.COLOR_BGR2GRAY)
rects = detector(gray, 0)
for k, d in enumerate(rects):
    win.clear_overlay()
    win.set_image(face)
    shape = predictor(gray, d)
    win.add_overlay(shape)
win.add_overlay(rects)
dlib.hit_enter_to_continue()

