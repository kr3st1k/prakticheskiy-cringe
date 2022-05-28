#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "loginpage.h"
#include "registrationwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    lp_ = new LoginPage();
    lp_->show();

}


void MainWindow::on_pushButton_2_clicked()
{
    rp_ = new RegistrationWindow();
    rp_->show();
}

