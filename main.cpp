/**
 *@file main.cpp
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief main of app
 */

#include "mainwindow.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
