#include <QApplication>
#include <QtCore/QException>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    } catch (const QException& e) {
        return 0;
    }
}
