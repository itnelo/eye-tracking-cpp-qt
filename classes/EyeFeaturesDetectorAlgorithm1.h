#ifndef EYEFEATURESDETECTORALGORITHM1_H
#define EYEFEATURESDETECTORALGORITHM1_H

#include <QtCore/QDebug>
#include <classes/EyeFeaturesDetectorAlgorithm.h>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"

#include <QtWidgets/QMessageBox>

class EyeFeaturesDetectorAlgorithm1 : public EyeFeaturesDetectorAlgorithm
{
public:
    EyeFeaturesDetectorAlgorithm1();
    virtual ~EyeFeaturesDetectorAlgorithm1();

    virtual int dataOffsetXPupil();
    virtual int dataOffsetYPupil();

    virtual int dataOffsetXBlik();
    virtual int dataOffsetYBlik();

    virtual int dataOffsetSpeed();

protected:
    virtual void _internal_find_algo_pupil(QString path_image);
    virtual void _internal_find_algo_blik(QString path_image);
};

#endif // EYEFEATURESDETECTORALGORITHM1_H
