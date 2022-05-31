#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "registrationwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include "QStyleFactory"
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QPalette p = qApp->palette();
    p.setColor(QPalette::Text, QColor(255,255,255));
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Base, QColor(35, 35, 35));
    p.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    p.setColor(QPalette::ToolTipBase, QColor(25, 25, 25));
    p.setColor(QPalette::ToolTipText, Qt::white);
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::PlaceholderText, Qt::gray);
    p.setColor(QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor(42, 130, 218));
    p.setColor(QPalette::Highlight, QColor(42, 130, 218));
    p.setColor(QPalette::HighlightedText, QColor(35, 35, 35));
    p.setColor(QPalette::Active, QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    p.setColor(QPalette::Disabled, QPalette::WindowText, Qt::darkGray);
    p.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    p.setColor(QPalette::Disabled, QPalette::Light, QColor(53, 53, 53));
    qApp->setPalette(p);

    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Kr3st1k/Documents/prakticheskiy-cringe/sqlite (1).db");
    if (!db.open())
    {
        QMessageBox pm;
        pm.setText("Failed to open connection.\nPlease put DB into correct directory.");
        pm.exec();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
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
            QSqlQuery query_;

            query_.prepare("SELECT password, role FROM polik_users WHERE login = :login");

            query_.bindValue(":login", login);

            if (!query_.exec()){
                QMessageBox pm;
                pm.setText(query_.lastError().text());
                pm.exec();
                ui->label->setText("Что-то произошло не так...");
                return;
            }

            if(query_.next())
            {

                QString passdb_ = query_.value(0).toString();

                if (passdb_.isEmpty())
                {
                    ui->label->setText("Неправильный логин или пароль");
                    return;
                }

                if(passdb_ == pass)
                {
                    QString role = query_.value(1).toString();
                    if (role == "Пациент")
                    {
                        tvp_ = new TableViewerPage(&db);
                        tvp_->show();
                    }
                    if (role == "")
                        ui->label->setText("noo");
                }
                else
                {
                    ui->label->setText("Неправильный логин или пароль");
                }
                return;

            }
        }

}


void MainWindow::on_pushButton_2_clicked()
{
    rp_ = new RegistrationWindow(&db);
    rp_->show();
}

