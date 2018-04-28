#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"
#include "connection.h"

#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QPixmap>

#include <QDebug>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsLineItem>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);


    QGraphicsLineItem* item = new QGraphicsLineItem;
    item->setLine(0,0,1,1);
    scene->addItem(item);

    pen = new QPen;
    pen->setWidth(4);

    block_count = 0;
    active_connection = NULL;
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
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
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
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
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
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
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
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
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
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
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
    block->setCoords(x, y);
    block->setGeometry(x,y,100,100);

    connection* ptr = block->getOutptr();
    if(ptr != NULL){
       block->getCoords(&x, &y);
       ptr->setOutcoords(&x, &y);
       ptr->getOutcoords(&x, &y);
       ptr->setLine(x,y,500,500);
    }

}


void MainWindow::checkPlacement(int* x, int* y){
    if(*x < 12){         //12 -> hranice povoleneho okna, 50 -> polovina bloku
        *x = 12;
    }
    else if(*x+110 > this->size().width())
        *x = this->size().width() - 111;

    if(*y < 67){
        *y = 67;
    }
    else if(*y+110 > this->size().height()){
        *y = this->size().height() - 111;
    }

    return;
}

void MainWindow::mousePress(MyLabel *block){
    int x;
    int y;
    if(active_connection){
        if(active_connection->getNumOfClicks() == 2){
            active_connection = new connection;
            block->setOutconnection(active_connection);
            active_connection->setOutblock(block);
            block->getCoords(&x, &y);
            active_connection->setOutcoords(&x, &y);
            active_connection->incNumOfClicks();

        }
        else{
            if(block == active_connection->getOutBlock())
                return;

            block->setInconnection(active_connection);
            active_connection->setInblock(block);
            int g,h;
            active_connection->getOutcoords(&g,&h);
            block->getCoords(&x, &y);
            active_connection->setPen(*pen);
            active_connection->setLine(g,h,x+50,y);
            scene->addItem(active_connection);
            active_connection->incNumOfClicks();
        }
    }

    else{
        active_connection = new connection();
        block->setOutconnection(active_connection);
        active_connection->setOutblock(block);
        block->getCoords(&x, &y);
        active_connection->setOutcoords(&x, &y);
        active_connection->incNumOfClicks();
    }
}

























