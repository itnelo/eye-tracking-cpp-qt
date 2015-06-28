#include "QImageLabelPoint.h"

const QColor    QImageLabelPoint::DEFAULT_COLOR_NONE            = QColor(qRgb(0, 0, 0));
const QColor    QImageLabelPoint::DEFAULT_COLOR_PUPIL           = QColor(qRgb(0, 255, 0));
const QColor    QImageLabelPoint::DEFAULT_COLOR_BLIK            = QColor(qRgb(0, 255, 255));
const QColor    QImageLabelPoint::DEFAULT_COLOR_PUPIL_AUTO1     = QColor(qRgb(255, 255, 0));
const QColor    QImageLabelPoint::DEFAULT_COLOR_PUPIL_AUTO2     = QColor(qRgb(255, 0, 255));
const QColor    QImageLabelPoint::DEFAULT_COLOR_BLIK_AUTO1      = QColor(qRgb(255, 0, 0));
const QColor    QImageLabelPoint::DEFAULT_COLOR_BLIK_AUTO2      = QColor(qRgb(214, 145, 66));

QImageLabelPoint::QImageLabelPoint(int x, int y, int type, QColor color) :
    QPoint(x, y)
{
    setType(type);

    if (!color.isValid()) {
        switch (type) {

            case QImageLabelPoint::TYPE_PUPIL:
                color = QImageLabelPoint::DEFAULT_COLOR_PUPIL;
                break;

            case QImageLabelPoint::TYPE_BLIK:
                color = QImageLabelPoint::DEFAULT_COLOR_BLIK;
                break;

            case QImageLabelPoint::TYPE_PUPIL_AUTO1:
                color = QImageLabelPoint::DEFAULT_COLOR_PUPIL_AUTO1;
                break;

            case QImageLabelPoint::TYPE_PUPIL_AUTO2:
                color = QImageLabelPoint::DEFAULT_COLOR_PUPIL_AUTO2;
                break;

            case QImageLabelPoint::TYPE_BLIK_AUTO1:
                color = QImageLabelPoint::DEFAULT_COLOR_BLIK_AUTO1;
                break;

            case QImageLabelPoint::TYPE_BLIK_AUTO2:
                color = QImageLabelPoint::DEFAULT_COLOR_BLIK_AUTO2;
                break;

            default:
                color = QImageLabelPoint::DEFAULT_COLOR_NONE;

        }
    }

    setColor(color);
}

QImageLabelPoint::QImageLabelPoint() :
    QPoint()
{}

void QImageLabelPoint::setColor(const QColor& color)
{
    _color = color;
}

void QImageLabelPoint::setType(int point_type_const)
{
    _type = point_type_const;
}

QColor QImageLabelPoint::getColor() const
{
    return _color;
}

int QImageLabelPoint::getType() const
{
    return _type;
}
