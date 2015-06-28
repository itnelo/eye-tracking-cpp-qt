#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H

#include <QDialog>
#include <QMoveEvent>

namespace Ui {
class CaptureDialog;
}

class CaptureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CaptureDialog(QWidget *parent = 0);
    ~CaptureDialog();

    int currentPointNum();

protected:
    void moveEvent(QMoveEvent* e);
    void closeEvent(QCloseEvent* e);

signals:
    needCaptureImage();
    dialogClosed();

public slots:
    onPointClear();
    onPointResetPosition();
    onPointShow(int point_num);
    onPointNext();
    onPointPrev();
    onCaptureImage();

private:
    Ui::CaptureDialog *ui;
    int _current_point_num;
};

#endif // CAPTUREDIALOG_H
