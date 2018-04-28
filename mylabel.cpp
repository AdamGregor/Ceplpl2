#include "mylabel.h"
#include <QWidget>
#include <QLabel>

#include <iostream>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent){
    this->setMouseTracking(true);
    out_connection = NULL;
    in_connection = NULL;
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

void MyLabel::setCoords(int x, int y){
    this->x = x;
    this->y = y;
}

void MyLabel::getCoords(int *x, int *y){
    *x = this->x;
    *y = this->y;
}

void MyLabel::setInconnection(connection *conn){
    this->in_connection = conn;
}

void MyLabel::setOutconnection(connection *conn){
    this->out_connection = conn;
}

connection* MyLabel::getOutptr(){
    if(out_connection)
        return out_connection;
    else
        return NULL;
}

