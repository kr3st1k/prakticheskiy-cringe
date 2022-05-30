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
    explicit RegistrationWindow(QSqlDatabase *db, QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::RegistrationWindow *ui;
    QSqlDatabase *db_;
};

#endif // REGISTRATIONWINDOW_H
