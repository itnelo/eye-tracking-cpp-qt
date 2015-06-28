#ifndef CAMERACAPTUREWORKER_H
#define CAMERACAPTUREWORKER_H

#include <QObject>
#include <QMessageBox>
#include <QtCore/QFile>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/legacy/legacy.hpp>

#include <classes/CameraCapture.h>

class CameraCaptureWorker : public QObject
{
    Q_OBJECT

public:
    CameraCaptureWorker();
    ~CameraCaptureWorker();

public slots:
    void process();
    void stop();
    void receiveDataString( QString );
    void receiveImage( QImage );
    void receiveMessage( QString );
    void receivePupilCords( int, int );
    void switchFilterCommand( const int );
    void switchDetectParamAction( const int );
    void saveShotAction();
    void videoSaveAction( bool );
    void setPupilDetectParamsAction( int, int, int, int );

signals:
    void finished();
    void sendDataString( QString );
    void sendImage( QImage );
    void sendMessage( QString );
    void switchFilterAction( const int );
    void sendPupilCords( QString );

private:
    CameraCapture* capture_handler;
};

#endif // CAMERACAPTUREWORKER_H
