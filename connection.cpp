#include "connection.h"
#include <QGraphicsLineItem>
#include <QWidget>
#include <QGraphicsItem>
#include "mainwindow.h"

connection::connection(QWidget* parent){
    num_of_clicks = 0;
    outBlock = NULL;
    inBlock = NULL;

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
    this->in_x = *x;
    this->in_y = *y;
}

void connection::getOutcoords(int *x, int *y){
    *x = out_x;
    *y = out_y;
}

void connection::incNumOfClicks(){
    num_of_clicks++;
}

int connection::getNumOfClicks(){
    return num_of_clicks;
}

MyLabel* connection::getOutBlock(){
    if(outBlock == NULL)
        return NULL;
    else
        return outBlock;

}
