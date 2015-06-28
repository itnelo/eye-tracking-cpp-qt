#ifndef EYEFEATURESDETECTORALGORITHM2_H
#define EYEFEATURESDETECTORALGORITHM2_H

#include <QtCore/QList>
#include <QtCore/QPoint>
#include <classes/EyeFeaturesDetectorAlgorithm.h>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include <vector>
#include <map>

using namespace std;
using namespace cv;

class EyeFeaturesDetectorAlgorithm2 : public EyeFeaturesDetectorAlgorithm
{
public:
    EyeFeaturesDetectorAlgorithm2();
    virtual ~EyeFeaturesDetectorAlgorithm2();

    virtual int dataOffsetXPupil();
    virtual int dataOffsetYPupil();

    virtual int dataOffsetXBlik();
    virtual int dataOffsetYBlik();

    virtual int dataOffsetSpeed();

protected:
    virtual void _internal_find_algo_pupil(QString path_image);
    virtual void _internal_find_algo_blik(QString path_image);

private:
    QList<QPoint> _max_grad_points;
};

#endif // EYEFEATURESDETECTORALGORITHM2_H
