#-------------------------------------------------
#
# Project created by QtCreator 2013-03-02T09:26:33
#
#-------------------------------------------------

# OpenCV
INCLUDEPATH += c:\opencv\RELEASE\install\include

LIBS += C:\opencv\RELEASE\bin\libopencv_core249.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_highgui249.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_imgproc249.dll
LIBS += C:\opencv\RELEASE\bin\libopencv_objdetect249.dll

#LIBS += C:\opencv\RELEASE\bin\libopencv_contrib249.dll
#LIBS += C:\opencv\RELEASE\bin\libopencv_calib3d249.dll

#file:///C:/opencv/RELEASE/bin/libopencv_features2d249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_flann249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_gpu249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_legacy249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_ml249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_nonfree249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_ocl249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_photo249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_stitching249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_superres249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_video249.dll
#file:///C:/opencv/RELEASE/bin/libopencv_videostab249.dll


# Camera API
LIBS += C:\Users\nelo\git\univer\ps3-libs\PSEye_API\bin\CLEyeMulticam.dll

QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ps3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classes/CameraCaptureWorker.cpp \
    classes/CameraManager.cpp \
    classes/CameraCapture.cpp \
    classes/CameraDetector.cpp \
    capturedialog.cpp \
    classes/QImageLabel.cpp \
    classes/QImageLabelPoint.cpp \
    classes/EyeFeaturesDetector.cpp \
    classes/EyeFeaturesDetectorAlgorithm1.cpp \
    classes/EyeFeaturesDetectorAlgorithm2.cpp \
    classes/EyeFeaturesDetectorAlgorithm.cpp \
    classes/QImageListView.cpp

HEADERS  += mainwindow.h \
    classes/CameraManager.h \
    classes/CameraCaptureWorker.h \
    classes/CameraCapture.h \
    classes/CameraDetector.h \
    capturedialog.h \
    classes/QImageLabel.h \
    classes/QImageLabelPoint.h \
    classes/EyeFeaturesDetector.h \
    classes/EyeFeaturesDetectorAlgorithm1.h \
    classes/EyeFeaturesDetectorAlgorithm2.h \
    classes/EyeFeaturesDetectorAlgorithm.h \
    classes/QImageListView.h

FORMS    += mainwindow.ui \
    capturedialog.ui

RESOURCES += \
    resources.qrc

CONFIG += c++11
CONFIG += static
CONFIG += staticlib
DEFINES += STATIC

QMAKE_LFLAGS += -static -static-libgcc
