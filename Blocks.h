#ifndef BLOCK_H
#define BLOCK_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "SupportClasses.h"
#include <typeinfo>
/// Hlavicky jednotlivych bloku
struct PortStuff {
	void *value;
	bool *init;
};

class Block {
public:
	SubscribeList *subscriptions;

	Block() { this->subscriptions = new SubscribeList; }
	void setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); }
	virtual char* getOut() = 0;
	virtual PortStuff tryConnect(char*) = 0;
	virtual void eval() = 0;
};

class Rest : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
	Gods *OPort1;
	bool OPort1_Connected;
	bool OPort1_Initiated;


	Rest();
	void eval();
	PortStuff tryConnect(char*);
	char* getOut() {return "Gods"; }
};

class Combat : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
	Arena *IPort2;
	bool IPort2_Connected;
	bool IPort2_Initiated;
	
	Gods *IPort3;
	bool IPort3_Connected;
	bool IPort3_Initiated;

	Gods *OPort1;
	bool OPort1_Connected;
	bool OPort1_Initiated;

	//metody

	Combat();
	void eval();
	PortStuff tryConnect(char*);
	char* getOut() { return "Gods"; }
	
};


class ItemApply : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
	Accessories *IPort2;
	bool IPort2_Connected;
	bool IPort2_Initiated;

	Gods *OPort1;
	bool OPort1_Connected;
	bool OPort1_Initiated;

	//metody

	ItemApply();
	void eval();
	PortStuff tryConnect(char*);
	char* getOut() { return "Gods"; }
};

class DiceThrow : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	bool IPort1_Initiated;

	Gods *OPort1;
	bool OPort1_Connected;
	bool OPort1_Initiated;

	//metody

	DiceThrow();
	void eval();
	PortStuff tryConnect(char*);
	char* getOut() { return "Gods"; }
};

class ArenaSelect : public Block {
public:
	//I/O Porty
	Gods *IPort1;
	bool IPort1_Connected;
	bool IPort1_Initiated;

	Gods *IPort2;
	bool IPort2_Connected;
	bool IPort2_Initiated;

	Arena *OPort1;
	bool OPort1_Connected;
	bool OPort1_Initiated;

	//metody

	ArenaSelect();
	void eval();
	PortStuff tryConnect(char*);
	char* getOut() { return "Arena"; }
};



#endif 
