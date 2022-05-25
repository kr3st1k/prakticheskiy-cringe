#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "loginpage.h"
#include <QtSql/QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    lp_ = new LoginPage(this);
    lp_->show();
    this->close();
}

