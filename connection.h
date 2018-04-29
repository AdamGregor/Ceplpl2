#ifndef CONNECTION_H
#define CONNECTION_H

#include "mylabel.h"

#include <QObject>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QHoverEvent>

class connection;

struct ListItem{
    connection* data;
    ListItem* next;
};

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
    void getIncoords(int* x, int* y);
    void incNumOfClicks();
    int getNumOfClicks();
    MyLabel* getOutBlock();
    MyLabel* getInBlock(){return inBlock;}
   // void setNext(connection* conn);
    //connection* getNext(){return next;}

};

class connectionList{
    ListItem* first;
    int lenght;


public:
    connectionList();
    void insert(connection* item);
    int getListLenght();
    ListItem* getFirst();
};

#endif // CONNECTION_H





