#include "CameraDetector.h"

const int DETECT_PARAM_FACE   = 1;
const int DETECT_PARAM_EYES   = 2;
const int DETECT_PARAM_NOSE   = 3;
const int DETECT_PARAM_MOUTH  = 4;
const int DETECT_PARAM_PUPILS = 5;

const char* face_cascade  = "haarcascade_frontalface_alt2.xml";
const char* eyes_cascade  = "haarcascade_mcs_eyepair_big.xml";
const char* nose_cascade  = "haarcascade_mcs_nose.xml";
const char* mouth_cascade = "haarcascade_mcs_mouth.xml";

CameraDetector::CameraDetector()
{
    storage = cvCreateMemStorage( 0 );

    cascade_face  = ( CvHaarClassifierCascade* )cvLoad( face_cascade, 0, 0, 0 );
    cascade_eyes  = ( CvHaarClassifierCascade* )cvLoad( eyes_cascade, 0, 0, 0 );
    cascade_nose  = ( CvHaarClassifierCascade* )cvLoad( nose_cascade, 0, 0, 0 );
    cascade_mouth = ( CvHaarClassifierCascade* )cvLoad( mouth_cascade, 0, 0, 0 );

    draw_faces  = false;
    draw_eyes   = false;
    draw_pupils = false;
    draw_nose   = false;
    draw_mouth  = false;

    pupil_contour_points_total     = 6;
    pupil_contour_ellipse_accuracy = 0.9;
    pupil_contour_min_square       = 30;
    pupil_contour_max_square       = 500;
}

CameraDetector::~CameraDetector()
{
    cvReleaseHaarClassifierCascade( &cascade_face );
    cvReleaseHaarClassifierCascade( &cascade_eyes );
    cvReleaseHaarClassifierCascade( &cascade_nose );
    cvReleaseHaarClassifierCascade( &cascade_mouth );

    cvReleaseMemStorage( &storage );
}

void CameraDetector::detectFacialFeatures( IplImage* frame, IplImage* bin_frame )
{
    float m[ 6 ];
    double factor = 1;
    //CvMat M = cvMat( 2, 3, CV_32F, m );
    int width  = frame->width;
    int height = frame->height;
    CvSeq* faces;
    CvRect* rectangle;

    m[ 0 ] = ( float)( factor * cos( 0.0 ) );
    m[ 1 ] = ( float )( factor * sin( 0.0 ) );
    m[ 2 ] = width * 0.5f;
    m[ 3 ] = -m[ 1 ];
    m[ 4 ] = m[ 0 ];
    m[ 5 ] = height * 0.5f;

    //cvGetQuadrangleSubPix(img, temp_img, &M);
    //CvMemStorage* storage=cvCreateMemStorage(0);
    //cvClearMemStorage( storage );

    faces = cvHaarDetectObjects( frame, cascade_face, storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING, cvSize( 20, 20 ) );

    /* for each face found, draw a red box */
    for( int i = 0; i < ( faces ? faces->total : 0 ); ++i )
    {
        rectangle = ( CvRect* )cvGetSeqElem( faces, i );

        if( draw_faces )
            cvRectangle( frame,
                         cvPoint( rectangle->x, rectangle->y ),
                         cvPoint( rectangle->x + rectangle->width, rectangle->y + rectangle->height ),
                         CV_RGB( 255, 0, 0 ),
                         1, 8, 0 );

        if( draw_eyes )
            drawEyes( frame, rectangle );

        if( draw_nose )
        {
            cvResetImageROI( frame );
            drawNose( frame, rectangle );
        }

        if( draw_mouth )
        {
            cvResetImageROI( frame );
            drawMouth( frame, rectangle );
        }

        cvResetImageROI( frame );
    }

    if( draw_pupils )
        drawPupils( frame, bin_frame );

    /* reset region of interest */
    cvResetImageROI( frame );
}

void CameraDetector::switchDetectParam( const int detect_param_id )
{
    switch( detect_param_id )
    {
        case DETECT_PARAM_FACE:
            draw_faces = !draw_faces;
            break;
        case DETECT_PARAM_EYES:
            draw_eyes = !draw_eyes;
            break;
        case DETECT_PARAM_NOSE:
            draw_nose = !draw_nose;
            break;
        case DETECT_PARAM_MOUTH:
            draw_mouth = !draw_mouth;
            break;
        case DETECT_PARAM_PUPILS:
            draw_pupils = !draw_pupils;
            break;
    }
}

void CameraDetector::setPupilDetectParams( int pupil_contours, int pupil_accuracy, int pupil_min_square, int pupil_max_square )
{
    pupil_contour_points_total     = pupil_contours;
    pupil_contour_ellipse_accuracy = pupil_accuracy;
    pupil_contour_min_square       = pupil_min_square;
    pupil_contour_max_square       = pupil_max_square;
}

