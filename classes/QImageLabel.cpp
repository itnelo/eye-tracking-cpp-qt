#include "QImageLabel.h"

const double QImageLabel::SCALE_FACTOR  = 1.1;

QImageLabel::QImageLabel(QWidget *parent) :
    QLabel(parent),
    _original(QPixmap()),
    _points_visible_mask(QImageLabelPoint::TYPE_PUPIL | QImageLabelPoint::TYPE_BLIK),
    _points(QMap<int, QImageLabelPoint>()),
    _current_point_type(QImageLabelPoint::TYPE_PUPIL),
    _scale_count(2)
{}

void QImageLabel::setPixmapOriginal(const QPixmap& pixmap)
{
    _original    = pixmap;
    _points      = QMap<int, QImageLabelPoint>();
    _scale_count = 2;

    renderView();
}

void QImageLabel::setPoint(const QImageLabelPoint& point)
{
    _points.insert(point.getType(), point);

    renderView();

    emit cordsSelected(point.x(), point.y(), point.getType());
}

void QImageLabel::changePointVisible(int point_const, bool visible_status)
{
    if (visible_status) {
        _points_visible_mask |= point_const;
    } else {
        if (_points_visible_mask & point_const) {
            _points_visible_mask ^= point_const;
        }
    }

    renderView();
}

void QImageLabel::setCurrentPointType(int point_type_const)
{
    _current_point_type = point_type_const;
}

bool QImageLabel::isPointVisible(int point_const)
{
    return _points_visible_mask & point_const;
}

void QImageLabel::renderScaled(QPixmap& _pixmap)
{
    if (0 >= _scale_count) {
        return;
    }

    double _final_scale_factor = qPow(QImageLabel::SCALE_FACTOR, _scale_count);

    QPixmap _scaled = _pixmap.scaled(_final_scale_factor * _pixmap.size(), Qt::KeepAspectRatio);

    int _resize_delta_x = (_scaled.width()  - (1.0 / _final_scale_factor) * _scaled.width())  / 2;
    int _resize_delta_y = (_scaled.height() - (1.0 / _final_scale_factor) * _scaled.height()) / 2;

    _pixmap = _scaled.copy(_resize_delta_x, _resize_delta_y, 320, 240);
}

void QImageLabel::renderPoints(QPixmap& _pixmap)
{
    if (_points.empty()) {
        return;
    }

    QMap<int, QImageLabelPoint>::const_iterator iter = _points.begin();
    for(; iter != _points.end(); ++iter) {
        if (!isPointVisible(iter.value().getType())) {
            continue;
        }

        renderPoint(_pixmap, iter.value());
    }
}

void QImageLabel::renderPoint(QPixmap& _pixmap, const QImageLabelPoint& _point)
{
    QImage src(_pixmap.toImage());

    QPainter p(&src);
    p.setPen(_point.getColor());

    QBrush brush(p.brush());
    brush.setColor(_point.getColor());
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);

    int _point_x = _point.x();
    int _point_y = _point.y();

    if (0 < _scale_count) {
        double _final_scale_factor  = qPow(QImageLabel::SCALE_FACTOR, _scale_count);
        int    _scaled_width        = 320 * _final_scale_factor;
        int    _scaled_height       = 240 * _final_scale_factor;

        _point_x = qCeil(_point_x * _scaled_width  / 320) - (_scaled_width  - 320) / 2;
        _point_y = qCeil(_point_y * _scaled_height / 240) - (_scaled_height - 240) / 2;
    }

    p.drawLine(QPointF(_point_x - 3,    _point_y)       , QPointF(_point_x + 3,     _point_y));
    p.drawLine(QPointF(_point_x,        _point_y - 3)   , QPointF(_point_x,         _point_y + 3));

    _pixmap = QPixmap::fromImage(src);
}

void QImageLabel::renderView()
{
    QPixmap _view(_original);

    renderScaled(_view);
    renderPoints(_view);

    setPixmap(_view);
}

void QImageLabel::mousePressEvent(QMouseEvent* event)
{
    int _real_x = event->x();
    int _real_y = event->y();

    if (0 < _scale_count) {
        double _final_scale_factor  = qPow(QImageLabel::SCALE_FACTOR, _scale_count);
        int    _scaled_width        = 320 * _final_scale_factor;
        int    _scaled_height       = 240 * _final_scale_factor;

        _real_x = qCeil(_real_x * 320 / _scaled_width)  + qCeil(((_scaled_width  - 320) / 2) * (1.0 / _final_scale_factor));
        _real_y = qCeil(_real_y * 240 / _scaled_height) + qCeil(((_scaled_height - 240) / 2) * (1.0 / _final_scale_factor));
    }

    _points[ _current_point_type ].setX(_real_x);
    _points[ _current_point_type ].setY(_real_y);

    setPoint(_points[ _current_point_type ]);
}

void QImageLabel::wheelEvent(QWheelEvent* event)
{
    if (0 < event->delta()) {

        if (20 <= _scale_count) {
            return;
        }

        ++_scale_count;
    } else {

        if (2 >= _scale_count) {
            return;
        }

        --_scale_count;
    }

    renderView();
}

