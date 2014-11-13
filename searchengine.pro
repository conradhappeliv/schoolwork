TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -lncurses
INCLUDEPATH +=/usr/include/libxml2 \
    /usr/include/glibmm-2.4 \
    /usr/lib/x86_64-linux-gnu/glibmm-2.4/include \
    /usr/include/glib-2.0 \
    /usr/lib/x86_64-linux-gnu/glib-2.0/include \
    /usr/include/sigc++-2.0 \
    /usr/lib/x86_64-linux-gnu/sigc++-2.0/include \
    /usr/include/libxml++-2.6 \
    /usr/lib/libxml++-2.6/include
LIBS += -lxml++-2.6 \
    -lxml2 \
    -lglibmm-2.4 \
    -lgobject-2.0 \
    -lglib-2.0 \
    -lsigc-2.0

SOURCES += src/main.cpp \
    src/HashTable.cpp \
    src/xmlparser.cpp \
    lib/getopt_pp.cpp

HEADERS += src/index.h \
    src/HashTable.h \
    src/saxparse.h \
    src/xmlparser.h \
    lib/getopt_pp.h
