/**
 *@file connection.cpp
 *@author Zdenek Jelinek (xjelin47)
 *@author Adam Gregor (xgrego18)
 *@brief  zdrojový soubor pro grafické spoje
 */

#include "connection.h"
#include "mainwindow.h"
#include <QObject>
#include <QGraphicsLineItem>
#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>

#include <iostream>
#include <string>

connection::connection(){
    num_of_clicks = 0;
    outBlock = nullptr;
    inBlock = nullptr;
    this->setAcceptHoverEvents(true);
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


/**
 * @brief Událost, kdy je myš nad spojem, nastaví tooltip spoje.
 * Pro spojení nad kterým se nachází myš, se zjistí ID a typ bloků, které jsou spojeny.
 * Pokud v bloku, ze kterého spoj vychází, byl proveden výpočet, zjistí se aktuální data,
 * která se nastaví jako ToolTip, v opačném případě se nastaví hláška s "No data transfered"
 * @param event
 */
void connection::hoverEnterEvent(QGraphicsSceneHoverEvent* event){
    unsigned int id = this->getOutBlock()->getID();
    QString ID = QString::number(id);
    blockType type;
    type = this->getOutBlock()->getType();
    blockType druhytype;
    druhytype = this->getInBlock()->getType();
    QString druheid = QString::number(this->getInBlock()->getID());
    QString druhytyp = " ?";
    QString blocktype = " ?";
    if(type == DICE)
        blocktype = "DICE";
    else if(type == COMBAT)
        blocktype = "COMBAT";
    else if(type == ARENA)
        blocktype = "ARENA";
    else if(type == ITEM)
        blocktype = "ITEM";
    else if(type == REST)
        blocktype = "REST";

    if(druhytype == DICE)
        druhytyp = "DICE";
    else if(druhytype == COMBAT)
        druhytyp = "COMBAT";
    else if(druhytype == ARENA)
        druhytyp = "ARENA";
    else if(druhytype == ITEM)
        druhytyp = "ITEM";
    else if (druhytype == REST)
        druhytyp = "REST";


    bool transf = this->getOutBlock()->getLogicconnect()->GetTransfered();

    if(!transf){
        this->setToolTip("Out Block ID: " + ID + "\n"
                         "Out Block Type: " + blocktype + "\n\n"
                         "In Block ID: " + druheid + "\n"
                         "In block Type: " + druhytyp + "\n\n"
                         "No data transfered.\n");
    }
    else{
        std::string name = this->getOutBlock()->getLogicconnect()->GetName();
        QString tmpname = QString::fromStdString(name);
        double strenght = this->getOutBlock()->getLogicconnect()->GetValue();
        QString eff = QString::number(strenght);
        if(type == ARENA){
            this->setToolTip("Out Block ID: " + ID + "\n"
                             "Out Block Type: " + blocktype + "\n\n"
                             "In Block ID: " + druheid + "\n"
                             "In block Type: " + druhytyp + "\n\n"
                             "Name of Arena: " + tmpname + "\n"
                             "Effect: " + strenght + "\n");
        }
        else{
            this->setToolTip("Out Block ID: " + ID + "\n"
                             "Out Block Type: " + blocktype + "\n\n"
                             "In Block ID: " + druheid + "\n"
                             "In block Type: " + druhytyp + "\n\n"
                             "Name of God: " + tmpname + "\n"
                             "Strenght: " + eff + "\n");
        }
    }


    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::red);
    this->setPen(pen);
}

void connection::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::black);
    this->setPen(pen);
}


//  CONNECTIONLIST
connectionList::connectionList(){
    lenght = 0;
    first = nullptr;
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
    ListItem* old_next = first;
    for(int i = 0; i < lenght; i++){
        if(out){
            if(block_ID == tmp->data->getOutBlock()->getID()){
                if(tmp->data == first->data){
                    first = tmp->next;
                    delete tmp->data;
                    delete tmp;
                    lenght--;
                    return;
                }
                else{
                    old_next->next = tmp->next;
                    delete tmp->data;
                    tmp->next = nullptr;
                    delete tmp;
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
                    delete tmp;
                    lenght--;
                    return;
                }
                else{
                    old_next->next = tmp->next;
                    delete tmp->data;
                    tmp->next = nullptr;
                    lenght--;
                    delete tmp;
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

// BLOCKLIST
blockConnect::blockConnect(){
    this->first = nullptr;
    this->lenght = 0;
}

void blockConnect::insert(int first_ID, int second_ID){
    blockConn* nove = new blockConn;
    blockConn* prvni = this->getFirst();
    nove->first_ID = first_ID;
    nove->second_ID = second_ID;
    nove->next = prvni;
    first = nove;
    lenght++;
}

blockConn *blockConnect::getFirst(){
    return first;
}

void blockConnect::deleteConn(unsigned int first_ID, unsigned int second_ID){
    blockConn* tmp = first;
    blockConn* old_next = first;
    for(int i = 0; i < lenght; i++){
        if(tmp->first_ID == first_ID && tmp->second_ID == second_ID){
            if(tmp == first){
                first = tmp->next;
                lenght--;
                //delete tmp;
                return;
            }
            else{
                old_next->next = tmp->next;
               // delete tmp;
                lenght--;
            }
        }
        else{
            old_next = tmp;
            tmp = tmp->next;
        }
    }
}

int blockConnect::getListlenght(){
    return lenght;
}

