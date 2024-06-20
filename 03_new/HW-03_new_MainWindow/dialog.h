#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void setData(const QString &text);

private slots:
    void on_pb_Close_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
