#include "mylabel.h"
#include "connection.h"
#include <QWidget>
#include <QLabel>

#include <iostream>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent){
    this->setMouseTracking(true);
    in_List = new connectionList;
    out_List = new connectionList;
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
    if(event->button() == Qt::RightButton){
        emit mousePress(this);
    }
}
/*
void MyLabel::mouseDoubleClickEvent(QMouseEvent *event){
    emit mouseDoubleClick(this);

}*/

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


