#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "QSqlQuery"
#include "databasetweaks.h"

#include <QMessageBox>
#include "QSqlError"

RegistrationWindow::RegistrationWindow(QSqlDatabase *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWindow),
    db_(db)
{
    ui->setupUi(this);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    QString p_fio = ui->lineEdit_3->text();
    QString p_address = ui->lineEdit_5->text();
    QString p_gender = ui->comboBox->currentText();

    if(p_gender.isEmpty())
    {
        ui->label->setText("Укажите пол");
        return;
    }

    QSqlQuery findPerson_;

    findPerson_.prepare("SELECT * FROM polik_users WHERE login = :lgn");

    findPerson_.bindValue(":lgn", login);

    if(!findPerson_.exec())
    {
        ui->label->setText("Что-то пошло не так");
        QMessageBox pm;
        pm.setText(findPerson_.lastError().text());
        pm.exec();
        return;
    }

    if(findPerson_.size() > 0)
    {
        ui->label->setText("Пользователь уже существует");
        return;
    }

    QSqlQuery findFio_("SELECT * FROM patients WHERE p_fio = '" + p_fio + "'");

    if (!findFio_.exec())
    {
        ui->label->setText("Something went wrong..");
        return;
    }

    if(findFio_.size() > 0)
    {
        ui->label->setText("Пользователь уже существует");
        return;
    }

    QSqlQuery query_;
    query_.prepare("INSERT INTO patients (p_fio, p_birthday, p_address, p_gender) VALUES (:fio, :bd, :address, :gender)");

        query_.bindValue(":fio", p_fio);
        query_.bindValue(":bd", ui->dateEdit->date().toString(Qt::ISODate));
        query_.bindValue(":address", p_address);
        query_.bindValue(":gender", p_gender);

    if(!query_.exec())
    {
        ui->label->setText("Something went wrong...");
        return;
    }

    QSqlQuery query2_;
    query2_.prepare("INSERT INTO polik_users (login, password, role) VALUES (:login, :pass, :role)");

    query2_.bindValue(":login", login);
    query2_.bindValue(":pass", pass);
    query2_.bindValue(":role", "Пациент");

    if(!query2_.exec())
    {
        ui->label->setText("Something went wrong...");
        return;
    }

    QMessageBox pm;
    pm.setText("Аккаунт успешно создан!");
    pm.exec();
    this->close();
}

