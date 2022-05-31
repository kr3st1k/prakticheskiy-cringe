#include "tableviewerpage.h"
#include "ui_tableviewerpage.h"

#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QDebug"
#include "QDialog"
#include "QPrinter"
#include "QPrintDialog"

#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>
#include <QTextDocument>

TableViewerPage::TableViewerPage(QSqlDatabase *db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewerPage),
   db_(db)
{
    ui->setupUi(this);

    modal_ = new QSqlTableModel();

    ui->comboBox->addItems({"Пациенты", "Доктора", "Назначения", "Диагнозы", "Пользователи"});

    ui->tableView->horizontalHeader()->setSectionsClickable(1);

    ui->tableView->setEditTriggers (QAbstractItemView::AnyKeyPressed |
    QAbstractItemView::DoubleClicked);
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

        modal_->setTable(getTableName(ui->comboBox->currentText()));
        modal_->setEditStrategy(QSqlTableModel::OnManualSubmit);
        modal_->select();

        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(modal_);
        proxyModel->setSourceModel(modal_);
        ui->tableView->setModel(modal_);

        connect(
         modal_,
         &QSqlTableModel::dataChanged, this,
         [this]
        {
            ui->pushButton_7->setEnabled(true);
        });

    }
}

void TableViewerPage::on_pushButton_5_clicked()
{
    QCoreApplication::quit();
}


void TableViewerPage::on_pushButton_clicked()
{

    modal_->insertRow(modal_->rowCount(QModelIndex()));
    ui->pushButton_7->setEnabled(true);
}


void TableViewerPage::on_checkBox_clicked(bool checked)
{
    ui->tableView->setSortingEnabled(checked);
}


void TableViewerPage::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "А вы точно уврены?", "Вы точно хотите удалить строку?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        modal_->removeRows(ui->tableView->currentIndex().row(), 1);
        ui->pushButton_7->setEnabled(true);
    }
}

void TableViewerPage::on_pushButton_7_clicked()
{
    modal_->submitAll();
    ui->pushButton_7->setEnabled(false);
}

QString TableViewerPage::getColomnNames()
{
    QString headers;
    for(int i = 0; i < ui->tableView->model()->columnCount(); i++)
    {
      headers += "<td>" + ui->tableView->model()->headerData(i, Qt::Horizontal).toString() + "</td>";
    }
    return headers;
}

void TableViewerPage::on_pushButton_2_clicked()
{
    // Вывод таблиц на печать
    QPrinter *pr = new QPrinter();
    QPrintDialog dlg(pr, this);
    QSqlQuery query("SELECT * FROM " + getTableName(ui->comboBox->currentText()));
    QString html =  "<table border = '1'>"
                        "<h1>" + ui->comboBox->currentText() +"</h1>"
                        "<tbody>"
                             "<tr>"
                                "" + getColomnNames() + ""
                             "</tr>";
    while (query.next()) {
        html += "<tr>";
        for (int i = 0; i < modal_->rowCount() + 1; i++) {
            html += "<td>" + query.value(i).toString() + "</td>";
        }
        html += "</tr> \n";
    }
    html += "\n </table>";
    if (dlg.exec() == QDialog::Accepted) {
        QTextDocument doc;
        doc.setHtml(html);
        doc.print(pr);
        delete pr;
    }
}

