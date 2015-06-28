#ifndef QIMAGELISTVIEW_H
#define QIMAGELISTVIEW_H

#include <QListView>
#include <QtGui/QKeyEvent>

class QImageListView : public QListView
{
    Q_OBJECT
public:
    explicit QImageListView(QWidget *parent = 0);

signals:

public slots:

protected:
    void keyReleaseEvent(QKeyEvent* event);

};

#endif // QIMAGELISTVIEW_H
