TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += / \
    newton_interp.cpp \
    test_newton.cpp \
    compare.cpp \
    lagrange2D.cpp
    lagrange.cpp
    mat.cpp

HEADERS += mat.h

OTHER_FILES += \
    Makefile

