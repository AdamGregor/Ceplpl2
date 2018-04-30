/**
 *@file mainwindow.cpp
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief mainwindow of app
 */

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
#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>


#include <QMessageBox>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BlockEditor");
    scene = new QGraphicsScene;
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);

    QGraphicsLineItem* item = new QGraphicsLineItem;
    item->setLine(0,0,0.01,0.01);
    scene->addItem(item);

    pen = new QPen;
    pen->setWidth(4);

    blocks_ID = 0;
    active_connection = NULL;
    this->blocks = new BlockList;
    this->Spawn_x = 12;
    this->Spawn_y = 67;

    connect(ui->actionCombat, SIGNAL(triggered()), this, SLOT(addCombat()));
    connect(ui->actionDice_throw, SIGNAL(triggered()), this, SLOT(addDice_throw()));
    connect(ui->actionArena_select, SIGNAL(triggered()), this, SLOT(addArena_select()));
    connect(ui->actionItem_apply, SIGNAL(triggered()), this, SLOT(addItem_apply()));
    connect(ui->actionRest, SIGNAL(triggered()), this, SLOT(addRest()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(printHelp()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newScheme()));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::addCombat(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    blocks_ID++;
    block->setType(COMBAT);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    block->setStyleSheet("QLabel { background-color : red;}");
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":combat.gif");
    block->setPixmap(pixmap);
    block->show();
    blocks->insert(block);

}

void MainWindow::addDice_throw(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    blocks_ID++;
    block->setType(DICE);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":dice.png");
    block->setPixmap(pixmap);
    block->show();
    blocks->insert(block);
}

void MainWindow::addItem_apply(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    blocks_ID++;
    block->setType(ITEM);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":itemSelect.gif");
    block->setPixmap(pixmap);
    block->show();
    blocks->insert(block);
}

void MainWindow::addArena_select(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    blocks_ID++;
    block->setType(ARENA);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":arenaSelect.gif");
    block->setPixmap(pixmap);
    block->show();
    blocks->insert(block);
}

void MainWindow::addRest(){
    MyLabel* block = new MyLabel(this);
    block->setID(blocks_ID);
    blocks_ID++;
    block->setType(REST);
    connect(block , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
    connect(block, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
    connect(block, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
    block->setGeometry(Spawn_x,Spawn_y,100,100);
    block->setCoords(Spawn_x, Spawn_y);
    Spawn_x +=10;
    Spawn_y +=10;
    QPixmap pixmap(":rest.gif");
    block->setPixmap(pixmap);
    block->show();
    blocks->insert(block);
}


void MainWindow::mouseRelease(MyLabel* block){
    if(ui->actionDelete->isChecked())
        return;

    QPoint place;
    place = this->mapFromGlobal(QCursor::pos());
    int x = place.x();
    int y = place.y();
    x -= 50;
    y -= 50;
    checkPlacement(&x, &y);
    block->setCoords(x, y);
    block->setGeometry(x,y,100,100);

    connectionList* out = block->getOutList();
    connectionList* in = block->getInList();

    if(out->getListLenght() != 0){               // posuny spoju s out porty
        ListItem* out_port = out->getFirst();
        for(int i = 0; i < out->getListLenght(); i++){
            block->getCoords(&x, &y);
            out_port->data->setOutcoords(&x, &y);
            out_port->data->getOutcoords(&x, &y);
            int g, h;
            out_port->data->getIncoords(&g, &h);
            out_port->data->setLine(x ,y, g, h);
            out_port = out_port->next;
        }
    }

    if(in->getListLenght() != 0){                   // posuny spoju s in porty
        ListItem* in_port = in->getFirst();
        for(int i = 0; i < in->getListLenght(); i++){
            int g, h;
            block->getCoords(&g, &h);
            in_port->data->setIncoords(&g, &h);
            in_port->data->getIncoords(&g, &h);
            in_port->data->getOutcoords(&x, &y);
            in_port->data->setLine(x, y, g, h);
            in_port = in_port->next;
        }
    }
}


void MainWindow::checkPlacement(int* x, int* y){
    if(*x < 12){         //12 -> hranice povoleneho okna
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
            active_connection->setOutblock(block);
            block->getCoords(&x, &y);
            active_connection->setOutcoords(&x, &y);
            active_connection->incNumOfClicks();

        }
        else{
            if(block == active_connection->getOutBlock())       //nelze vytvorit spojeni na jednom bloku
                return;

            active_connection->setInblock(block);
            connectionList* in = block->getInList();
            MyLabel* temp = active_connection->getOutBlock();
            connectionList* out = temp->getOutList();
            int g,h;
            active_connection->getOutcoords(&g,&h);
            block->getCoords(&x, &y);
            active_connection->setPen(*pen);
            active_connection->setIncoords(&x, &y);
            active_connection->getIncoords(&x, &y);
            active_connection->setLine(g,h, x, y);
            scene->addItem(active_connection);
            active_connection->incNumOfClicks();
            in->insert(active_connection);
            out->insert(active_connection);
        }
    }

    else{
        active_connection = new connection();
        active_connection->setOutblock(block);
        block->getCoords(&x, &y);
        active_connection->setOutcoords(&x, &y);
        active_connection->incNumOfClicks();
    }
}

void MainWindow::deleteSlot(MyLabel *block){
    if(ui->actionDelete->isChecked()){
        // muzes deletovat
        active_connection = NULL;
        connectionList* out_list = block->getOutList();
        connectionList* in_list = block->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(block->getID(), true);
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(block->getID(), false);
            item = item->next;
        }

        blocks->deleteBlock(block->getID());
    }

    else{
        return;
    }
}


/*
void MainWindow::mouseDoubleClick(MyLabel *block){
    blockType type = block->getType();
        // TODO zjisti kolik vstupu potrebujes
    if (type == COMBAT){
        bool ok;
        QString text = QInputDialog::getText(this, "Input", "Enter an input God", QLineEdit::Normal, "", &ok);
      //  QDebug << text <<" jet ocombat\n";
    }
}*/


void MainWindow::run(){


}

void MainWindow::newScheme(){
    this->Spawn_x = 12;
    this->Spawn_y = 67;
    blocks_ID = 0;
    Listblock* tmp = blocks->getFirst();
    int lenght = blocks->getListLenght();
    active_connection = NULL;
    for(int i = 0; i < lenght; i++){
        connectionList* out_list = tmp->data->getOutList();
        connectionList* in_list = tmp->data->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(tmp->data->getID(), true);
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(tmp->data->getID(), false);
            item = item->next;
        }

        blocks->deleteBlock(tmp->data->getID());
        tmp = tmp->next;
    }

    delete blocks;
    blocks = new BlockList;
}

void MainWindow::printHelp(){
    QMessageBox help;
    help.setWindowTitle("Block Editor - Help");
    help.setText(QString("Move a block:\n   - Press, move and release left mouse button\n\n") +
                 QString("Make a connection:\n   - Click on a blocks you want to connect with right mouse button\n\n") +
                 QString("Run editor:\n   - Press Run\n\n") +
                 QString("Enter a God:\n   - Zeus, Odin, Athena, Njord, Mimir, Poseidon\n\n") +
                 QString("Delete block or connection:\n   - Toggle Delete button and press on block/connection \n      you want to delete with left mouse button\n\n"));
    help.exec();
}

void MainWindow::load(){
    QString filename;
    filename = QFileDialog::getOpenFileName(this, "Load a scheme", "/home/", "Scheme (*.bla)");
    qDebug() << filename;
}



























