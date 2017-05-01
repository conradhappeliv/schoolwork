import cv2
import dlib
from skimage import io
import matplotlib.pyplot as plt
import numpy as np


face1 = io.imread('data/face1.jpg') #io reads as RGB
face2 = io.imread('data/face2.jpg')
face1gray = cv2.cvtColor(face1, cv2.COLOR_RGB2GRAY)
face2gray = cv2.cvtColor(face2, cv2.COLOR_RGB2GRAY)


def find_points(img,predfile = 'data/shape_predictor_68_face_landmarks.dat'):
    detector = dlib.get_frontal_face_detector()
    predictor = dlib.shape_predictor(predfile)  # get from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
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


def weighted_points(points1, points2, alpha=0.5):
    pts = []
    for pt1, pt2 in zip(points1,points2):
        x = (1-alpha)*pt1[0] + alpha*pt2[0]
        y = (1-alpha)*pt1[1] + alpha*pt2[1]
        pts.append((x,y))
    return pts

def find_triangles(shape, points):
    #topleftx toplefty width height
    rect = (0, 0, shape[1], shape[0])
    subdiv = cv2.Subdiv2D(rect)
    [subdiv.insert(pt) for pt in points]
    return subdiv.getTriangleList()


def show_triangles(img, triangles, window_name="triangles"):
    for k, t in enumerate(triangles):
        tri1 = [(t[0], t[1]), (t[2], t[3]), (t[4], t[5])]
        cv2.line(img, tri1[0], tri1[1], (255, 255, 255))
        cv2.line(img, tri1[1], tri1[2], (255, 255, 255))
        cv2.line(img, tri1[2], tri1[0], (255, 255, 255))
        coords = (int((t[0]+t[2]+t[4])/3), int((t[1]+t[3]+t[5])/3))
        cv2.putText(img, str(k), coords, cv2.FONT_HERSHEY_COMPLEX_SMALL, .7, (1,1,1))

    cv2.imshow(window_name, img)

points1 = find_points(face1)
points2 = find_points(face2)
points_morphed = weighted_points(points1,points2)
# points_morphed = [((pt1[0]+pt2[0])/2, (pt1[1]+pt2[1])/2) for pt1, pt2 in zip(points1, points2)]

# plt.figure()
# plt.imshow(face1)
# for pt in points1:
#     plt.plot(pt[0], pt[1], 'o')
#
# plt.figure()
# plt.imshow(face2)
# for pt in points2:
#     plt.plot(pt[0], pt[1], 'o')
#
# plt.show()

triangles1 = find_triangles(face1.shape, points1)
triangles2 = find_triangles(face2.shape, points2)
triangles_morphed = find_triangles(face2.shape, points_morphed)



tri1 = [[(int(tri[0]),int(tri[1])),(int(tri[2]),int(tri[3])),(int(tri[4]),int(tri[5]))] for tri in triangles1]
tri2 = []
trim = []
tri1new = []
for tri in tri1:
    ind = 1
    try:
        pt1 = points1.index(tri[0])
        pt2 = points1.index(tri[1])
        pt3 = points1.index(tri[2])
        ind = 1
    except ValueError:
        #find triangles sometimes uses points way beyond edge of picture
        ind = -1
    if ind != -1:
        #append legit triangles, might not need to find triangles for 2 and morph
        tri1new.append((points1[pt1],points1[pt2],points1[pt3]))
        tri2.append((points2[pt1],points2[pt2],points2[pt3]))
        trim.append((points_morphed[pt1],points_morphed[pt2],points_morphed[pt3]))



#comment this section to use the original morphing triangles
triangles1 = np.array([[x[0][0],x[0][1],x[1][0],x[1][1],x[2][0],x[2][1]] for x in tri1new],dtype=np.float32)
triangles2 = np.array([[x[0][0],x[0][1],x[1][0],x[1][1],x[2][0],x[2][1]] for x in tri2],dtype=np.float32)
triangles_morphed = np.array([[x[0][0],x[0][1],x[1][0],x[1][1],x[2][0],x[2][1]] for x in trim],dtype=np.float32)

# Uncomment this section to show triangle numbers
# show_triangles(face1, triangles1, "face1")
# show_triangles(face2, triangles2, "face2")
# #cv2.imwrite("./face1.out.png", face1)
# #cv2.imwrite("./face2.out.png", face2)
# cv2.waitKey(0)
# exit(0)
# print(triangles1.shape)

# See: https://github.com/spmallick/learnopencv/blob/master/FaceMorph/faceMorph.py
newimg = np.zeros(face2gray.shape, np.uint8)
alpha = 0.5
for tri1, tri2, tri_morph in zip(triangles1, triangles2, triangles_morphed):
    #3 edges, 2 vertices in each edge
    tri1 = tri1.reshape(3,2)
    tri2 = tri2.reshape(3,2)
    tri_morph = tri_morph.reshape(3,2)

    bb1 = cv2.boundingRect(tri1)
    bb2 = cv2.boundingRect(tri2)
    bb_morph = cv2.boundingRect(tri_morph)
    #rect strucure: {topleftx toplefty width height}

    tri1_offset = np.subtract(tri1,np.repeat([[bb1[0],bb1[1]]],3,axis=0),dtype=np.float32)
    tri2_offset = np.subtract(tri1,np.repeat([[bb2[0],bb2[1]]],3,axis=0),dtype=np.float32)
    tri_morph_offset = np.subtract(tri1,np.repeat([[bb_morph[0],bb_morph[1]]],3,axis=0),dtype=np.float32)

    trans1 = cv2.getAffineTransform(tri1_offset, tri_morph_offset)
    trans2 = cv2.getAffineTransform(tri2_offset, tri_morph_offset)

    mask = np.zeros((bb_morph[3], bb_morph[2]), np.float32)
    cv2.fillConvexPoly(mask, np.int32(tri_morph_offset), 1.0)

    subimg1 = face1gray[bb1[1]:bb1[1]+bb1[3], bb1[0]:bb1[0]+bb1[2]]
    subimg2 = face2gray[bb2[1]:bb2[1]+bb2[3], bb2[0]:bb2[0]+bb2[2]]

    # SOMETHING IS WRONG WITH THIS SECTION (PROBABLY)
    warped1 = cv2.warpAffine(subimg1, trans1, (bb_morph[2], bb_morph[3]))
    warped2 = cv2.warpAffine(subimg2, trans2, (bb_morph[2], bb_morph[3]))
    # plt.subplot(2,2,1)
    # plt.imshow(warped1*mask, cmap='gray')
    # plt.subplot(2, 2, 2)
    # plt.imshow(warped2*mask, cmap='gray')
    # plt.subplot(2, 2, 3)
    # plt.imshow(subimg1, cmap='gray')
    # plt.subplot(2, 2, 4)
    # plt.imshow(subimg2, cmap='gray')
    # plt.show()

    alpha_blend = (1-alpha)*warped1 + alpha*warped2
    newimg_sq = newimg[bb_morph[1]:bb_morph[1]+bb_morph[3], bb_morph[0]:bb_morph[0]+bb_morph[2]]
    newimg[bb_morph[1]:bb_morph[1]+bb_morph[3], bb_morph[0]:bb_morph[0]+bb_morph[2]] = newimg_sq + (alpha_blend*mask)[:newimg_sq.shape[0], :newimg_sq.shape[1]]

plt.figure()
plt.imshow(newimg, cmap='gray')
plt.show()
