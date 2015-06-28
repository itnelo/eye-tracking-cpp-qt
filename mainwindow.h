#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QDir>

#include <classes/CameraManager.h>
#include <classes/EyeFeaturesDetector.h>
#include <classes/EyeFeaturesDetectorAlgorithm1.h>
#include <classes/EyeFeaturesDetectorAlgorithm2.h>
#include <capturedialog.h>

#include <QtGui/QScreen>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_captureStartBtn_clicked();

    void on_captureStopBtn_clicked();

    void on_saveFrameBtn_clicked();

    void on_saveVideoStartBtn_clicked();

    void on_saveVideoStopBtn_clicked();

    void on_execFilter_clicked();

    void on_execFilter_3_clicked();

    void on_execFilter_2_clicked();

    void on_execFilter_4_clicked();

    void on_checkBoxFace_toggled();

    void on_checkBoxEyes_toggled();

    void on_checkBoxNose_toggled();

    void on_checkBoxMouth_toggled();

    void on_checkBoxPupils_toggled();

    void on_pushButtonUnsetPupilParams_clicked();

    void on_pushButtonSetPupilParams_clicked();

    void on_pointsShowButton_clicked();

    void on_updateImagesListBtn_clicked();

    void on_imagesListView_clicked(const QModelIndex &index);

    void receiveCords(int x, int y, int type);

    void on_pupilX_valueChanged(int x);

    void on_pupilY_valueChanged(int y);

    void on_blikX_valueChanged(int x);

    void on_blikY_valueChanged(int y);

    void modeChanged();

    void algoPointVisibleChanged();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:

    void captureDialogClosed();

protected:

    void closeEvent(QCloseEvent* event);
    bool eventFilter(QObject* object, QEvent* event);

private:

    void childEventFilterSetup(QObject* object);

private:
    Ui::MainWindow* ui;
    CaptureDialog* dialog;
};

#endif // MAINWINDOW_H
