#include "tableviewerpage.h"
#include "ui_tableviewerpage.h"

#include "QSqlQueryModel"
#include "QSqlQuery"

#include <QMessageBox>

TableViewerPage::TableViewerPage(QSqlDatabase *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewerPage),
    db_(db)
{
    ui->setupUi(this);
}

TableViewerPage::~TableViewerPage()
{
    delete ui;
}

void TableViewerPage::on_comboBox_currentIndexChanged(int index)
{
    if (index_ != index)
    {
        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery query;

        index = index_;

        query.prepare("select * from patients");

        if(!query.exec())
        {
            QMessageBox pm;
            pm.setText("Something went wrong");
            pm.exec();
        }

        modal->setQuery(std::move(query));
        ui->tableView->setModel(modal);

        qDebug() << modal->rowCount();
    }
}

