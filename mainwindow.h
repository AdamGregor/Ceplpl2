#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QGraphicsScene>
#include <QPen>
#include "mylabel.h"
#include "connection.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void checkPlacement(int* x, int* y);

private:
    int Spawn_x,Spawn_y;
    QGraphicsScene* scene;
    QPen* pen;
    connection* active_connection;
    Ui::MainWindow *ui;
    int block_count;

private slots:
    void printHelp();
    void addCombat();
    void addDice_throw();
    void addItem_apply();
    void addArena_select();
    void addRest();
    void mouseRelease(MyLabel* block);
    void mousePress(MyLabel* block);
};

#endif // MAINWINDOW_H
