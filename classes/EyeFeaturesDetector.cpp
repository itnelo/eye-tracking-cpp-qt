#include "EyeFeaturesDetector.h"

EyeFeaturesDetector::EyeFeaturesDetector()
{}

EyeFeaturesDetector::~EyeFeaturesDetector()
{}

void EyeFeaturesDetector::setPathData(QString data_path)
{
    _data_path = data_path;
}

void EyeFeaturesDetector::setDirImages(QString dir_images_path)
{
    _dir_images_path = dir_images_path;
}

void EyeFeaturesDetector::setAlgo(EyeFeaturesDetectorAlgorithm* algo)
{
    _algo = algo;
}

void EyeFeaturesDetector::detect(int options)
{
    QFile db(_data_path);

    if (!db.exists()) {
        qDebug() << "not exists";
        return;
    }

    db.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream db_stream(&db);
    QStringList string_list;
    string_list << db_stream.readLine();

    while (!db_stream.atEnd()) {
        QString record = db_stream.readLine();
        QStringList parts = record.split(";");
        QString image_path = parts.at(1).trimmed();
        QElapsedTimer a_timer;
        double a_time = 0.0;

        if (options & EyeFeaturesDetector::MODE_DETECT_PUPIL) {

            a_timer.start();
            QPoint eye_feature_center = _algo->findPupil(image_path);
            a_time += a_timer.nsecsElapsed() / 1000000.0 / 1000.0;

            parts.replace(_algo->dataOffsetXPupil(), QString::number(eye_feature_center.x()));
            parts.replace(_algo->dataOffsetYPupil(), QString::number(eye_feature_center.y()));

        }

        if (options & EyeFeaturesDetector::MODE_DETECT_BLIK) {

            a_timer.start();
            QPoint eye_feature_center = _algo->findBlik(image_path);
            a_time += a_timer.nsecsElapsed() / 1000000.0 / 1000.0;

            parts.replace(_algo->dataOffsetXBlik(), QString::number(eye_feature_center.x()));
            parts.replace(_algo->dataOffsetYBlik(), QString::number(eye_feature_center.y()));

        }

        parts.replace(_algo->dataOffsetSpeed(), QString::number(a_time, 'f', 4));

        record = parts.join(";");
        string_list << record;
    }

    db.close();

    db.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    db_stream << string_list.join("\n") << "\n";
    db.close();
}

void EyeFeaturesDetector::free()
{
    if (NULL != _algo) {
        delete _algo;
    }
}
