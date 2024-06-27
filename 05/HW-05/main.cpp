#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qssFile(":/qss/Style.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()) {
        QString qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
        qDebug() << "Can open";
    } else {
        qDebug() << "Can't open";
    }
    MainWindow w;
    w.show();
    return a.exec();
}
