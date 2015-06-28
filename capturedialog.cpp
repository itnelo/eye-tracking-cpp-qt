#include "capturedialog.h"
#include "ui_capturedialog.h"
#include "classes/cameramanager.h"

#include <QApplication>
#include <QDesktopWidget>

CaptureDialog::CaptureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaptureDialog),
    _current_point_num(0)
{
    ui->setupUi(this);

    //connect(this, &CaptureDialog::needCaptureImage, &CameraManager::instance(), &CameraManager::doCaptureImage);
}

CaptureDialog::~CaptureDialog()
{
    delete ui;
}

int CaptureDialog::currentPointNum()
{
    return _current_point_num;
}

void CaptureDialog::moveEvent(QMoveEvent* e)
{
    e->ignore();
}

void CaptureDialog::closeEvent(QCloseEvent* e)
{
    emit dialogClosed();
    return QDialog::closeEvent(e);
}

CaptureDialog::onPointClear()
{
    foreach (QLabel* label, findChildren<QLabel*>()) {
        label->setVisible(false);
    }
}

CaptureDialog::onPointResetPosition()
{
    _current_point_num = 0;
}

CaptureDialog::onPointShow(int point_num)
{
    QLabel* label = findChild<QLabel*>("point" + QString::number(point_num));
    label->setVisible(true);
}

CaptureDialog::onPointNext()
{
    onPointClear();

    if (9 < ++_current_point_num) {
        _current_point_num = 1;
    }

    onPointShow(_current_point_num);
}

CaptureDialog::onPointPrev()
{
    onPointClear();

    if (1 > --_current_point_num) {
        _current_point_num = 9;
    }

    onPointShow(_current_point_num);
}

CaptureDialog::onCaptureImage()
{
    emit needCaptureImage();
}
