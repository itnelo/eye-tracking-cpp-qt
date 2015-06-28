#ifndef CAMERADETECTOR_H
#define CAMERADETECTOR_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/legacy/legacy.hpp>

class CameraDetector : public QObject
{
    Q_OBJECT

public:
    CameraDetector();
    ~CameraDetector();

    void detectFacialFeatures(IplImage* frame, IplImage* bin_frame );

    void switchDetectParam( const int detect_param_id );

    void setPupilDetectParams( int pupil_contours, int pupil_accuracy, int pupil_min_square, int pupil_max_square );

signals:
    void sendPupilCords( int, int );

private:
    void drawEyes( IplImage* frame, CvRect* rectangle );
    void drawPupils( IplImage* frame, IplImage* bin_frame );
    void drawNose( IplImage* frame, CvRect* rectangle );
    void drawMouth( IplImage* frame, CvRect* rectangle );

private:
    CvMemStorage*            storage;
    CvHaarClassifierCascade* cascade_face;
    CvHaarClassifierCascade* cascade_eyes;
    CvHaarClassifierCascade* cascade_nose;
    CvHaarClassifierCascade* cascade_mouth;

    bool draw_faces;
    bool draw_eyes;
    bool draw_pupils;
    bool draw_nose;
    bool draw_mouth;

    int pupil_contour_points_total;
    int pupil_contour_ellipse_accuracy;
    int pupil_contour_min_square;
    int pupil_contour_max_square;
};

#endif // CAMERADETECTOR_H
