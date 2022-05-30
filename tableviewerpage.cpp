#include "tableviewerpage.h"
#include "ui_tableviewerpage.h"

TableViewerPage::TableViewerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableViewerPage)
{
    ui->setupUi(this);
}

TableViewerPage::~TableViewerPage()
{
    delete ui;
}
