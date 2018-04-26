#ifndef SUPP_H
#define SUPP_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"

class Block;
struct PortStuff {
	void *value;
	bool *init;
};

class Connect {
public:
	char *Data_type;
	bool transfered;
	PortStuff *reaction;

	Block* in;
	Block* out;

	Connect(Block *blok, Block *blok2);
	void DistributeResult(void *);

};

struct ListItem {
	Connect *data;
	ListItem *next;
};

class SubscribeList {
public:
	ListItem *first;
	int	listLenght;

	SubscribeList() { this->first = nullptr;  this->listLenght = 0; }
	int getLenght() { return this->listLenght; }
	ListItem * getFirst() { return this->first; }
	void InsertItem(Connect *);


};

#endif