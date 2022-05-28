#include "loginpage.h"
#include "ui_loginpage.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("poliklinika.sqlite");
    if (!db.open())
    {
        QMessageBox pm;
        pm.setText("Failed to open connection.\nPlease put DB into correct directory.");
        pm.exec();
    }
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    if(login.isEmpty())
    {
        ui->label->setText("Вы не ввели логин");
        return;
    }
    else if (pass.isEmpty())
    {
        ui->label->setText("Вы не ввели пароль");
        return;
    }
    else
    {
        QSqlQuery query_("SELECT password FROM users WHERE login = :lgn");
        query_.bindValue(":lgn", login);
        if (!query_.exec()){
            QMessageBox pm;
            pm.setText(query_.lastError().text());
            pm.exec();
            ui->label->setText("Что-то произошло не так...");
            return;
        }

        if (query_.size() == 0)
        {
            ui->label->setText("Не найден пользователь");
            return;
        }

        QString passdb_ = query_.value(0).toString();

        if(passdb_ == pass)
            ui->label->setText("Чел харош!");
        return;


    }
}

