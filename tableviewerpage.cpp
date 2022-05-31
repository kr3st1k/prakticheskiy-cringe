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

    ui->comboBox->addItems({"Пациенты", "Доктора", "Назначения", "Диагнозы", "Пользователи"});
}

TableViewerPage::~TableViewerPage()
{
    delete ui;
}

QString getTableName(QString name)
{
    if (name == "Пациенты")
        return "patients";
    if (name == "Доктора")
        return "doctors";
    if (name == "Назначения")
        return "appointment";
    if (name == "Диагнозы")
        return "diagnose";
    if (name == "Пользователи")
        return "polik_users";
    return "";
}

void TableViewerPage::on_comboBox_currentIndexChanged(int index)
{
    if (index_ != index)
    {
        index_ = index;

        QSqlQueryModel *modal = new QSqlQueryModel();
        QSqlQuery query("select * from  " + getTableName(ui->comboBox->currentText()));

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

