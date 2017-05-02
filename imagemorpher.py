import cv2
import dlib
import matplotlib.pyplot as plt
import numpy as np
from skimage import io

detector = dlib.get_frontal_face_detector()
# get from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
predictor = dlib.shape_predictor('data/shape_predictor_68_face_landmarks.dat')


def find_points(img):
    if len(img.shape) == 3:
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    else:
        gray = img
    rects = detector(img, 0)
    shape = predictor(img, rects[0])

    points = []
    for pt in shape.parts():
        points.append((pt.x, pt.y))

    # Edge points:
    points.append((0, 0))
    points.append((img.shape[1] / 2, 0))
    points.append((img.shape[1] - 1, 0))
    points.append((0, img.shape[0] / 2))
    points.append((0, img.shape[0] - 1))
    points.append((img.shape[1] - 1, img.shape[0] / 2))
    points.append((img.shape[1] / 2, img.shape[0] - 1))
    points.append((img.shape[1] - 1, img.shape[0] - 1))
    return points


def weighted_points(points1, points2, alpha=0.5):
    pts = []
    for pt1, pt2 in zip(points1, points2):
        x = (1 - alpha) * pt1[0] + alpha * pt2[0]
        y = (1 - alpha) * pt1[1] + alpha * pt2[1]
        pts.append((x, y))
    return pts


def find_triangles(shape, points):
    # topleftx toplefty width height
    rect = (0, 0, shape[1], shape[0])
    subdiv = cv2.Subdiv2D(rect)
    [subdiv.insert(pt) for pt in points]
    return subdiv.getTriangleList()


def refine_triangles(triangles_reference, points1, points2, points_morphed):
    def find_point(pointlist, point):
        try:
            return pointlist.index(point)
        except ValueError:
            return -1

    tri1 = [[(int(tri[0]), int(tri[1])), (int(tri[2]), int(tri[3])), (int(tri[4]), int(tri[5]))] for tri in
            triangles_reference]
    tri2 = []
    trim = []
    tri1new = []
    for tri in tri1:
        pt1 = find_point(points1, tri[0])
        pt2 = find_point(points1, tri[1])
        pt3 = find_point(points1, tri[2])
        # append legit triangles, might not need to find triangles for 2 and morph
        tri1new.append((points1[pt1] if pt1 != -1 else tri[0],
                        points1[pt2] if pt2 != -1 else tri[1],
                        points1[pt3] if pt3 != -1 else tri[2]))
        tri2.append((points2[pt1] if pt1 != -1 else tri[0],
                     points2[pt2] if pt2 != -1 else tri[1],
                     points2[pt3] if pt3 != -1 else tri[2]))
        trim.append((points_morphed[pt1] if pt1 != -1 else tri[0],
                     points_morphed[pt2] if pt2 != -1 else tri[1],
                     points_morphed[pt3] if pt3 != -1 else tri[2]))

    triangles1 = np.array([[x[0][0], x[0][1], x[1][0], x[1][1], x[2][0], x[2][1]] for x in tri1new], dtype=np.float32)
    triangles2 = np.array([[x[0][0], x[0][1], x[1][0], x[1][1], x[2][0], x[2][1]] for x in tri2], dtype=np.float32)
    triangles_morphed = np.array([[x[0][0], x[0][1], x[1][0], x[1][1], x[2][0], x[2][1]] for x in trim],
                                 dtype=np.float32)

    return triangles1, triangles2, triangles_morphed


def show_triangles(img, triangles, window_name="triangles"):
    for k, t in enumerate(triangles):
        tri1 = [(t[0], t[1]), (t[2], t[3]), (t[4], t[5])]
        cv2.line(img, tri1[0], tri1[1], (255, 255, 255))
        cv2.line(img, tri1[1], tri1[2], (255, 255, 255))
        cv2.line(img, tri1[2], tri1[0], (255, 255, 255))
        coords = (int((t[0] + t[2] + t[4]) / 3), int((t[1] + t[3] + t[5]) / 3))
        cv2.putText(img, str(k), coords, cv2.FONT_HERSHEY_COMPLEX_SMALL, .7, (1, 1, 1))

    cv2.imshow(window_name, img)

baseline = [380, 380]
def shrink(image1):
    origsize = image1.shape[0:2]
    scale = np.divide(baseline,origsize)
    return cv2.resize(image1,(0,0),fx=scale[1],fy=scale[0])

