#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "QSqlQuery"
#include "databasetweaks.h"

#include <QMessageBox>
#include "QSqlError"

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/Users/kr3st1k/Documents/prakticheskiy-cringe/poliklinika.sqlite");
    if (!db.open())
    {
        QMessageBox pm;
        pm.setText("Failed to open connection.\nPlease put DB into correct directory.");
        pm.exec();
    }
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

    findPerson_.prepare("SELECT * FROM users");

    qInfo() << findPerson_.executedQuery();

    if(!findPerson_.exec())
    {
        ui->label->setText("Что-то пошло не так");
        QMessageBox pm;
        pm.setText(findPerson_.lastError().text());
        pm.exec();
        return;
    }

    if(findPerson_.size() != 0)
    {
        ui->label->setText("Пользователь уже существует");
        return;
    }

    QSqlQuery findFio_("SELECT * FROM patients WHERE p_fio = :fio");

    findFio_.bindValue(":fio", p_fio);

    if (!findFio_.exec() || findFio_.size() != 0)
    {
        ui->label->setText("Something went wrong..");
        return;
    }

    QSqlQuery query_("INSERT INTO patients (p_fio, p_birthday, p_address, p_gender) VALUES (:fio, :bd, :address, :gender)");

        query_.bindValue(":fio", p_fio);
        query_.bindValue(":bd", ui->dateEdit->date().toString(Qt::ISODate));
        query_.bindValue(":address", p_address);
        query_.bindValue(":gender", p_gender);

    if(!query_.exec())
    {
        ui->label->setText("Something went wrong...");
        return;
    }

    QSqlQuery query2_("INSERT INTO users (login, password, role, pa_id) VALUES (:login, :pass, :role, :pa_id");

    query2_.bindValue(":login", login);
    query2_.bindValue(":pass", pass);
    query2_.bindValue(":role", "Пациент");
    query2_.bindValue(":pa_id", 2);

    if(!query2_.exec())
    {
        ui->label->setText("Something went wrong...");
        return;
    }
}

