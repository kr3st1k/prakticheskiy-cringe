#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "QSqlQuery"
#include "QRegularExpression"

#include <QMessageBox>
#include "QSqlError"
#include "utils.h"

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
    QString login = ui->login->text();
    QString pass = ui->password->text();
    QString p_fio = ui->fio->text();
    QString p_address = ui->address->text();
    QString p_gender = ui->genderBox->currentText();
    Utils utils;

    if (login.isEmpty())
    {
        ui->label->setText("Укажите логин");
        return;
    }

    if (pass.isEmpty())
    {
        ui->label->setText("Укажите пароль");
        return;
    }


    if (!utils.checkPassword(pass))
    {
        QMessageBox::warning(this, "Неправильный формат пароля", "Пароль должен иметь:\nРазмер от 8 до 16\nХотя бы одну заглавную букву\nХотя бы одну маленькую букву\nХотя бы одну цифру");
        return;
    }

    QStringList p_fioList = p_fio.trimmed().split(" ");

    if(p_fio.isEmpty() || p_fioList.size() != 3)
    {
        ui->label->setText("Укажите ФИО");
        return;
    }

    if(p_address.isEmpty())
    {
        ui->label->setText("Укажите адрес");
        return;
    }

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
        ui->label->setText("Что-то пошло не так");
        return;
    }

    if(findFio_.size() > 0)
    {
        ui->label->setText("Пользователь уже существует");
        return;
    }

    QSqlQuery query_;
    query_.prepare("INSERT INTO patients (p_id, p_fio, p_birthday, p_address, p_gender) VALUES (:pid, :fio, :bd, :address, :gender)");

        query_.bindValue(":pid", utils.createReqIdText(p_fio.split(" "), ui->bdDate->date()));
        query_.bindValue(":fio", p_fio);
        query_.bindValue(":bd", ui->bdDate->date().toString(Qt::ISODate));
        query_.bindValue(":address", p_address);
        query_.bindValue(":gender", p_gender);

    if(!query_.exec())
    {
        ui->label->setText("Что-то пошло не так");
        return;
    }

    QSqlQuery query2_;
    query2_.prepare("INSERT INTO polik_users (login, password) VALUES (:login, :pass)");

    query2_.bindValue(":login", login);
    query2_.bindValue(":pass", pass);

    if(!query2_.exec())
    {
        ui->label->setText("Что-то пошло не так");
        return;
    }

    QMessageBox::information(this, "Поздравляем!", "Аккаунт успешно создан!");
    this->close();
}

