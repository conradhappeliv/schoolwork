import cv2
import dlib
from skimage import io
import matplotlib.pyplot as plt
import numpy as np

detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor('data/shape_predictor_68_face_landmarks.dat')  # get from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2

face1 = io.imread('data/face1.jpg')
face2 = io.imread('data/face2.jpg')
face1gray = cv2.cvtColor(face1, cv2.COLOR_BGR2GRAY)
face2gray = cv2.cvtColor(face2, cv2.COLOR_BGR2GRAY)


def find_points(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)
    shape = predictor(gray, rects[0])

    points = []
    for pt in shape.parts():
        points.append((pt.x, pt.y))

    # Edge points:
    points.append((0, 0))
    points.append((img.shape[1]/2, 0))
    points.append((img.shape[1] - 1, 0))
    points.append((0, img.shape[0]/2))
    points.append((0, img.shape[0] - 1))
    points.append((img.shape[1] - 1, img.shape[0]/2))
    points.append((img.shape[1]/2, img.shape[0] - 1))
    points.append((img.shape[1] - 1, img.shape[0] - 1))
    return points


def find_triangles(y_len, x_len, points):
    rect = (0, 0, x_len, y_len)
    subdiv = cv2.Subdiv2D(rect)
    [subdiv.insert(pt) for pt in points]
    return subdiv.getTriangleList()


def show_triangles(img, triangles):
    for t in triangles:
        tri1 = [(t[0], t[1]), (t[2], t[3]), (t[4], t[5])]
        cv2.line(face1, tri1[0], tri1[1], (255, 255, 255))
        cv2.line(face1, tri1[1], tri1[2], (255, 255, 255))
        cv2.line(face1, tri1[2], tri1[0], (255, 255, 255))

    cv2.imshow("window", img)
    cv2.waitKey(0)

points1 = find_points(face1)
points2 = find_points(face2)
points_morphed = [((pt1[0]+pt2[0])/2, (pt1[1]+pt2[1])/2) for pt1, pt2 in zip(points1, points2)]

# plt.figure()
# plt.imshow(face1)
# for pt in points1:
#     plt.plot(pt[0], pt[1], 'o')
#
# plt.figure()
# plt.imshow(face2)
# for pt in points2:
#     plt.plot(pt[0], pt[1], 'o')

triangles1 = find_triangles(face1.shape[0], face1.shape[1], points1)[4:]
triangles_morphed = find_triangles(face2.shape[0], face2.shape[1], points2)[4:]
triangles2 = find_triangles(face2.shape[0], face2.shape[1], points2)[4:]

# See: https://github.com/spmallick/learnopencv/blob/master/FaceMorph/faceMorph.py
newimg = np.zeros(face2gray.shape, np.uint8)
for tri1, tri2, tri_morph in zip(triangles1, triangles2, triangles_morphed):
    tri1 = np.array([(tri1[0], tri1[1]), (tri1[2], tri1[3]), (tri1[4], tri1[5])])
    tri2 = np.array([(tri2[0], tri2[1]), (tri2[2], tri2[3]), (tri2[4], tri2[5])])
    tri_morph = np.array([(tri_morph[0], tri_morph[1]), (tri_morph[2], tri_morph[3]), (tri_morph[4], tri_morph[5])])

    bb1 = cv2.boundingRect(tri1)
    bb2 = cv2.boundingRect(tri2)
    bb_morph = cv2.boundingRect(tri_morph)

    tri1_offset = np.array([(tri1[0][0]-bb1[0], tri1[0][1]-bb1[1]), (tri1[1][0]-bb1[0], tri1[1][1]-bb1[1]), (tri1[2][0]-bb1[0], tri1[2][1]-bb1[1])], np.float32)
    tri2_offset = np.array([(tri2[0][0]-bb2[0], tri2[0][1]-bb2[1]), (tri2[1][0]-bb2[0], tri2[1][1]-bb2[1]), (tri2[2][0]-bb2[0], tri2[2][1]-bb2[1])], np.float32)
    tri_morph_offset = np.array([(tri_morph[0][0] - bb_morph[0], tri_morph[0][1] - bb_morph[1]), (tri_morph[1][0] - bb_morph[0], tri_morph[1][1] - bb_morph[1]), (tri_morph[2][0] - bb_morph[0], tri_morph[2][1] - bb_morph[1])], np.float32)

    trans1 = cv2.getAffineTransform(tri1_offset, tri_morph_offset)
    trans2 = cv2.getAffineTransform(tri2_offset, tri_morph_offset)

    mask = np.zeros((bb_morph[3], bb_morph[2]), np.float32)
    cv2.fillConvexPoly(mask, np.int32(tri_morph_offset), 1.0)

    subimg1 = face1gray[bb1[1]:bb1[1]+bb1[3], bb1[0]:bb1[0]+bb1[2]]
    subimg2 = face2gray[bb2[1]:bb2[1]+bb2[3], bb2[0]:bb2[0]+bb2[2]]

    warped1 = cv2.warpAffine(subimg1, trans1, (bb_morph[2], bb_morph[3]))
    warped2 = cv2.warpAffine(subimg2, trans2, (bb_morph[2], bb_morph[3]))

    newimg_sq = newimg[bb_morph[1]:bb_morph[1]+bb_morph[3], bb_morph[0]:bb_morph[0]+bb_morph[2]]
    newimg[bb_morph[1]:bb_morph[1]+bb_morph[3], bb_morph[0]:bb_morph[0]+bb_morph[2]] = newimg_sq + ((warped1*.5+warped2*.5)*mask)[:newimg_sq.shape[0], :newimg_sq.shape[1]]


plt.figure()
plt.imshow(face1)

plt.figure()
plt.imshow(newimg, cmap='gray')
plt.show()
