#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H

#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtCore/qmath.h>
#include <QtWidgets/QLabel>
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <classes/QImageLabelPoint.h>

class QImageLabel : public QLabel
{
    Q_OBJECT

public:

    static const double SCALE_FACTOR;

    explicit QImageLabel(QWidget *parent = 0);

    void setPixmapOriginal(const QPixmap& pixmap);
    void setPoint(const QImageLabelPoint& point);
    void changePointVisible(int point_const, bool visible_status);
    void setCurrentPointType(int point_type_const);

    bool isPointVisible(int point_const);

protected:
    void mousePressEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);

signals:
    cordsSelected(int x, int y, int type);

public slots:

private:
    void renderScaled(QPixmap& _pixmap);
    void renderPoints(QPixmap& _pixmap);
    void renderPoint(QPixmap& _pixmap, const QImageLabelPoint& _point);
    void renderView();

private:
    QPixmap                     _original;
    QMap<int, QImageLabelPoint> _points;
    int                         _points_visible_mask;
    int                         _current_point_type;
    int                         _scale_count;
};

#endif // QIMAGELABEL_H
