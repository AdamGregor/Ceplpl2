/**
 *@file mylabel.cpp
 *@author Zdenek Jelinek (xjelin47)
 *@author Adam Gregor (xgrego18)
 *@brief  zdrojový soubor pro grafické bloky
 */

#include "mylabel.h"
#include "connection.h"
#include <QWidget>
#include <QLabel>

#include <iostream>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent){
    this->setMouseTracking(true);
    in_List = new connectionList;
    out_List = new connectionList;
    IDlabel = nullptr;
    logicConnect = nullptr;
}

MyLabel::~MyLabel(){
    delete IDlabel;
    MyLabel* other_block;
    ListItem* tmp = out_List->getFirst();
    for(int i = 0; i < out_List->getListLenght(); i++){
        other_block = tmp->data->getInBlock();
        other_block->getInList()->deleteConnection(this->block_ID, true);
        tmp = tmp->next;
    }

    tmp = in_List->getFirst();
    for(int i = 0; i < in_List->getListLenght(); i++){
        other_block = tmp->data->getOutBlock();
        other_block->getOutList()->deleteConnection(this->block_ID, false);
        tmp = tmp->next;
    }

    return;
}

void MyLabel::setID(unsigned int ID){
    block_ID = ID;
}

unsigned int MyLabel::getID(){
    return this->block_ID;
}

void MyLabel::setType(blockType typ){
    type = typ;
}

blockType MyLabel::getType(){
    return type;
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit mouseRelease(this);
    }
}

void MyLabel::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton)
        emit mousePress(this);
    else if (event->button() == Qt::LeftButton)
        emit deleteSig(this);

}

Block *MyLabel::getLogicblock(){
    return this->logicBlock;
}

void MyLabel::setLogicblock(Block* logicBl){
    this->logicBlock = logicBl;
}

void MyLabel::setLogicconnect(Connect *conn){
    this->logicConnect = conn;
}

void MyLabel::setCoords(int x, int y){
    this->x = x;
    this->y = y;
}

void MyLabel::getCoords(int *x, int *y){
    *x = this->x;
    *y = this->y;
}

connectionList *MyLabel::getOutList(){
    return out_List;

}

connectionList *MyLabel::getInList(){
    return in_List;
}

void MyLabel::setIDlabel(MyLabel *label){
    this->IDlabel = label;
}

MyLabel *MyLabel::getIDlabel(){
    return IDlabel;
}


// BlocksList

BlockList::BlockList(){
    lenght = 0;
    first = nullptr;
}

void BlockList::insert(MyLabel *block){
    Listblock* nove = new Listblock;
    Listblock* prvni = this->getFirst();
    nove->data = block;
    nove->next = prvni;
    first = nove;
    lenght++;
}

void BlockList::deleteBlock(unsigned int block_ID){
    Listblock* tmp = this->getFirst();
    Listblock* old_tmp = tmp;
    for(int i = 0; i < lenght; i++){
        if(tmp->data->getID() == block_ID){
            if(this->first->data->getID() == block_ID){
                first = tmp->next;
                delete tmp->data;
                lenght--;
                return;
            }
            else{
                old_tmp->next = tmp->next;
                delete tmp->data;
                lenght--;
                return;
            }
        }
        else{
            old_tmp = tmp;
            tmp = tmp->next;
        }
    }
}

int BlockList::getListLenght(){
    return lenght;
}

Listblock* BlockList::getFirst(){
    return this->first;
}
