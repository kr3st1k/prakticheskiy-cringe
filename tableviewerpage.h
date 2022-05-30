#ifndef TABLEVIEWERPAGE_H
#define TABLEVIEWERPAGE_H

#include <QWidget>

namespace Ui {
class TableViewerPage;
}

class TableViewerPage : public QWidget
{
    Q_OBJECT

public:
    explicit TableViewerPage(QWidget *parent = nullptr);
    ~TableViewerPage();

private:
    Ui::TableViewerPage *ui;
};

#endif // TABLEVIEWERPAGE_H
