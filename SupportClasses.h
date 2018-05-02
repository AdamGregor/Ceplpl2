#ifndef SUPP_H
#define SUPP_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"
#include <string>
using namespace std;

class Block;
struct PortStuff {
    void *value;
    bool *init;
};

class Connect {
public:
    string Data_type;
    bool transfered;
    PortStuff *reaction;

    Block* in;
    Block* out;

    Connect(Block *blok, Block *blok2);
    void DistributeResult(void *);
};

struct ListItemLogic {
    Connect *data;
    ListItemLogic *next;
};

class SubscribeList {
public:
    ListItemLogic *first;
    int	listLenght;

    SubscribeList() { this->first = nullptr ;  this->listLenght = 0; }
    int getLenght() { return this->listLenght; }
    ListItemLogic * getFirst() { return this->first; }
    void InsertItem(Connect *);


};

#endif