def morph(image1, image2, alpha, rgb=True):
    # image1 = shrink(image1)
    # print(image1.shape)
    # image2 = shrink(image2)
    # print(image2.shape)
    # plt.imshow(image1)
    if not rgb:
        image1 = cv2.cvtColor(image1, cv2.COLOR_RGB2GRAY)
        image2 = cv2.cvtColor(image2, cv2.COLOR_RGB2GRAY)

    face1 = image1
    face2 = image2

    points1 = find_points(image1)
    points2 = find_points(image2)
    points_morphed = weighted_points(points1, points2, alpha)

    triangles1 = find_triangles(image1.shape, points1)[4:]
    (triangles1, triangles2, triangles_morphed) = refine_triangles(triangles1, points1, points2, points_morphed)

    # need to make sure that image2 and image1 the same shape
    newimg = np.zeros(image2.shape, np.uint8)
    for tri1, tri2, tri_morph in zip(triangles1, triangles2, triangles_morphed):
        # 3 edges, 2 vertices in each edge
        tri1 = tri1.reshape(3, 2)
        tri2 = tri2.reshape(3, 2)
        tri_morph = tri_morph.reshape(3, 2)

        bb1 = cv2.boundingRect(tri1)
        bb2 = cv2.boundingRect(tri2)
        bb_morph = cv2.boundingRect(tri_morph)
        # rect strucure: {topleftx toplefty width height}

        tri1_offset = np.subtract(tri1, np.repeat([[bb1[0], bb1[1]]], 3, axis=0), dtype=np.float32)
        tri2_offset = np.subtract(tri2, np.repeat([[bb2[0], bb2[1]]], 3, axis=0), dtype=np.float32)
        tri_morph_offset = np.subtract(tri_morph, np.repeat([[bb_morph[0], bb_morph[1]]], 3, axis=0), dtype=np.float32)

        trans1 = cv2.getAffineTransform(tri1_offset, tri_morph_offset)
        trans2 = cv2.getAffineTransform(tri2_offset, tri_morph_offset)

        mask = np.zeros((bb_morph[3], bb_morph[2]), np.float32)
        cv2.fillConvexPoly(mask, np.int32(tri_morph_offset), 1)

        if not rgb:
            subimg1 = face1[bb1[1]:bb1[1] + bb1[3], bb1[0]:bb1[0] + bb1[2]]
            subimg2 = face2[bb2[1]:bb2[1] + bb2[3], bb2[0]:bb2[0] + bb2[2]]

            warped1 = cv2.warpAffine(subimg1, trans1, (bb_morph[2], bb_morph[3]), None, flags=cv2.INTER_LINEAR, borderMode=cv2.BORDER_REFLECT_101)
            warped2 = cv2.warpAffine(subimg2, trans2, (bb_morph[2], bb_morph[3]), None, flags=cv2.INTER_LINEAR, borderMode=cv2.BORDER_REFLECT_101)

            alpha_blend = (1 - alpha) * warped1 + alpha * warped2
            newimg_sq = newimg[bb_morph[1]:bb_morph[1] + bb_morph[3], bb_morph[0]:bb_morph[0] + bb_morph[2]]
            mask[newimg_sq != 0] = 0
            newimg[bb_morph[1]:bb_morph[1] + bb_morph[3], bb_morph[0]:bb_morph[0] + bb_morph[2]] = newimg_sq + (alpha_blend * mask)[:newimg_sq.shape[0], :newimg_sq.shape[1]]
        else:
            subimg1 = face1[bb1[1]:bb1[1] + bb1[3], bb1[0]:bb1[0] + bb1[2], :]
            subimg2 = face2[bb2[1]:bb2[1] + bb2[3], bb2[0]:bb2[0] + bb2[2], :]

            warped1 = cv2.warpAffine(subimg1, trans1, (bb_morph[2], bb_morph[3]), None, flags=cv2.INTER_LINEAR, borderMode=cv2.BORDER_REFLECT_101)
            warped2 = cv2.warpAffine(subimg2, trans2, (bb_morph[2], bb_morph[3]), None, flags=cv2.INTER_LINEAR, borderMode=cv2.BORDER_REFLECT_101)

            alpha_blend = (1 - alpha) * warped1 + alpha * warped2
            newimg_sq = newimg[bb_morph[1]:bb_morph[1] + bb_morph[3], bb_morph[0]:bb_morph[0] + bb_morph[2], :]
            mask[newimg_sq[:, :, 0] != 0] = 0
            for i in range(3):
                alpha_blend[:, :, i] *= mask
            newimg[bb_morph[1]:bb_morph[1] + bb_morph[3], bb_morph[0]:bb_morph[0] + bb_morph[2]] = newimg_sq + alpha_blend[:newimg_sq.shape[0], :newimg_sq.shape[1]]

    newimg = shrink(newimg)
    return newimg


if __name__ == "__main__":
    face1 = io.imread('data/face1.jpg')
    face2 = io.imread('data/face2.jpg')
    face1gray = cv2.cvtColor(face1, cv2.COLOR_RGB2GRAY)
    face2gray = cv2.cvtColor(face2, cv2.COLOR_RGB2GRAY)

    newimg = morph(face1, face2, .5)

    plt.figure()
    plt.imshow(newimg)
    plt.show()
