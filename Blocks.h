#ifndef BLOCK_H
#define BLOCK_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"

/// Hlavicky jednotlivych bloku

class Block {
public:
	virtual void eval() = 0;
};

class Rest: public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	Gods *OPort1;
	bool OPort1_Connected;


	Rest();
	void eval();
};

class Combat : public Block {
protected:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	Arena *IPort2;
	bool IPort2_Connected;
	Gods *IPort3;
	bool IPort3_Connected;
	
	Gods *OPort1;
	bool OPort1_Connected;
	
	//metody
public:
	Combat();
	void eval();
};


class ItemApply : public Block {
protected:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	Accessories *IPort2;
	bool IPort2_Connected;

	Gods *OPort1;
	bool OPort1_Connected;

	//metody
public:
	ItemApply();
	void eval();
};

class DiceThrow : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;

	Gods *OPort1;
	bool OPort1_Connected;

	//metody

	DiceThrow();
	void eval();
};

class ArenaSelect: public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	Gods *IPort2;
	bool IPort2_Connected;

	Arena *OPort1;
	bool OPort1_Connected;

	//metody

	ArenaSelect();
	void eval();
};

#endif 
