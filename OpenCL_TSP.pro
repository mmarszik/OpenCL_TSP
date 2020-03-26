TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++14

LIBS += /usr/lib/x86_64-linux-gnu/libOpenCL.so

SOURCES += main.cpp

DISTFILES += \
    OpenCLPi.cl

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
