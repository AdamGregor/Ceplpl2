#ifndef MYLABEL_H
#define MYLABEL_H

#include "connection.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class connection;
class connectionList;

enum blockType {COMBAT, ITEM, DICE, REST, ARENA};

class MyLabel : public QLabel{

    Q_OBJECT

private:
    blockType type;
    int x;
    int y;

    connectionList* out_List;
    connectionList* in_List;


public:
    MyLabel(QWidget *parent = 0);
    void setType(blockType typ);
    blockType getType();
    void setCoords(int x, int y);
    void getCoords(int* x, int *y);
    void setInconnection(connection* conn);
    void setOutconnection(connection* conn);
    connectionList* getOutList();
    connectionList* getInList();

public:
    void mouseReleaseEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
  //  void mouseDoubleClickEvent(QMouseEvent* event);


signals:
    void mouseRelease(MyLabel* label);
    void mousePress(MyLabel* label);
    void mouseDoubleClick(MyLabel* label);

};

#endif // MYLABEL_H
