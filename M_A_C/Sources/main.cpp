/**
 *  @file    media.cpp
 *  @author  Francisco Calleja Vazquez (4k1x)
 *  @date    12/05/2018
 *  @version 1.0
 *
 */
#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

