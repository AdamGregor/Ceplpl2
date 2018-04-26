#ifndef  EXECUTE_H
#define EXECUTE_H
#include "Blocks.h"

struct BlocklistElem {
	Block *Data;
	BlocklistElem *next;
};

class  Blocklist {
	BlocklistElem * first;
public:
	Blocklist() { first = nullptr; }
	void addItem(Block*);
	BlocklistElem*	getFirst() { return first; }
};

class Execute{
	Blocklist *Blocks;
	

public:
	int Block_count;

	Execute();
	void AddBlock(Block *);
	void Run();
	/*void Step();
	void Reset();
	*/
};




#endif // ! EXECUTE_H
