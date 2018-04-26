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
    bool moving;

public:
    MyLabel(QWidget *parent = 0);

public:
    void mousePressEvent(QMouseEvent *event);
   // void mouseReleaseEvent(QMouseEvent *event);
    void setMovingtrue();
    void setMovingfalse();


signals:
    void mousePress();
   // void mouseRelease(MyLabel* label);

};

#endif // MYLABEL_H
