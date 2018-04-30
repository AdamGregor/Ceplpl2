/**
 *@file connection.cpp
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief  connection between blocks for gui
 */

#include "connection.h"
#include <QGraphicsLineItem>
#include <QWidget>
#include <QGraphicsItem>
#include "mainwindow.h"

#include <iostream>

connection::connection(QWidget* parent){
    num_of_clicks = 0;
    outBlock = NULL;
    inBlock = NULL;
  //  this->setAcceptHoverEvents(true);

}

void connection::setOutblock(MyLabel *block){
    this->outBlock = block;
}

void connection::setInblock(MyLabel *block){
    this->inBlock = block;
}

void connection::setOutcoords(int *x, int *y){
    this->out_x = *x + 88;
    this->out_y = *y - 17;
}


void connection::setIncoords(int *x, int *y){
    this->in_x = *x - 12;
    this->in_y = *y - 17;
}

void connection::getOutcoords(int *x, int *y){
    *x = out_x;
    *y = out_y;
}

void connection::getIncoords(int *x, int *y){
    *x = in_x;
    *y = in_y;
}

void connection::incNumOfClicks(){
    num_of_clicks++;
}

int connection::getNumOfClicks(){
    return num_of_clicks;
}

MyLabel *connection::getOutBlock(){
    return outBlock;
}


//  CONNECTIONLIST
connectionList::connectionList(){
    lenght = 0;
    first = NULL;
}

void connectionList::insert(connection* item){
    ListItem* nove = new ListItem;
    ListItem* prvni = this->getFirst();
    nove->data = item;
    nove->next = prvni;
    first = nove;
    lenght++;
}

void connectionList::deleteConnection(unsigned int block_ID, bool out){
    ListItem* tmp = first;
    ListItem* old_next;
    for(int i = 0; i < lenght; i++){
        if(out){
            if(block_ID == tmp->data->getOutBlock()->getID()){
                if(tmp->data == first->data){
                    first = tmp->next;
                    delete tmp->data;
                    lenght--;
                    return;
                }
                else{
                    old_next->next = tmp->next;
                    delete tmp->data;
                    tmp->next = NULL;
                    lenght--;
                    return;
                }
            }
            else{
                old_next = tmp;
                tmp = tmp->next;
            }
        }
        else{
            if(block_ID == tmp->data->getInBlock()->getID()){
                if(tmp->data == first->data){
                    first = tmp->next;
                    delete tmp->data;
                    lenght--;
                    return;
                }
                else{
                    old_next->next = tmp->next;
                    delete tmp->data;
                    tmp->next = NULL;
                    lenght--;
                    return;
                }
            }
            else{
                old_next = tmp;
                tmp = tmp->next;
            }
        }
    }
}

int connectionList::getListLenght(){
    return lenght;
}

ListItem* connectionList::getFirst(){
    return first;
}
