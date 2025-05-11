#include "mainwindow.h"
#include "beginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    BeginWindow bw;
    bw.show();
    return a.exec();
}
