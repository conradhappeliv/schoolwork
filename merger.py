import cv2
import numpy as np

def alpha_blend(first,second,alpha):
    #assumes first and second image are same size
    return first*(1 - alpha) + (alpha)*second
