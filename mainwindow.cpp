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
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BlockEditor");
    scene = new QGraphicsScene;
    ui->graphicsView->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setEnabled(false);
    QGraphicsLineItem* item = new QGraphicsLineItem;
    item->setLine(0,0,0.01,0.01);
    scene->addItem(item);

    pen = new QPen;
    pen->setWidth(4);

    blocks_ID = 0;
    active_connection = NULL;
    filename = QString();
    this->blocks = new BlockList;
    this->listConn = new blockConnect;
    this->Spawn_x = 12;
    this->Spawn_y = 67;

    connect(this, SIGNAL(resized()), this, SLOT(doResized()));
    connect(ui->actionCombat, SIGNAL(triggered()), this, SLOT(addCombat()));
    connect(ui->actionDice_throw, SIGNAL(triggered()), this, SLOT(addDice_throw()));
    connect(ui->actionArena_select, SIGNAL(triggered()), this, SLOT(addArena_select()));
    connect(ui->actionItem_apply, SIGNAL(triggered()), this, SLOT(addItem_apply()));
    connect(ui->actionRest, SIGNAL(triggered()), this, SLOT(addRest()));
    connect(ui->actionRun, SIGNAL(triggered()), this, SLOT(run()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(printHelp()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(save_as()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newScheme()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save_as()));

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

void MainWindow::resizeEvent(QResizeEvent *event){
    emit resized();
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
            listConn->insert(active_connection->getOutBlock()->getID(), active_connection->getInBlock()->getID());
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
        active_connection = NULL;
        connectionList* out_list = block->getOutList();
        connectionList* in_list = block->getInList();
        ListItem* item = out_list->getFirst();
        MyLabel* other_block;

        for(int i = 0; i < out_list->getListLenght(); i++){
            other_block = item->data->getInBlock();
            other_block->getInList()->deleteConnection(block->getID(), true);
            item = item->next;
            listConn->deleteConn(block->getID(), other_block->getID());
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(block->getID(), false);
            item = item->next;
            listConn->deleteConn(other_block->getID(), block->getID());
        }

        blocks->deleteBlock(block->getID());
    }

    else{
        return;
    }
}

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
            listConn->deleteConn(tmp->data->getID(), other_block->getID());
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(tmp->data->getID(), false);
            listConn->deleteConn(other_block->getID(), tmp->data->getID());
            item = item->next;
        }

        blocks->deleteBlock(tmp->data->getID());
        tmp = tmp->next;
    }

    delete blocks;
    listConn = new blockConnect;
    blocks = new BlockList;
}

void MainWindow::printHelp(){
    QMessageBox help;
    help.setWindowTitle("Block Editor - Help");
    help.setText(QString("Move a block:\n   - Press, move and release left mouse button\n\n") +
                 QString("Make a connection:\n   - Click on a blocks you want to connect with right mouse button\n\n") +
                 QString("Run editor:\n   - Press Run\n\n") +
                 QString("Enter a God:\n   - Zeus, Odin, Athena, Njord, Mimir, Poseidon\n\n") +
                 QString("Delete block:\n   - Toggle Delete button and press on block/connection \n      you want to delete with left mouse button\n\n"));
    help.exec();
}

