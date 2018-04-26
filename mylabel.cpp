#include "mylabel.h"
#include <QWidget>
#include <QLabel>

#include <iostream>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent){
    this->setMouseTracking(true);
}

void MyLabel::mousePressEvent(QMouseEvent *event){
   // setMovingtrue();
    emit mousePress();
}

/*
void MyLabel::mouseReleaseEvent(QMouseEvent *event){
    emit mouseRelease(this);
}*/

void MyLabel::setMovingtrue(){
    moving = true;
}

void MyLabel::setMovingfalse(){
    moving = false;
}
