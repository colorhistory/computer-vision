TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /opt/opencv/install/include/opencv4

LIBS += $$system(libs_opencv_files)


SOURCES += main.cpp
