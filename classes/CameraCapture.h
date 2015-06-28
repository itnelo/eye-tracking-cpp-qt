#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H

#include <QObject>
#include <QMessageBox>
#include <QImage>
#include <QtCore/QDebug>

#include <opencv2/video/video.hpp>

#include "classes/CameraDetector.h"
#include "classes/CLEyeMulticam.h"

class CameraCapture : public QObject
{
    Q_OBJECT

public:
    CameraCapture();
    ~CameraCapture();

    // Цикл захвата изображения с камеры, работает в отдельном потоке.
    void captureLoop();

    void videoSave( bool set_status );

    IplImage* getImage();

signals:
    void sendString( QString );
    void sendImage( QImage );
    void sendMessage( QString );

private:
    IplImage* useFilter();

private:
    IplImage* frame;
    IplImage* filtered_frame;

public:
    CameraDetector* camera_detector;
    CvVideoWriter*  video_writer;

    bool do_capture;
    bool do_save_capture;
    int active_filter;
};

#endif // CAMERACAPTURE_H
