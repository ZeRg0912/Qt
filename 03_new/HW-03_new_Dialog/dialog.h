#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>

#include "infowindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

    void on_pb_Connect_clicked();

private:
    Ui::Dialog *ui;
    infoWindow* InfoWIndow = new infoWindow(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
};
#endif // DIALOG_H
