#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dialog(new CaptureDialog(this))
{
    ui->setupUi(this);

    connect(ui->nextPointButton,    &QPushButton::clicked,          dialog,     &CaptureDialog::onPointNext);
    connect(ui->prevPointButton,    &QPushButton::clicked,          dialog,     &CaptureDialog::onPointPrev);

    connect(ui->imageView,          &QImageLabel::cordsSelected,    this,       &MainWindow::receiveCords);

    connect(ui->modePupil,          &QRadioButton::clicked,         this,       &MainWindow::modeChanged);
    connect(ui->modeBlik,           &QRadioButton::clicked,         this,       &MainWindow::modeChanged);

    connect(ui->visibleA1P,         &QCheckBox::toggled,            this,       &MainWindow::algoPointVisibleChanged);
    connect(ui->visibleA1B,         &QCheckBox::toggled,            this,       &MainWindow::algoPointVisibleChanged);
    connect(ui->visibleA2P,         &QCheckBox::toggled,            this,       &MainWindow::algoPointVisibleChanged);
    connect(ui->visibleA2B,         &QCheckBox::toggled,            this,       &MainWindow::algoPointVisibleChanged);

    connect(dialog,                 &CaptureDialog::dialogClosed,   this,       &MainWindow::captureDialogClosed);

    childEventFilterSetup(this);

    dialog->installEventFilter(this);
    dialog->setModal(false);
}

MainWindow::~MainWindow()
{
    delete dialog;
    delete ui;
}

/*
 * @brief     Обработчик события нажатия кнопки захвата изображения с камеры
 *
 * @return    NULL
 *
 * По нажатию кнопки начинается захват изображения с камеры
 */
void MainWindow::on_captureStartBtn_clicked()
{
    // Нельзя начать захват изображения с камеры, если он уже был начат ранее.
    if( CameraManager::instance()->isRunning() )
        return;

    CameraManager::instance()->startCapture( ui->testLabel, ui->lineEditPupilCords, ui->textEditPupilCordsLog );
}

/*
 * @brief     Обработчик события нажатия кнопки отмены изображения с камеры
 *
 * @return    NULL
 *
 * По нажатию кнопки захват изображения с камеры отменяется
 */
void MainWindow::on_captureStopBtn_clicked()
{
    // Нельзя остановить захват изображения с камеры, если он не начинался.
    if( !CameraManager::instance()->isRunning() )
        return;

    CameraManager::instance()->stopCapture();
}

/*
 * @brief     Обработчик события нажатия кнопки сохранения изображения, захваченного с камеры
 *
 * @return    NULL
 *
 * По нажатию кнопки захват изображения с камеры отменяется
 */
void MainWindow::on_saveFrameBtn_clicked()
{
    // Сохранить можно только при активном процессе захвата изображения с камеры.
    if( !CameraManager::instance()->isRunning() )
        return;

    // Создать структуру файлов, если еще не создана.
    QDir dir_data("data/images");

    if (!dir_data.exists()) {
        dir_data.mkpath(".");
    }

    QFile db("data/data.csv");
    QFile last_image_id("data/last_image_id.txt");

    if (!last_image_id.exists()) {
        last_image_id.open(QIODevice::WriteOnly);
        QTextStream out1(&last_image_id);
        out1 << QString("1");
        last_image_id.close();
    }

    if (!db.exists()) {
        db.open(QIODevice::WriteOnly);
        QTextStream out2(&db);
        out2.setCodec("UTF-8");
        out2 << QString("IMAGE_ID; IMAGE_PATH; FIO; EYE_COLOR; DEEP_BROW; COSMETIC; GLASSES; DISTANCE; LIGHTING; VIEW_POINT_POSITION; PUPIL_MANUAL_X; PUPIL_MANUAL_Y; BLIK_MANUAL_X; BLIK_MANUAL_Y; PUPIL_AUTO1_X; PUPIL_AUTO1_Y; BLIK_AUTO1_X; BLIK_AUTO1_Y; PUPIL_AUTO2_X; PUPIL_AUTO2_Y; BLIK_AUTO2_X; BLIK_AUTO2_Y; TIME_AUTO1; TIME_AUTO2; EYE_SIGHT_INNACURACY\n");
        db.close();
    }

    CameraManager::instance()->saveShot();

    // Загрузить текущий ID изображения
    last_image_id.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in1(&last_image_id);
    int current_image_id = in1.readLine().toInt();
    last_image_id.close();

    int current_point_num = dialog->currentPointNum();

    // Сохраняем в базу результат опыта.
    db.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out3(&db);
    out3.setCodec("UTF-8");

    out3 << QString::number(current_image_id) + QString("; ");
    out3 << QString("data/images/") + QString::number(current_image_id) + ".jpg" + QString("; ");
    out3 << ui->ps_fio->text() + QString("; ");
    out3 << ui->ps_eye_color->currentText() + QString("; ");
    out3 << QString::number(ui->ps_deep_brow->isChecked() ? 1 : 0) + QString("; ");
    out3 << QString::number(ui->ps_cosmetic->isChecked() ? 1 : 0) + QString("; ");
    out3 << QString::number(ui->ps_glasses->isChecked() ? 1 : 0) + QString("; ");
    out3 << ui->ps_distance->text() + QString("; ");
    out3 << ui->ps_lighting->currentText() + QString("; ");
    out3 << QString::number(current_point_num) + QString("; ");

    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("; ");
    out3 << QString("");

    out3 << "\n";

    db.close();

    // Обновляем счетчик изображений.
    last_image_id.open(QIODevice::WriteOnly);
    QTextStream out4(&last_image_id);
    out4 << QString::number(++current_image_id);
    last_image_id.close();
}

