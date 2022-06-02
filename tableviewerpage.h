#ifndef TABLEVIEWERPAGE_H
#define TABLEVIEWERPAGE_H

#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QWidget>
#include <qsqldatabase.h>

namespace Ui {
class TableViewerPage;
}

class TableViewerPage : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewerPage(QSqlDatabase *db, QWidget *parent = nullptr);
    ~TableViewerPage();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_exitButton_clicked();

    void on_addButton_clicked();

    void on_checkBox_clicked(bool checked);

    void on_removeButton_clicked();

    void on_saveButton_clicked();

    void on_printButton_clicked();

    QString getColomnNames();

    void on_outputToFile_clicked();

    void on_loadFromFile_clicked();

private:
    Ui::TableViewerPage *ui;
    int index_ = -1;
    QSqlTableModel *modal_;
    QSqlDatabase *db_;
};

#endif // TABLEVIEWERPAGE_H
