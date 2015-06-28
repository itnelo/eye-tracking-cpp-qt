#include "QImageListView.h"

QImageListView::QImageListView(QWidget *parent) :
    QListView(parent)
{}

void QImageListView::keyReleaseEvent(QKeyEvent* event)
{
    if (Qt::Key_Up == event->key() || Qt::Key_Down == event->key()) {
        emit clicked(currentIndex());
    }
}
