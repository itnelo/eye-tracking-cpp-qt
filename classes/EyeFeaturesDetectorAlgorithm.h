#ifndef EYEFEATURESDETECTORALGORITHM_H
#define EYEFEATURESDETECTORALGORITHM_H

#include <QtCore/QString>
#include <QtCore/QPoint>

class EyeFeaturesDetectorAlgorithm
{
public:
    EyeFeaturesDetectorAlgorithm();
    virtual ~EyeFeaturesDetectorAlgorithm();

    QPoint findPupil(QString path_image);
    QPoint findBlik(QString path_image);

    virtual int dataOffsetXPupil();
    virtual int dataOffsetYPupil();

    virtual int dataOffsetXBlik();
    virtual int dataOffsetYBlik();

    virtual int dataOffsetSpeed();

protected:
    virtual void _internal_find_algo_pupil(QString path_image);
    virtual void _internal_find_algo_blik(QString path_image);

protected:
    QPoint _center_pupil;
    QPoint _center_blik;
};

#endif // EYEFEATURESDETECTORALGORITHM_H
