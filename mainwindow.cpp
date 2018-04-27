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
//#include <QGraphicsLineItem>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    block_count = 0;
    this->Spawn_x = 12;
    this->Spawn_y = 67;

    connect(ui->actionCombat, SIGNAL(triggered()), this, SLOT(addCombat()));
    connect(ui->actionDice_throw, SIGNAL(triggered()), this, SLOT(addDice_throw()));
    connect(ui->actionArena_select, SIGNAL(triggered()), this, SLOT(addArena_select()));
    connect(ui->actionItem_apply, SIGNAL(triggered()), this, SLOT(addItem_apply()));
    connect(ui->actionRest, SIGNAL(triggered()), this, SLOT(addRest()));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::printHelp(){
    std::cout<<"HELP\n";
   // QGraphicsLineItem* item;
  //  item->
}

void MainWindow::addCombat(){
    MyLabel* block = new MyLabel(this);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":combat.gif");
    block->setPixmap(pixmap);
    block->show();

}

void MainWindow::addDice_throw(){
    MyLabel* block = new MyLabel(this);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":dice.png");
    block->setPixmap(pixmap);
    block->show();
}

void MainWindow::addItem_apply(){
    MyLabel* block = new MyLabel(this);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":itemSelect.gif");
    block->setPixmap(pixmap);
    block->show();
}

void MainWindow::addArena_select(){
    MyLabel* block = new MyLabel(this);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":arenaSelect.gif");
    block->setPixmap(pixmap);
    block->show();
}

void MainWindow::addRest(){
    MyLabel* block = new MyLabel(this);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":rest.gif");
    block->setPixmap(pixmap);
    block->show();
}


void MainWindow::mouseRelease(MyLabel* block){
    QPoint place;
    place = this->mapFromGlobal(QCursor::pos());
    int x = place.x();
    int y = place.y();
    x -= 50;
    y -= 50;
    checkPlacement(&x, &y);
    block->setGeometry(x,y,100,100);

}


void MainWindow::checkPlacement(int* x, int* y){
    if(*x < 12){         //12 -> hranice povoleneho okna, 50 -> polovina bloku
        *x = 12;
    }

    if(*y < 67){
        *y = 67;
    }

    return;
}






























