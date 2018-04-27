#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QWidget>
#include <QGraphicsLineItem>

class connection : public QGraphicsLineItem
{
public:
    connection(QWidget* parent = 0);
};

#endif // CONNECTION_H
