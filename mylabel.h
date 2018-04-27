#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class MyLabel : public QLabel{

    Q_OBJECT

private:
    int x;
    int y;

public:
    MyLabel(QWidget *parent = 0);

public:
    void mouseReleaseEvent(QMouseEvent *event);


signals:
    void mouseRelease(MyLabel* label);

};

#endif // MYLABEL_H
