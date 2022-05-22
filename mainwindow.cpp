#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
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

