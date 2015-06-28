#include "CameraCaptureWorker.h"

CameraCaptureWorker::CameraCaptureWorker(){}

CameraCaptureWorker::~CameraCaptureWorker()
{
    if( capture_handler != NULL )
        delete capture_handler;
}

void CameraCaptureWorker::process()
{
    capture_handler = new CameraCapture;

    connect( capture_handler, SIGNAL( sendString( QString ) ), this, SLOT( receiveDataString( QString ) ) );
    connect( capture_handler, SIGNAL( sendImage( QImage ) ), this, SLOT( receiveImage( QImage ) ) );
    connect( capture_handler, SIGNAL( sendMessage( QString ) ), this, SLOT( receiveMessage( QString ) ) );
    connect( capture_handler->camera_detector, SIGNAL( sendPupilCords( int, int ) ), this, SLOT( receivePupilCords( int, int ) ) );

    // Запуск цикла захвата изображения с камеры.
    capture_handler->captureLoop();

    emit finished();
}

void CameraCaptureWorker::stop()
{
    capture_handler->do_capture = false;
}

void CameraCaptureWorker::switchFilterCommand( const int filter_id )
{
    capture_handler->active_filter = capture_handler->active_filter == filter_id ? 0 : filter_id;
}

void CameraCaptureWorker::switchDetectParamAction( const int detect_param_id )
{
    capture_handler->camera_detector->switchDetectParam( detect_param_id );
}

void CameraCaptureWorker::saveShotAction()
{
    QFile last_image_id("data/last_image_id.txt");
    last_image_id.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&last_image_id);
    int current_image_id = in.readLine().toInt();
    last_image_id.close();

    const char* filename = ( "data/images/" + QString::number( current_image_id ) + QString( ".jpg" ) ).toUtf8().data();
    cvSaveImage( filename, capture_handler->getImage() );
}

void CameraCaptureWorker::videoSaveAction( bool set_status )
{
    capture_handler->videoSave( set_status );
}

void CameraCaptureWorker::setPupilDetectParamsAction( int pupil_contours, int pupil_accuracy, int pupil_min_square, int pupil_max_square )
{
    capture_handler->camera_detector->setPupilDetectParams( pupil_contours, pupil_accuracy, pupil_min_square, pupil_max_square );
}

void CameraCaptureWorker::receiveDataString( QString str )
{
    emit sendDataString( str );
}

void CameraCaptureWorker::receiveImage( QImage img )
{
    emit sendImage( img );
}

void CameraCaptureWorker::receiveMessage( QString msg )
{
    emit sendMessage( msg );
}

void CameraCaptureWorker::receivePupilCords( int x, int y )
{
    emit sendPupilCords( QString::number( x ) + " x " + QString::number( y ) );
}
