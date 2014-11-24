TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -pthread
QMAKE_LFLAGS += -pthread
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
    lib/getopt_pp.cpp \
    src/index.cpp\
    src/xmlparser.cpp\
    src/processor.cpp\
    src/hashtableindex.cpp\
<<<<<<< HEAD
    src/hashentry.cpp \
=======
    src/avltreeindex.cpp\
>>>>>>> 9f08caf5e3bd5eada4125244bd73ca38ca4d1b43
    src/queryprocessor.cpp \
    src/listindex.cpp \
    src/stlhashtableindex.cpp

HEADERS += src/index.h \
    lib/getopt_pp.h\
    lib/c_threadsafe_porter.h \
    src/xmlparser.h\
    src/processor.h\
    src/Page.h\
    src/hashtableindex.h\
    src/hashentry.h \
    src/queryprocessor.h \
    src/listindex.h \
    src/avltree.h \
    src/stlhashtableindex.h
