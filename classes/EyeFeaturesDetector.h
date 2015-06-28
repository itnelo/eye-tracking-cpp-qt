#ifndef EYEFEATURESDETECTOR_H
#define EYEFEATURESDETECTOR_H

#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QElapsedTimer>
#include <classes/EyeFeaturesDetectorAlgorithm1.h>
#include <classes/EyeFeaturesDetectorAlgorithm2.h>

class EyeFeaturesDetector
{
public:

    static const int MODE_DETECT_PUPIL = 1;
    static const int MODE_DETECT_BLIK  = 2;

public:
    ~EyeFeaturesDetector();

    static EyeFeaturesDetector* instance() {
        static EyeFeaturesDetector _efd;
        return &_efd;
    }

    void setPathData(QString data_path);
    void setDirImages(QString dir_images_path);
    void setAlgo(EyeFeaturesDetectorAlgorithm* algo);

    void detect(int options = EyeFeaturesDetector::MODE_DETECT_PUPIL);
    void free();

private:
    EyeFeaturesDetector();
    EyeFeaturesDetector( const EyeFeaturesDetector& );
    EyeFeaturesDetector& operator = ( const EyeFeaturesDetector& );

private:
    QString                         _dir_images_path;
    QString                         _data_path;
    EyeFeaturesDetectorAlgorithm*   _algo;
};

#endif // EYEFEATURESDETECTOR_H
