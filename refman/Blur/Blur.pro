TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /opt/opencv4.0/install/include/opencv4

LIBS += $$system(libs_opencv_files)

SOURCES += main.cpp