void MainWindow::on_saveVideoStartBtn_clicked()
{
    // Начать запись видео файла можно только если активен захват изображения с камеры.
    if( !CameraManager::instance()->isRunning() )
        return;

    // Код для начала записи видео файла.
    CameraManager::instance()->videoSave( true );

    // Можно улучшить: Куда записывать новые видео файлы? ( определить константу в классе MyCamera ).
    // Можно улучшить: Определить поле, означающую что идет запись видео файла.
}

void MainWindow::on_saveVideoStopBtn_clicked()
{
    // Код для остановки записи видео файла.
    CameraManager::instance()->videoSave( false );
}

void MainWindow::on_execFilter_clicked()
{
    CameraManager::instance()->switchFilter( 1 );
}

void MainWindow::on_execFilter_3_clicked()
{
    CameraManager::instance()->switchFilter( 2 );
}

void MainWindow::on_execFilter_2_clicked()
{
    CameraManager::instance()->switchFilter( 3 );
}

void MainWindow::on_execFilter_4_clicked()
{
    CameraManager::instance()->switchFilter( 4 );
}

void MainWindow::on_checkBoxFace_toggled()
{
    CameraManager::instance()->switchDetectParam( 1 );
}

void MainWindow::on_checkBoxEyes_toggled()
{
    CameraManager::instance()->switchDetectParam( 2 );
}

void MainWindow::on_checkBoxNose_toggled()
{
    CameraManager::instance()->switchDetectParam( 3 );
}

void MainWindow::on_checkBoxMouth_toggled()
{
    CameraManager::instance()->switchDetectParam( 4 );
}

void MainWindow::on_checkBoxPupils_toggled()
{
    CameraManager::instance()->switchDetectParam( 5 );
}

void MainWindow::on_pushButtonUnsetPupilParams_clicked()
{
    ui->spinBoxPupilContours->setValue( 6 );
    ui->SpinBoxPupilAccuracy->setValue( 0.6f );
    ui->spinBoxPupilMinSquare->setValue( 30 );
    ui->spinBoxPupilMaxSquare->setValue( 500 );

    CameraManager::instance()->setPupilDetectParams( 6, 0.6, 30, 500 );
}

void MainWindow::on_pushButtonSetPupilParams_clicked()
{
    int pupil_contours   = ui->spinBoxPupilContours->value();
    int pupil_accuracy   = ui->SpinBoxPupilAccuracy->value();
    int pupil_min_square = ui->spinBoxPupilMinSquare->value();
    int pupil_max_square = ui->spinBoxPupilMaxSquare->value();

    CameraManager::instance()->setPupilDetectParams( pupil_contours, pupil_accuracy, pupil_min_square, pupil_max_square );
}

void MainWindow::on_pointsShowButton_clicked()
{
    if (dialog->isVisible()) {
        dialog->close();
        return;
    }

    dialog->onPointResetPosition();
    dialog->onPointClear();
    dialog->onPointNext();

    ui->nextPointButton->setEnabled(true);
    ui->prevPointButton->setEnabled(true);
    ui->collectImagesMode->setChecked(true);

    if (QApplication::screens().size() > 1) {
        dialog->setWindowState(Qt::WindowFullScreen);
        dialog->setGeometry(QGuiApplication::screens().last()->geometry());
    } else {
        dialog->setWindowState(Qt::WindowNoState);
    }

    dialog->show();
}

