#include "EyeFeaturesDetectorAlgorithm.h"

EyeFeaturesDetectorAlgorithm::EyeFeaturesDetectorAlgorithm()
{}

EyeFeaturesDetectorAlgorithm::~EyeFeaturesDetectorAlgorithm()
{}

QPoint EyeFeaturesDetectorAlgorithm::findPupil(QString path_image)
{
    _internal_find_algo_pupil(path_image);
    return _center_pupil;
}

QPoint EyeFeaturesDetectorAlgorithm::findBlik(QString path_image)
{
    _internal_find_algo_blik(path_image);
    return _center_blik;
}

void EyeFeaturesDetectorAlgorithm::_internal_find_algo_pupil(QString path_image)
{
    _center_pupil = QPoint(0, 0);
}

void EyeFeaturesDetectorAlgorithm::_internal_find_algo_blik(QString path_image)
{
    _center_blik = QPoint(0, 0);
}

int EyeFeaturesDetectorAlgorithm::dataOffsetXPupil()
{
    return -1;
}

int EyeFeaturesDetectorAlgorithm::dataOffsetYPupil()
{
    return -1;
}

int EyeFeaturesDetectorAlgorithm::dataOffsetXBlik()
{
    return -1;
}

int EyeFeaturesDetectorAlgorithm::dataOffsetYBlik()
{
    return -1;
}

int EyeFeaturesDetectorAlgorithm::dataOffsetSpeed()
{
    return -1;
}
