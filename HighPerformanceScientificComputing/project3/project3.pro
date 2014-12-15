TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += / \
    newton_interp.cpp \
    test_newton.cpp \
    compare.cpp \
    lagrange2D.cpp \
    runge_regular.cpp \
    runge_chebyshev.cpp
    lagrange.cpp
    mat.cpp

HEADERS += mat.h

OTHER_FILES += \
    Makefile

