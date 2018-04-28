#ifndef CONNECTION_H
#define CONNECTION_H

#include "mylabel.h"

#include <QObject>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QGraphicsItem>

class MyLabel;

class connection : public QGraphicsLineItem{
    MyLabel* outBlock;
    int out_x;
    int out_y;

    MyLabel* inBlock;
    int in_x;
    int in_y;

    int num_of_clicks;

public:
    connection(QWidget* parent = 0);
    void setOutblock(MyLabel* block);
    void setInblock(MyLabel* block);
    void setOutcoords(int* x, int* y);
    void getOutcoords(int* x, int* y);
    void setIncoords(int* x, int* y);
    void incNumOfClicks();
    int getNumOfClicks();
    MyLabel* getOutBlock();
    MyLabel* getInBlock(){return inBlock;}



};

#endif // CONNECTION_H
