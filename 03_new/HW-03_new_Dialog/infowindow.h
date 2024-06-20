#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QDialog>

namespace Ui {
class infoWindow;
}

class infoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit infoWindow(QWidget *parent = nullptr);
    ~infoWindow();
    void setData(const QString &text);

private slots:
    void on_pb_Close_clicked();

private:
    Ui::infoWindow *ui;
};

#endif // INFOWINDOW_H
