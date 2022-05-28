#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegistrationWindow *ui;
    QSqlDatabase db;
};

#endif // REGISTRATIONWINDOW_H
