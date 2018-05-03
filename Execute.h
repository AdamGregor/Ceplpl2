#ifndef  EXECUTE_H
#define EXECUTE_H
#include "Blocks.h"

struct BlocklistElem {
    Block*          Data;
    BlocklistElem*  next;
};

class  Blocklist {
public:
    BlocklistElem*  first;


    Blocklist() { first = nullptr; }
    void            addItem(Block*);
	BlocklistElem*	getFirst() { return first; }
};

class Execute{
    Blocklist*      Blocks;
    int             Done;
    int             NotReadyInRow;
    bool            Completed;

public:
	int Block_count;

	Execute();
    void            AddBlock(Block *);
    void            Run();
    void            Step();
    void            Reset();
    void            Remove(Block*);
};




#endif // ! EXECUTE_H
