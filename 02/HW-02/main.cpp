#include <QCoreApplication>
#include "header.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Network
    QHostInfo info = QHostInfo::fromName("qt-project.org");
    QString name = info.hostName();
    qDebug() << name;
    qDebug() << QHostInfo::localHostName();

    // SQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("test-db");
    db.setUserName("postgres");
    db.setPassword("Zerg0912");
    bool ok = db.open();
    qDebug() << ok;
    return a.exec();
}
