#include "mylabel.h"
#include <QWidget>
#include <QLabel>

#include <iostream>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent){
    this->setMouseTracking(true);
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        emit mouseRelease(this);
    }
}