void MainWindow::on_updateImagesListBtn_clicked()
{
    // 1. Загрузить содержимое файла
    //QFile db("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/data.csv");
    QFile db("data/data.csv");

    if (!db.exists()) {
        qDebug() << "not exists";
        return;
    }

    db.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream db_reader(&db);
    QStringList string_list;

    while (!db_reader.atEnd()) {
        QString record = db_reader.readLine();
        QStringList parts = record.split(";");
        string_list << parts.at(1).trimmed();
    }

    db.close();

    string_list.removeAt(0);
    ui->imagesListView->setModel(new QStringListModel(string_list));
}

void MainWindow::on_imagesListView_clicked(const QModelIndex &index)
{
    QString image_path = index.data(Qt::DisplayRole).toString();
    //ui->imageView->setPixmapOriginal(QPixmap(QString("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/") + image_path));
    ui->imageView->setPixmapOriginal(image_path);

    int pupil_x, pupil_y, blik_x, blik_y;
    int pupil_auto1_x, pupil_auto1_y, pupil_auto2_x, pupil_auto2_y;
    int blik_auto1_x, blik_auto1_y, blik_auto2_x, blik_auto2_y;
    int record_index = index.row() + 1;
    int current_index = 0;

    //QFile db("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/data.csv");
    QFile db("data/data.csv");

    if (db.exists()) {
        db.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream db_stream(&db);

        while (!db_stream.atEnd()) {
            QString record = db_stream.readLine();

            if (record_index == current_index) {
                QStringList parts = record.split(";");
                pupil_x = parts.at(10).toInt();
                pupil_y = parts.at(11).toInt();
                blik_x  = parts.at(12).toInt();
                blik_y  = parts.at(13).toInt();

                pupil_auto1_x = parts.at(14).toInt();
                pupil_auto1_y = parts.at(15).toInt();

                blik_auto1_x = parts.at(16).toInt();
                blik_auto1_y = parts.at(17).toInt();

                pupil_auto2_x = parts.at(18).toInt();
                pupil_auto2_y = parts.at(19).toInt();

                blik_auto2_x = parts.at(20).toInt();
                blik_auto2_y = parts.at(21).toInt();

                break;
            }

            ++current_index;
        }
    }

    db.close();

    ui->imageView->setPoint(QImageLabelPoint(pupil_x, pupil_y, QImageLabelPoint::TYPE_PUPIL));
    ui->imageView->setPoint(QImageLabelPoint(blik_x,  blik_y,  QImageLabelPoint::TYPE_BLIK));

    if (0 < pupil_auto1_x && 0 < pupil_auto1_y) {
       ui->imageView->setPoint(QImageLabelPoint(pupil_auto1_x,  pupil_auto1_y,  QImageLabelPoint::TYPE_PUPIL_AUTO1));
    }

    if (0 < pupil_auto2_x && 0 < pupil_auto2_y) {
        ui->imageView->setPoint(QImageLabelPoint(pupil_auto2_x,  pupil_auto2_y,  QImageLabelPoint::TYPE_PUPIL_AUTO2));
    }

    if (0 < blik_auto1_x && 0 < blik_auto1_y) {
        ui->imageView->setPoint(QImageLabelPoint(blik_auto1_x,  blik_auto1_y,  QImageLabelPoint::TYPE_BLIK_AUTO1));
    }

    if (0 < blik_auto2_x && 0 < blik_auto2_y) {
        ui->imageView->setPoint(QImageLabelPoint(blik_auto2_x,  blik_auto2_y,  QImageLabelPoint::TYPE_BLIK_AUTO2));
    }
}

void MainWindow::receiveCords(int x, int y, int type)
{
    int f_offset_x, f_offset_y = 0;

    switch (type) {

        case QImageLabelPoint::TYPE_PUPIL:
            ui->pupilX->setValue(x);
            ui->pupilY->setValue(y);
            f_offset_x = 10;
            f_offset_y = 11;
            break;

        case QImageLabelPoint::TYPE_BLIK:
            ui->blikX->setValue(x);
            ui->blikY->setValue(y);
            f_offset_x = 12;
            f_offset_y = 13;
            break;

        default:
            return;

    }

    QModelIndex current_index = ui->imagesListView->currentIndex();
    int data_record_string_index = current_index.row() + 1;

    //QFile db("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/data.csv");
    QFile db("data/data.csv");

    if (!db.exists()) {
        qDebug() << "not exists";
        return;
    }

    int current_data_record_index = 0;
    db.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream db_stream(&db);
    QStringList string_list;

    while (!db_stream.atEnd()) {
        QString record = db_stream.readLine();

        if (data_record_string_index == current_data_record_index) {
            QStringList parts = record.split(";");
            parts.replace(f_offset_x, QString::number(x));
            parts.replace(f_offset_y, QString::number(y));
            record = parts.join(";");
        }

        string_list << record;
        ++current_data_record_index;
    }

    db.close();

    db.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    db_stream << string_list.join("\n") << "\n";
    db.close();
}

