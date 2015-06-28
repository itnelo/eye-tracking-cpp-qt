#include "CameraCapture.h"

const int FILTER_NONE      = 0;
const int FILTER_SMOOTH    = 1;
const int FILTER_ERODE     = 2;
const int FILTER_DILATE    = 3;
const int FILTER_THRESHOLD = 4;

double GetRandomNormalized()
{
    return ( double )( rand() - ( RAND_MAX >> 1 ) ) / ( double )( RAND_MAX >> 1 );
}

QImage IplImage2QImage( const IplImage* iplImage )
{
    int height = iplImage->height;
    int width  = iplImage->width;

    const uchar* QImageBuffer = ( const uchar* )iplImage->imageData;
    QImage img( QImageBuffer, width, height, QImage::Format_RGB32 );
    return img.rgbSwapped();
}

CameraCapture::CameraCapture()
{
    camera_detector = new CameraDetector;
    video_writer    = 0;
    do_capture      = false;
    do_save_capture = false;
    active_filter   = FILTER_NONE;
    frame           = NULL;
    filtered_frame  = NULL;
}

CameraCapture::~CameraCapture()
{
    if( camera_detector != NULL )
        delete camera_detector;

    cvReleaseVideoWriter( &video_writer );

    if( frame != NULL )
        cvReleaseImage( &frame );

    if( filtered_frame != NULL )
        cvReleaseImage( &filtered_frame );
}

void CameraCapture::captureLoop()
{
    int w, h;
    PBYTE pCapBuffer = NULL;
    IplImage* tmp_frame;
    IplImage* bin_frame;
    QImage qImg;

    GUID cameraGUID                  = CLEyeGetCameraUUID( 0 );
    CLEyeCameraColorMode mode        = CLEYE_COLOR_PROCESSED;
    CLEyeCameraResolution resolution = CLEYE_QVGA;
    float fps                        = 30;

    // Create camera instance.
    CLEyeCameraInstance cam = CLEyeCreateCamera( cameraGUID, mode, resolution, fps );

    if( cam == NULL )
    {
        emit sendMessage( "camera not found" );
        return;
    }

    // Get camera frame dimensions.
    CLEyeCameraGetFrameDimensions( cam, w, h );

    frame          = cvCreateImage( cvSize(w, h), IPL_DEPTH_8U, 4 );
    filtered_frame = cvCreateImage( cvSize( frame->width, frame->height ), IPL_DEPTH_8U, 4 );
    bin_frame      = cvCreateImage( cvSize( frame->width, frame->height ), 8, 1 );

    // Set some camera parameters.
    CLEyeSetCameraParameter( cam, CLEYE_GAIN, 15 );
    CLEyeSetCameraParameter( cam, CLEYE_EXPOSURE, 511 );
    CLEyeSetCameraParameter( cam, CLEYE_ZOOM, ( int )( GetRandomNormalized() * 100.0 ) );
    //CLEyeSetCameraParameter( cam, CLEYE_ROTATION, (int)(GetRandomNormalized()*300.0));

    // Start capturing.
    CLEyeCameraStart( cam );
    cvGetRawData( frame, &pCapBuffer );

    do_capture = true;

    // Camera Capture Cycle.
    while( do_capture )
    {
        CLEyeCameraGetFrame( cam, pCapBuffer );

        camera_detector->detectFacialFeatures( frame, bin_frame );

        if( do_save_capture && video_writer != 0 )
            cvWriteFrame( video_writer, frame );

        qImg = IplImage2QImage( getImage() );

        emit sendImage( qImg );
    }

    // Stop camera capture.
    CLEyeCameraStop( cam );

    // Destroy camera object.
    CLEyeDestroyCamera( cam );

    cvReleaseImage( &bin_frame );
    cvReleaseImage( &filtered_frame );
    cvReleaseImage( &frame );

    frame          = NULL;
    filtered_frame = NULL;
}

IplImage* CameraCapture::getImage()
{
    return active_filter != FILTER_NONE ? useFilter() : frame;
}

IplImage* CameraCapture::useFilter()
{
    switch( active_filter )
    {
        case FILTER_SMOOTH:
            cvSmooth( frame, filtered_frame, CV_BLUR, 10, 10 );
            break;
        case FILTER_ERODE:
            cvErode( frame, filtered_frame, NULL, 3 );
            break;
        case FILTER_DILATE:
            cvDilate( frame, filtered_frame, NULL, 4 );
            break;
        case FILTER_THRESHOLD:
            cvThreshold( frame, filtered_frame, 50, 250, CV_THRESH_BINARY );
            break;
    }

    return filtered_frame;
}

void CameraCapture::videoSave( bool set_status )
{
    static int vcount;

    if( set_status )
    {
        const char* filename = ( QString( "Video" ) + QString::number( ++vcount ) + QString( ".avi" ) ).toUtf8().data();
        video_writer = cvCreateVideoWriter( filename, CV_FOURCC( 'X', 'V', 'I', 'D' ), 15, cvSize( 320, 240 ), 1 );
        //assert( video_writer != 0 );
        do_save_capture = true;
    }
    else
    {
        do_save_capture = false;
        cvReleaseVideoWriter( &video_writer );
        video_writer = 0;
    }
}
