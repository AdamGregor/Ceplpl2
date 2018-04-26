#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include "mylabel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int block_count;
    QLabel *label;
   // QLabel *blocks[100];
    QPixmap image;

private slots:
    void printHelp();
    void addCombat();
    void addDice_throw();
    void addItem_apply();
    void addArena_select();
    void addRest();
    void mousePress();
   // void mouseRelease(MyLabel* label);
};

#endif // MAINWINDOW_H