void MainWindow::on_pupilX_valueChanged(int x)
{
    ui->imageView->setPoint(QImageLabelPoint(x, ui->pupilY->value(), QImageLabelPoint::TYPE_PUPIL));
}

void MainWindow::on_pupilY_valueChanged(int y)
{
    ui->imageView->setPoint(QImageLabelPoint(ui->pupilX->value(), y, QImageLabelPoint::TYPE_PUPIL));
}

void MainWindow::on_blikX_valueChanged(int x)
{
    ui->imageView->setPoint(QImageLabelPoint(x, ui->blikY->value(), QImageLabelPoint::TYPE_BLIK));
}

void MainWindow::on_blikY_valueChanged(int y)
{
    ui->imageView->setPoint(QImageLabelPoint(ui->blikX->value(), y, QImageLabelPoint::TYPE_BLIK));
}

void MainWindow::modeChanged()
{
    if (ui->modeBlik->isChecked()) {
        ui->imageView->setCurrentPointType(QImageLabelPoint::TYPE_BLIK);
    } else if (ui->modePupil->isChecked()) {
        ui->imageView->setCurrentPointType(QImageLabelPoint::TYPE_PUPIL);
    }
}

void MainWindow::algoPointVisibleChanged()
{
    ui->imageView->changePointVisible(QImageLabelPoint::TYPE_PUPIL_AUTO1, ui->visibleA1P->isChecked());
    ui->imageView->changePointVisible(QImageLabelPoint::TYPE_PUPIL_AUTO2, ui->visibleA2P->isChecked());
    ui->imageView->changePointVisible(QImageLabelPoint::TYPE_BLIK_AUTO1, ui->visibleA1B->isChecked());
    ui->imageView->changePointVisible(QImageLabelPoint::TYPE_BLIK_AUTO2, ui->visibleA2B->isChecked());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if( CameraManager::instance()->isRunning() ) {
        CameraManager::instance()->stopCapture();
    }

    return QMainWindow::closeEvent(event);
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if (!ui->collectImagesMode->isChecked() || (event->type() != QEvent::KeyPress && event->type() != QEvent::KeyRelease)) {
        return QObject::eventFilter(object, event);
    }

    if (QEvent::KeyRelease == event->type()) {
        QKeyEvent* ke = static_cast<QKeyEvent*>(event);

        if (Qt::Key_Space == ke->key()) {
            MainWindow::on_saveFrameBtn_clicked();
            dialog->onPointNext();
        }

    }

    return true;
}

void MainWindow::childEventFilterSetup(QObject* object)
{
    QObjectList::const_iterator iter = object->children().begin();

    for (; iter != object->children().end(); ++iter) {
        if (!(*iter)->children().empty()) {
            childEventFilterSetup(*iter);
        }

        (*iter)->installEventFilter(this);
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Запуск алгоритма 1 по всем изображениям из data/images с сохранением координат в data/data.csv
    EyeFeaturesDetector* d = EyeFeaturesDetector::instance();
    //d->setPathData("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/data.csv");
    d->setPathData("data/data.csv");
    //d->setDirImages("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/images");
    d->setDirImages("data/images");
    d->setAlgo(new EyeFeaturesDetectorAlgorithm1());

    // @todo: progress bar processing.
    d->detect(EyeFeaturesDetector::MODE_DETECT_PUPIL | EyeFeaturesDetector::MODE_DETECT_BLIK);
    d->free();
}

void MainWindow::on_pushButton_2_clicked()
{
    // Запуск алгоритма 2 по всем изображениям из data/images с сохранением координат в data/data.csv
    EyeFeaturesDetector* d = EyeFeaturesDetector::instance();
    //d->setPathData("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/data.csv");
    d->setPathData("data/data.csv");
    //d->setDirImages("c:/Users/nelo/git/univer/ps3-camera-capture/build/debug/data/images");
    d->setDirImages("data/images");
    d->setAlgo(new EyeFeaturesDetectorAlgorithm2());

    // @todo: progress bar processing.
    d->detect(EyeFeaturesDetector::MODE_DETECT_PUPIL | EyeFeaturesDetector::MODE_DETECT_BLIK);
    d->free();
}

void MainWindow::captureDialogClosed()
{
    ui->collectImagesMode->setChecked(false);
    ui->nextPointButton->setEnabled(false);
    ui->prevPointButton->setEnabled(false);
}
