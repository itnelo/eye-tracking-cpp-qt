#include "EyeFeaturesDetectorAlgorithm2.h"

EyeFeaturesDetectorAlgorithm2::EyeFeaturesDetectorAlgorithm2() :
    EyeFeaturesDetectorAlgorithm()
{}

EyeFeaturesDetectorAlgorithm2::~EyeFeaturesDetectorAlgorithm2()
{}

int EyeFeaturesDetectorAlgorithm2::dataOffsetXPupil()
{
    return 18;
}

int EyeFeaturesDetectorAlgorithm2::dataOffsetYPupil()
{
    return 19;
}

int EyeFeaturesDetectorAlgorithm2::dataOffsetXBlik()
{
    return 20;
}

int EyeFeaturesDetectorAlgorithm2::dataOffsetYBlik()
{
    return 21;
}

int EyeFeaturesDetectorAlgorithm2::dataOffsetSpeed()
{
    return 23;
}

void EyeFeaturesDetectorAlgorithm2::_internal_find_algo_pupil(QString path_image)
{
    cv::Mat src = cv::imread( path_image.toStdString() );

    double max_grad_s = 0;
    double min_grad_s = 10000;
    double** sobel_mask = new double*[ 1000 ];
    for (int i = 0; i < 1000; ++i) {
        sobel_mask[ i ] = new double[1000];
    }

    cv::Mat gray;
    cv::Size gray_size = src.size();

    // Хранилище памяти для кругов
    CvMemStorage* storage = cvCreateMemStorage(0);

    // grayscale.
    cv::cvtColor( src, gray, CV_BGR2GRAY );

    // blur.
    cv::GaussianBlur( gray, gray, Size(9, 9), 2, 2 );

    _max_grad_points.clear();

    // Source sobel mask calc.
    for( int i = 40; i < gray_size.height - 40; ++i )
        for( int j = 40; j < gray_size.width - 40; ++j )
        {
            int grad_x = 0;
            int grad_y = 0;
            int grad_s = 0;

            // * . .     . . *
            // * _ .     . _ *
            // * . .     . . *
            grad_x += gray.at<uchar>(i - 1, j - 1) * (-1);
            grad_x += gray.at<uchar>(i,     j - 1) * (-2);
            grad_x += gray.at<uchar>(i + 1, j - 1) * (-1);

            grad_x += gray.at<uchar>(i - 1, j + 1) * (1);
            grad_x += gray.at<uchar>(i,     j + 1) * (2);
            grad_x += gray.at<uchar>(i + 1, j + 1) * (1);

            // * * *     . . .
            // . _ .     . _ .
            // . . .     * * *
            grad_y += gray.at<uchar>(i - 1, j - 1) * (-1);
            grad_y += gray.at<uchar>(i - 1, j    ) * (-2);
            grad_y += gray.at<uchar>(i - 1, j + 1) * (-1);

            grad_y += gray.at<uchar>(i + 1, j - 1) * (1);
            grad_y += gray.at<uchar>(i + 1, j    ) * (2);
            grad_y += gray.at<uchar>(i + 1, j + 1) * (1);

            grad_s = sqrt( pow( grad_x, 2 ) + pow( grad_y, 2 ) );

            sobel_mask[ i ][ j ] = grad_s;

            if( grad_s > max_grad_s )
            {
                max_grad_s = grad_s;
                _max_grad_points.append(QPoint(j, i));
            }

            if( grad_s < min_grad_s )
            {
                min_grad_s = grad_s;
            }
        }

    // Normize.
    double norm_value = 255 / (max_grad_s - min_grad_s);

    for( int i = 40; i < gray_size.height - 40; ++i )
        for( int j = 40; j < gray_size.width - 40; ++j ) {
            gray.at<uchar>(i, j) = floor( (sobel_mask[ i ][ j ] - min_grad_s) * norm_value );
        }

    IplImage src_img_ = gray;
    IplImage* src_img = &src_img_;

    // Поиск кругов
    CvSeq* results = cvHoughCircles(
            src_img,
            storage,
            CV_HOUGH_GRADIENT,
            5,
            gray_size.width,
            50,
            50,
            10,
            30
            );

    // Пробегаемся по кругам и рисуем их на оригинальном изображении.
    for( int i = 0; i < results->total; ++i ) {
        float* p = (float*) cvGetSeqElem( results, i );
        CvPoint pt = cvPoint( cvRound( p[0] ), cvRound( p[1] ) );
        //cv::circle( src, pt, cvRound( p[2] ), CV_RGB(0xff,0,0) );
        _center_pupil = QPoint(pt.x, pt.y);
        break;
    }

    // free.
    cvReleaseMemStorage(&storage);

    for (int i = 0; i < 1000; ++i) {
        delete[] sobel_mask[ i ];
    }
    delete[] sobel_mask;
}

void EyeFeaturesDetectorAlgorithm2::_internal_find_algo_blik(QString path_image)
{
    _center_blik = _max_grad_points.isEmpty()
            ? QPoint(0, 0)
            : _max_grad_points.last()
    ;
}
