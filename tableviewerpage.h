#ifndef TABLEVIEWERPAGE_H
#define TABLEVIEWERPAGE_H

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

private:
    Ui::TableViewerPage *ui;
    int index_ = -1;
    QSqlDatabase *db_;
};

#endif // TABLEVIEWERPAGE_H
