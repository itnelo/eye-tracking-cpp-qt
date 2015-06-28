#include "CameraManager.h"

CameraManager::~CameraManager()
{
    //if( draw_label != NULL )
    //    delete draw_label;

    emit stopCaptureThread();
}

bool CameraManager::isRunning()
{
    return running_status;
}

bool CameraManager::startCapture( QLabel* label_ptr, QLineEdit* edit_ptr, QTextEdit* tedit_ptr )
{
    running_status = true;

    draw_label  = label_ptr;
    edit_cords  = edit_ptr;
    tedit_cords = tedit_ptr;

    addCaptureThread();

    return true;
}

void CameraManager::stopCapture()
{
    running_status = false;

    emit stopCaptureThread();
}

void CameraManager::videoSave( bool set_status )
{
    emit videoSaveCommand( set_status );
}

void CameraManager::saveShot()
{
    emit saveShotCommand();
}

void CameraManager::switchFilter( const int filter_id )
{
    emit switchFilterCommand( filter_id );
}

void CameraManager::switchDetectParam( const int detect_param_id )
{
    emit switchDetectParamCommand( detect_param_id );
}

void CameraManager::setPupilDetectParams( int pupil_contours, int pupil_accuracy, int pupil_min_square, int pupil_max_square )
{
    emit setPupilDetectParamsCommand( pupil_contours, pupil_accuracy, pupil_min_square, pupil_max_square );
}

void CameraManager::addCaptureThread()
{
    CameraCaptureWorker* worker = new CameraCaptureWorker;
    QThread* thread = new QThread;
    worker->moveToThread( thread );

    connect( thread, SIGNAL( started() ), worker, SLOT( process() ) );
    connect( worker, SIGNAL( finished() ), thread, SLOT( quit() ) );
    connect( thread, SIGNAL( finished() ), thread, SLOT( deleteLater() ) );
    connect( worker, SIGNAL( finished() ), worker, SLOT( deleteLater() ) );
    connect( worker, SIGNAL( finished() ), this, SLOT( stopCapture() ) );

    connect( this, SIGNAL( stopCaptureThread() ), worker, SLOT( stop() ), Qt::DirectConnection );
    connect( this, SIGNAL( switchFilterCommand( const int ) ), worker, SLOT( switchFilterCommand( const int ) ), Qt::DirectConnection );
    connect( this, SIGNAL( saveShotCommand() ), worker, SLOT( saveShotAction() ), Qt::DirectConnection );
    connect( this, SIGNAL( switchDetectParamCommand( const int ) ), worker, SLOT( switchDetectParamAction( const int ) ), Qt::DirectConnection );
    connect( this, SIGNAL( setPupilDetectParamsCommand( int, int, int, int ) ), worker, SLOT( setPupilDetectParamsAction( int, int, int, int ) ), Qt::DirectConnection );
    connect( this, SIGNAL( videoSaveCommand( bool ) ), worker, SLOT( videoSaveAction( bool ) ), Qt::DirectConnection );

    connect( worker, SIGNAL( sendImage( QImage ) ), this, SLOT( drawImage( QImage ) ) );
    connect( worker, SIGNAL( sendMessage( QString ) ), this, SLOT( viewMessage( QString ) ) );
    connect( worker, SIGNAL( sendPupilCords( QString ) ), edit_cords, SLOT( setText( QString ) ) );
    connect( worker, SIGNAL( sendPupilCords( QString ) ), tedit_cords, SLOT( append( QString ) ) );

    thread->start();
}

void CameraManager::drawImage( QImage img )
{
    QPixmap _source = QPixmap::fromImage(img);
    double _scale_factor = 1.8;

    QPixmap _scaled = _source.scaled(_scale_factor * _source.size(), Qt::KeepAspectRatio);

    draw_label->setPixmap( _scaled.copy(50, 37, 479, 358) );
    draw_label->show();
}

void CameraManager::viewMessage( QString msg )
{
    QMessageBox mbox;
    mbox.setText( msg );
    mbox.exec();
}
