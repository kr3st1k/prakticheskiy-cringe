#include "mainwindow.h"

#include <QApplication>

#include "testutils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTest::qExec(new TestUtils(), argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
