#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>

class block{
public:
    block();
    void setCoord(int x, int y);
    int getXCoord();
    int getYCoord();
    void addBlock(QLabel *label);
    void deleteBlock();
    void deleteAll();

private:
    QLabel *label;
    QLabel *nextLabel;
    int xCoord;
    int yCoord;
};

#endif // BLOCK_H
