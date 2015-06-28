#ifndef MYCAMERACAPTURE_H
#define MYCAMERACAPTURE_H

#include <QObject>
#include <QThread>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPixmap>

#include <classes/CameraCaptureWorker.h>

class CameraManager : public QObject
{
    Q_OBJECT

public:    
    ~CameraManager();

    // Шаблон одиночка, класс управления камерой имеет только один экземпляр.
    static CameraManager* instance() {
        static CameraManager instance;
        return &instance;
    }

    // Возвращает статус состояния камеры ( активен/не активен захват ).
    bool isRunning();

    // Начало захвата изображения с камеры.
    bool startCapture(QLabel* label_ptr, QLineEdit* edit_ptr, QTextEdit *tedit_ptr );

    // Запись видеофайла ( true - начать, false - остановить ).
    void videoSave( bool set_status );

    // Сохранить изображение в файл.
    void saveShot();

    // Управление фильтрами во время захвата изображения.
    void switchFilter( const int filter_id );

    // Управление детектирование частей лица во время захвата изображения.
    void switchDetectParam( const int detect_param_id );

    // Управление параметрами детектирования зрачка.
    void setPupilDetectParams( int pupil_contours, int pupil_accuracy, int pupil_min_square, int pupil_max_square );

public slots:
    void drawImage( QImage );
    void viewMessage( QString );

    // Завершение захвата изображения с камеры.
    void stopCapture();

signals:
    void stopCaptureThread();
    void switchFilterCommand( const int );
    void switchDetectParamCommand( const int );
    void videoSaveCommand( bool );
    void saveShotCommand();
    void setPupilDetectParamsCommand( int, int, int, int );

private:
    CameraManager(){}
    CameraManager( const CameraManager& );
    CameraManager& operator = ( const CameraManager& );

    void addCaptureThread();

private:
    bool       running_status;
    QLabel*    draw_label;
    QLineEdit* edit_cords;
    QTextEdit* tedit_cords;
};

#endif // MYCAMERACAPTURE_H
