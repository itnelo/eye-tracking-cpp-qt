#include "EyeFeaturesDetectorAlgorithm1.h"

EyeFeaturesDetectorAlgorithm1::EyeFeaturesDetectorAlgorithm1() :
    EyeFeaturesDetectorAlgorithm()
{}

EyeFeaturesDetectorAlgorithm1::~EyeFeaturesDetectorAlgorithm1()
{}

int EyeFeaturesDetectorAlgorithm1::dataOffsetXPupil()
{
    return 14;
}

int EyeFeaturesDetectorAlgorithm1::dataOffsetYPupil()
{
    return 15;
}

int EyeFeaturesDetectorAlgorithm1::dataOffsetXBlik()
{
    return 16;
}

int EyeFeaturesDetectorAlgorithm1::dataOffsetYBlik()
{
    return 17;
}

int EyeFeaturesDetectorAlgorithm1::dataOffsetSpeed()
{
    return 22;
}

void EyeFeaturesDetectorAlgorithm1::_internal_find_algo_pupil(QString path_image)
{
    //cv::Mat src = cv::imread( "1.jpg" );
    cv::Mat src = cv::imread( path_image.toStdString() );
    cv::Mat gray;
    cv::cvtColor( ~src, gray, CV_BGR2GRAY);
    //imwrite(path_image.append(".gray.jpg").toStdString(), gray);

    cv::threshold(gray, gray, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU );
    //imwrite(path_image.append(".threshold.jpg").toStdString(), gray);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(gray.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    //cv::drawContours(gray, contours, -1, CV_RGB(255,255,255), -1);

    if (!contours.empty()) {
        cv::Rect rect = cv::boundingRect(contours.front());
        _center_pupil = QPoint(rect.x + rect.width/2, rect.y + rect.width/2);
    } else {
        _center_pupil = QPoint(0, 0);
    }

    int    p1_min = 100;
    double p2_min = 0.8;
    double p3_min = 0.8;

    for (int i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);    // Blob area
        cv::Rect rect = cv::boundingRect(contours[i]); // Bounding box

        if (rect.width < 15 || rect.width > 100) {
            continue;
        }

        float radius = rect.width / 2;                     // Approximate radius

        int    p1_result = std::abs(30 - rect.width);
        double p2_result = std::abs(1 - ((double)rect.width / (double)rect.height));
        double p3_result = std::abs(1 - (area / (CV_PI * std::pow(radius, 2))));

        //cv::circle(src, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 1);

        // Look for max. round shaped blob
        if (p1_result <= p1_min && p2_result <= p2_min && p3_result <= p3_min)
        {
            //cv::circle(src, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 1);

            _center_pupil = QPoint(rect.x + radius, rect.y + radius);

            p1_min = p1_result;
            p2_min = p2_result;
            p3_min = p3_result;
        }
    }

    //imwrite(path_image.append(".algo1.jpg").toStdString(), src);
}

void EyeFeaturesDetectorAlgorithm1::_internal_find_algo_blik(QString path_image)
{
    //cv::Mat src = cv::imread( "1.jpg" );
    cv::Mat src = cv::imread( path_image.toStdString() );
    cv::Mat gray;
    cv::cvtColor( src, gray, CV_BGR2GRAY);

    int threshold_value = 0;

    for (size_t i = 0; i < gray.rows; ++i) {
        for (size_t j = 0; j < gray.cols; ++j) {
            if (threshold_value < gray.at<uchar>(i, j)) {
                threshold_value = gray.at<uchar>(i, j);
            }
        }
    }

    cv::threshold(gray, gray, threshold_value - 15, 255, cv::THRESH_BINARY );
    //imwrite(path_image.append(".algo1-blik.jpg").toStdString(), gray);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(gray.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    if (!contours.empty()) {

        auto nearest_contour = contours[0];
        cv::Rect r = cv::boundingRect(nearest_contour);
        int min_d = std::sqrt( std::pow(_center_pupil.x() - r.x, 2) + std::pow(_center_pupil.y() - r.y, 2) );

        for (size_t i = 1; i < contours.size(); ++i) {
            r = cv::boundingRect(contours[i]);
            int cur_d = std::sqrt( std::pow(_center_pupil.x() - r.x, 2) + std::pow(_center_pupil.y() - r.y, 2) );
            if (cur_d < min_d) {
                nearest_contour = contours[i];
                min_d = cur_d;
            }
        }

        r = cv::boundingRect(nearest_contour);
        float radius = r.width / 2;

        _center_blik = QPoint(r.x + radius, r.y + radius);

        //cv::circle(gray, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 1);
        //imwrite(path_image.append(".algo1-blik.jpg").toStdString(), gray);

    } else {

        _center_blik = QPoint(0, 0);

    }
}
