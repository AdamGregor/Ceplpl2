#ifndef MYLABEL_H
#define MYLABEL_H

#include "connection.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class connection;
class connectionList;

class MyLabel : public QLabel{

    Q_OBJECT

private:
    int x;
    int y;

    connectionList* out_List;
    connectionList* in_List;


public:
    MyLabel(QWidget *parent = 0);
    void setCoords(int x, int y);
    void getCoords(int* x, int *y);
    void setInconnection(connection* conn);
    void setOutconnection(connection* conn);
    //connection* getOutptr();
    //connection* getInptr(){return in_connection;}
    connectionList* getOutList();
    connectionList* getInList();

public:
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);


signals:
    void mouseRelease(MyLabel* label);
    void mousePress(MyLabel* label);

};

#endif // MYLABEL_H
