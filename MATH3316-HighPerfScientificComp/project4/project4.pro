TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    composite_int.cpp \
    test_int.cpp \
    composite_Gauss2.cpp \
    mat.cpp \
    adaptive_int.cpp \
    test_adapt.cpp \
    carbon.cpp \
    application.cpp \
    test_carbon.cpp \
    steffensen.cpp

HEADERS += \
    mat.h

OTHER_FILES += \
    Makefile