void CameraDetector::drawEyes( IplImage* frame, CvRect* rectangle )
{
    CvSeq* eyes_polygons;
    int eyes_count = 0;

    // Set the Region of Interest: estimate the eyes' position.
    cvSetImageROI( frame, cvRect(
                            rectangle->x,
                            rectangle->y + ( rectangle->height / 5.5 ),
                            rectangle->width,
                            rectangle->height / 3.0 ) );

    // Set the eyes poligons.
    eyes_polygons = cvHaarDetectObjects( frame, cascade_eyes, storage, 1.15, 3, 0, cvSize(25, 15) );

    // Draw a rectangle for each detected eyes.
    for( int i = 0; i < ( eyes_polygons ? eyes_polygons->total : 0 ); ++i )
    {
        ++eyes_count;

        // Get one eye polygon cordinates..
        CvRect* eye_cords = ( CvRect* )cvGetSeqElem( eyes_polygons, i );

        // Draw a red rectangle.
        cvRectangle( frame, cvPoint( eye_cords->x, eye_cords->y ),
                            cvPoint( eye_cords->x + eye_cords->width, eye_cords->y + eye_cords->height ),
                            CV_RGB( 0, 0, 255 ),
                            1, 8, 0 );
    }
}

void CameraDetector::drawPupils( IplImage* frame, IplImage* bin_frame )
{
    int box_square;
    int pupil_x, pupil_y;

    cvCvtColor( frame, bin_frame, CV_RGB2GRAY );
    cvEqualizeHist( bin_frame, bin_frame );
    cvCanny( bin_frame, bin_frame, 50, 150 );

    CvMemStorage*    pupil_storage  = cvCreateMemStorage( 0 );
    CvContourScanner pupil_traverse = cvStartFindContours( bin_frame, pupil_storage, sizeof( CvContour ), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    for( CvSeq* contour = cvFindNextContour( pupil_traverse ); contour; contour = cvFindNextContour( pupil_traverse ) )
    {
        if ( contour->total > pupil_contour_points_total )
        {
            CvBox2D box = cvFitEllipse2( contour );
            CvPoint center = cvPointFrom32f( box.center );
            CvSize size = cvSize( cvRound( box.size.width * 0.5 ), cvRound( box.size.height * 0.5 ) );

            box_square = box.size.width * box.size.height;

            // Отсеиваем то, что не похоже на окружность.
            if( ( double )box.size.width / ( double )box.size.height > pupil_contour_ellipse_accuracy &&
                 box_square > pupil_contour_min_square && box_square < pupil_contour_max_square  )
            {
                cvEllipse( frame, center, size, -box.angle, 0, 360, CV_RGB(0, 0, 255), 4, CV_AA, 0);

                pupil_x = ( int )box.center.x;
                pupil_y = ( int )box.center.y;

                //std::cout << "---TRACE--- BOX square:" << box.size.width * box.size.height << std::endl;
            }
        }
    }

    cvEndFindContours( &pupil_traverse );
    cvReleaseMemStorage( &pupil_storage );

    if( pupil_x > 0 && pupil_y > 0 )
        emit sendPupilCords( pupil_x, pupil_y );
}

void CameraDetector::drawNose( IplImage* frame, CvRect* rectangle )
{
    CvSeq* nose_polygons;

    // Set the Region of Interest: nose' position.
    cvSetImageROI( frame, cvRect(
                            rectangle->x,
                            rectangle->y,
                            rectangle->width,
                            rectangle->height ) );

    nose_polygons = cvHaarDetectObjects( frame, cascade_nose, storage, 1.15, 3, 0, cvSize(25, 15) );

    for( int i = 0; i < ( nose_polygons ? nose_polygons->total : 0 ); ++i )
    {
        CvRect* nose_cords = ( CvRect* )cvGetSeqElem( nose_polygons, i );

        cvRectangle( frame, cvPoint( nose_cords->x, nose_cords->y ),
                            cvPoint( nose_cords->x + nose_cords->width, nose_cords->y + nose_cords->height ),
                            CV_RGB( 0, 255, 0 ),
                            1, 8, 0 );
    }
}

void CameraDetector::drawMouth( IplImage* frame, CvRect* rectangle )
{
    CvSeq* mouth_polygons;

    // Mouth detecetion - set ROI.
    cvSetImageROI( frame, cvRect(
                            rectangle->x,
                            rectangle->y + ( rectangle->height * 2/3 ),
                            rectangle->width,
                            rectangle->height / 3 ) );

    mouth_polygons = cvHaarDetectObjects( frame, cascade_mouth, storage, 1.15, 4, 0, cvSize(25, 15) );

    for( int i = 0; i < ( mouth_polygons ? mouth_polygons->total : 0 ); ++i )
    {
        CvRect* mouth_cords = ( CvRect* )cvGetSeqElem( mouth_polygons, i );

        cvRectangle( frame, cvPoint( mouth_cords->x, mouth_cords->y ),
                            cvPoint( mouth_cords->x + mouth_cords->width, mouth_cords->y + mouth_cords->height ),
                            CV_RGB( 255, 255, 255 ),
                            1, 8, 0 );
    }
}
