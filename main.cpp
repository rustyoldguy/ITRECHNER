//ITRechner main.cpp
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FitDimensions fd;
    fd.show();

    return a.exec();
}
