#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    block_count = 0;

    connect(ui->actionCombat, SIGNAL(triggered()), this, SLOT(addCombat()));
    connect(ui->actionDice_throw, SIGNAL(triggered()), this, SLOT(addDice_throw()));
    connect(ui->actionArena_select, SIGNAL(triggered()), this, SLOT(addArena_select()));
    connect(ui->actionItem_apply, SIGNAL(triggered()), this, SLOT(addItem_apply()));
    connect(ui->actionRest, SIGNAL(triggered()), this, SLOT(addRest()));

}

MainWindow::~MainWindow(){
    delete ui;
   /* for(int i; i < block_count; i++){
        delete blocks[i];
    }*/
}

void MainWindow::printHelp(){
    std::cout<<"HELP\n";
}

void MainWindow::addCombat(){
    MyLabel* ano = new MyLabel(this);
    connect(ano , SIGNAL(mousePress()), this, SLOT(mousePress()));
//    connect(ano , SIGNAL(mouseRelease(ano)), this, SLOT(mouseRelease(MyLabel* label)));
    ano->setGeometry(100,100,100,100);
    QPixmap pixmap(":combat.jpg");
    ano->setPixmap(pixmap);
    ano->show();

}

void MainWindow::addDice_throw(){
    label = new QLabel(this);
   // blocks[block_count] = label;
    block_count++;
    label->setGeometry(100,100,100,100);
    QPixmap pixmap(":dice.jpg");
    label->setPixmap(pixmap);
    label->show();
}

void MainWindow::addItem_apply(){
    label = new QLabel(this);
  //  blocks[block_count] = label;
    block_count++;
    label->setGeometry(100,200,100,100);
    QPixmap pixmap(":itemSelect.jpg");
    label->setPixmap(pixmap);
    label->show();
}

void MainWindow::addArena_select(){
    label = new QLabel(this);
  //SR  blocks[block_count] = label;
    block_count++;
    label->setGeometry(100,100,100,100);
    QPixmap pixmap(":arenaSelect.jpg");
    label->setPixmap(pixmap);
    label->show();
}

void MainWindow::addRest(){
    label = new QLabel(this);
 //   blocks[block_count] = label;
    block_count++;
    label->setGeometry(100,100,100,100);
    QPixmap pixmap(":rest.jpg");
    label->setPixmap(pixmap);
    label->show();
}

void MainWindow::mousePress(){
    //setMovingtrue();
    std::cout<<"ano\n";
}
/*
void MainWindow::mouseRelease(MyLabel* label){
    QPoint place = QCursor::pos();
    label->setGeometry(100, 100, place.x(), place.y());

}
*/