void MainWindow::load(){
    filename = QFileDialog::getOpenFileName(this, "Open scheme", "./", "Scheme (*.az)");
    if(filename.isEmpty())
        return;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, "Unable to open file", file.errorString());
        return;
    }

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
            listConn->deleteConn(tmp->data->getID(), other_block->getID());
            item = item->next;
        }

        item = in_list->getFirst();
        for(int i = 0; i < in_list->getListLenght(); i++){
            other_block = item->data->getOutBlock();
            other_block->getOutList()->deleteConnection(tmp->data->getID(), false);
            listConn->deleteConn(other_block->getID(), tmp->data->getID());
            item = item->next;
        }

        blocks->deleteBlock(tmp->data->getID());
        tmp = tmp->next;
    }

    delete blocks;
    listConn = new blockConnect;
    blocks = new BlockList;

    QTextStream read(&file);
    bool ok;
    int count = 0;
    int ID, x, y;   //pro nove bloky
    blockType typ;
    QString combat = "COMBAT"; QString dice = "DICE"; QString item = "ITEM";
    QString arena = "ARENA"; QString rest = "REST";

    QString line = read.readLine();
    if(line.isEmpty()){
        file.close();
        return;
    }

    count = line.toInt(&ok, 10);
    for(int i = 0; i < count; i++){
        line = read.readLine();
        QStringList items = line.split(" ");
        for(int j = 0; j < items.size(); j++){
            if(j == 0){
                QString tmp = items.at(j);
                ID = tmp.toInt(&ok, 10);
                if(blocks_ID <= ID)
                    blocks_ID = ID + 1;
            }
            else if(j == 1){
                QString tmp = items.at(j);
                if(QString::compare(tmp, combat) == 0)
                    typ = COMBAT;
                else if(QString::compare(tmp, dice) == 0)
                    typ = DICE;
                else if(QString::compare(tmp, item) == 0)
                    typ = ITEM;
                else if(QString::compare(tmp, arena) == 0)
                    typ = ARENA;
                else if(QString::compare(tmp, rest) == 0)
                    typ = REST;
            }
            else if(j == 2){
                QString tmp = items.at(j);
                x = tmp.toInt(&ok, 10);
            }
            else if(j == 3){
                QString tmp = items.at(j);
                y = tmp.toInt(&ok, 10);
            }
        }

        MyLabel* newblock = new MyLabel(this);
        newblock->setID(ID);
        newblock->setType(typ);
        checkPlacement(&x, &y);
        newblock->setCoords(x, y);
        newblock->getCoords(&x, &y);
        connect(newblock , SIGNAL(mouseRelease(MyLabel*)), this, SLOT(mouseRelease(MyLabel*)));
        connect(newblock, SIGNAL(mousePress(MyLabel*)), this, SLOT(mousePress(MyLabel*)));
        connect(newblock, SIGNAL(deleteSig(MyLabel*)), this, SLOT(deleteSlot(MyLabel*)));
        newblock->setGeometry(x, y, 100, 100);
        if(typ == COMBAT){
            QPixmap pixmap(":combat.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == ARENA){
            QPixmap pixmap(":arenaSelect.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == DICE){
            QPixmap pixmap(":dice.png");
            newblock->setPixmap(pixmap);
        }
        else if(typ == ITEM){
            QPixmap pixmap(":itemSelect.gif");
            newblock->setPixmap(pixmap);
        }
        else if(typ == REST){
            QPixmap pixmap(":rest.gif");
            newblock->setPixmap(pixmap);
        }

        blocks->insert(newblock);
        newblock->show();
    }

    line = read.readLine();
    if(line.isEmpty()){
        file.close();
        return;
    }

    count = line.toInt(&ok, 10);
    qDebug() << blocks->getListLenght();

    file.close();
}

void MainWindow::save_as(){

    if(filename.isEmpty() == true){
      filename = QFileDialog::getSaveFileName(this, "Save File", "./untitled.az", "Scheme (*.az)");
    }

    if(filename.isEmpty() == true){
        return;
    }

    QFile file(filename);
    file.open( QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << blocks->getListLenght() << endl;
    Listblock* block = blocks->getFirst();
    for(int i = 0; i < blocks->getListLenght(); i++){
        stream << block->data->getID();
        if(block->data->getType() == COMBAT){
            stream << " COMBAT ";
        }
        else if(block->data->getType() == DICE){
            stream << " DICE ";
        }
        else if (block->data->getType() == ITEM){
            stream << " ITEM ";
        }
        else if (block->data->getType() == REST){
            stream << " REST ";
        }
        else if (block->data->getType() == ARENA){
            stream << " ARENA ";
        }

        int x,y;
        block->data->getCoords(&x, &y);
        stream << x << " " << y << endl;

        block = block->next;
    }

    stream << listConn->getListlenght() << endl;
    blockConn* item = listConn->getFirst();
    for(int i = 0; i < listConn->getListlenght(); i++){
        stream << item->first_ID << " " << item->second_ID << endl;
        item = item->next;
    }

    file.close();
}

void MainWindow::doResized(){
    Listblock* tmp = blocks->getFirst();
    connectionList* list;
    int x, y, g, h;
    for(int i = 0; i < blocks->getListLenght(); i++){
        tmp->data->getCoords(&x, &y);
        checkPlacement(&x, &y);
        tmp->data->setCoords(x, y);
        tmp->data->setGeometry(x, y, 100, 100);
        list = tmp->data->getOutList();
        ListItem* item = list->getFirst();
        for(int j = 0; j < list->getListLenght(); j++){
            item->data->setOutcoords(&x, &y);
            item->data->getOutcoords(&x, &y);
            item->data->getIncoords(&g, &h);
            item->data->setLine(x, y, g, h);
            item = item->next;
        }

        list = tmp->data->getInList();
        item = list->getFirst();
        for(int j = 0; j < list->getListLenght(); j++){
            item->data->setIncoords(&x, &y);
            item->data->getIncoords(&x, &y);
            item->data->getOutcoords(&g, &h);
            item->data->setLine(g, h, x, y);
            item = item->next;
        }
        tmp = tmp->next;
    }
}































