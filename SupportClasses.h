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
    void*           value;
    bool*           init;
    string          blockType;
};

class Connect {
public:
    string          Data_type;
    bool            transfered;
    PortStuff*      reaction;
    double          value;
    string          name;

    Block*          in;
    string          in_name;
    Block*          out;
    string          out_name;

                    Connect(Block *blok, Block *blok2, bool* ok);
    bool            GetTransfered(){return transfered;}
    double          GetValue(){return value;}
    string          GetName(){return name;}
    void            Disconnect(int);
    void            DistributeResult(void *,double, string);
    void            Reset(){transfered = false; value = -1; name = "None";}
};

struct ListItemLogic {
    Connect*        data;
    ListItemLogic*  next;
};

class SubscribeList {
public:
    ListItemLogic*  first;
    int             listLenght;

                    SubscribeList() { this->first = nullptr ;  this->listLenght = 0; }
    int             getLenght() { return this->listLenght; }
    ListItemLogic*  getFirst() { return this->first; }
    void            InsertItem(Connect *);
    void            RemoveItem(Connect *);
};

#endif
