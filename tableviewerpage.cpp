#include "tableviewerpage.h"
#include "ui_tableviewerpage.h"

#include "QSqlQueryModel"
#include "QSqlQuery"
#include "QDebug"
#include "QDialog"
#include "QPrinter"
#include "QPrintDialog"
#include "QFileDialog"
#include "QSqlRecord"

#include <QFile>
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
            ui->saveButton->setEnabled(true);
        });

        ui->tableView->resizeColumnsToContents();

    }
}

void TableViewerPage::on_exitButton_clicked()
{
    QCoreApplication::quit();
}


void TableViewerPage::on_addButton_clicked()
{

    modal_->insertRow(modal_->rowCount(QModelIndex()));
    ui->saveButton->setEnabled(true);
}


void TableViewerPage::on_checkBox_clicked(bool checked)
{
    ui->tableView->setSortingEnabled(checked);
}


void TableViewerPage::on_removeButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "А вы точно уврены?", "Вы точно хотите удалить строку?",
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        modal_->removeRows(ui->tableView->currentIndex().row(), 1);
        ui->saveButton->setEnabled(true);
    }
}

void TableViewerPage::on_saveButton_clicked()
{
    modal_->submitAll();
    ui->saveButton->setEnabled(false);
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

void TableViewerPage::on_printButton_clicked()
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


void TableViewerPage::on_outputToFile_clicked()
{
    QString file_text;
    QString table_name = getTableName(ui->comboBox->currentText());
    QSqlQuery query("SELECT * FROM " + table_name);

    file_text = table_name + "\n";

    while (query.next()) {
        for (int i = 0; i < modal_->rowCount() + 1; i++) {
            file_text += query.value(i).toString() + ";";
        }
        file_text += "\n";
    }

    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save table info"), "",
            tr("Table Info (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else
    {
        const QString qPath(fileName);
        QFile qFile(qPath);
        if (qFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&qFile);
            out << file_text;
            qFile.close();
        }
        else
        {
            QMessageBox::warning(this, "Нет доступа к файлу", "Файл невозможно записать");
        }
    }

}


void TableViewerPage::on_loadFromFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open table info"), "",
            tr("Table info (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {

        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            QString table_name = in.readLine();
            if (table_name != getTableName(ui->comboBox->currentText()))
            {
                QMessageBox::warning(this, "Неправильная таблица", "Эти данные подходят только для таблицы " + getTableName(ui->comboBox->currentText()));
            }

            while (!in.atEnd())
            {
              QString line = in.readLine();
              QStringList list = line.split(";");
              QSqlRecord newRecord = modal_->record();

              for (int i = 0; i < list.size() - 1; i++)
              {
                  newRecord.setValue(i, list[i]);
              }

              modal_->insertRecord(modal_->rowCount(), newRecord);

            }
            file.close();
        }
        else
        {
            QMessageBox::warning(this, "Нет доступа к файлу", "Файл невозможно прочитать");
        }
    }
}

