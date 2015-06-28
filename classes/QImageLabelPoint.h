#ifndef QIMAGELABELPOINT_H
#define QIMAGELABELPOINT_H

#include <QtCore/QPoint>
#include <QtGui/QColor>

class QImageLabelPoint : public QPoint
{
public:

    static const    int         TYPE_NONE               = 0;
    static const    int         TYPE_PUPIL              = 2;
    static const    int         TYPE_BLIK               = 4;
    static const    int         TYPE_PUPIL_AUTO1        = 8;
    static const    int         TYPE_PUPIL_AUTO2        = 16;
    static const    int         TYPE_BLIK_AUTO1         = 32;
    static const    int         TYPE_BLIK_AUTO2         = 64;

    static const    QColor      DEFAULT_COLOR_NONE;
    static const    QColor      DEFAULT_COLOR_PUPIL;
    static const    QColor      DEFAULT_COLOR_BLIK;
    static const    QColor      DEFAULT_COLOR_PUPIL_AUTO1;
    static const    QColor      DEFAULT_COLOR_PUPIL_AUTO2;
    static const    QColor      DEFAULT_COLOR_BLIK_AUTO1;
    static const    QColor      DEFAULT_COLOR_BLIK_AUTO2;

    QImageLabelPoint(int x, int y, int type = 0, QColor color = QColor());
    explicit QImageLabelPoint();

    void setColor(const QColor& color);
    void setType(int point_type_const);

    QColor getColor() const;
    int getType() const;

signals:

public slots:

private:

    int    _type;
    QColor _color;

};

#endif // QIMAGELABELPOINT_H
