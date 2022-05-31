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

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    QString getColomnNames();

private:
    Ui::TableViewerPage *ui;
    int index_ = -1;
    QSqlTableModel *modal_;
    QSqlDatabase *db_;
};

#endif // TABLEVIEWERPAGE_H
