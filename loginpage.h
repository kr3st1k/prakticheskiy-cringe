#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QSqlDatabase>
#include <QWidget>

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginPage *ui;
    QSqlDatabase db;
};

#endif // LOGINPAGE_H
