#ifndef BLOCK_H
#define BLOCK_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "SupportClasses.h"
#include <typeinfo>

/// Hlavicky jednotlivych bloku
class Block {
public:
	SubscribeList *subscriptions;
	bool OPort1_Connected;
	bool OPort1_Initiated;

	Block() { this->subscriptions = new SubscribeList; }
	virtual void setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); this->OPort1_Connected = true; }
	virtual char* getOut() = 0;
	virtual PortStuff *tryConnect(char*) = 0;
	virtual void eval() = 0;
	virtual bool askReady() = 0;
};

class Rest : public Block {
public:
	//I/O Porty
	void *IPort1;	//BUH
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
    Gods *OPort1;


	Rest();
	void eval();
	PortStuff *tryConnect(char*);
	char* getOut() {return "Gods"; }
	bool askReady();
};

class Combat : public Block {
public:
	//I/O Porty
	void *IPort1; //BUH
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
	void *IPort2; //ARENA
	bool IPort2_Connected;
	bool IPort2_Initiated;
	
	void *IPort3; //BUH
	bool IPort3_Connected;
	bool IPort3_Initiated;

	Gods *OPort1;

	//metody

	Combat();
	void eval();
	PortStuff *tryConnect(char*);
	char* getOut() { return "Gods"; }
	bool askReady();
	
};


class ItemApply : public Block {
public:
	//I/O Porty
	void *IPort1;	//BUH
	bool IPort1_Connected;
	bool IPort1_Initiated;
	
	void *IPort2;	//PREDMET
	bool IPort2_Connected;
	bool IPort2_Initiated;

	Gods *OPort1;

	//metody

	ItemApply();
	void eval();
	PortStuff *tryConnect(char*);
	char* getOut() { return "Gods"; }
	bool askReady();
};

class DiceThrow : public Block {
public:
	//I/O Porty
	void*IPort1; //BUH
	bool IPort1_Connected;
	bool IPort1_Initiated;

	Gods *OPort1;

	//metody

	DiceThrow();
	void eval();
	PortStuff *tryConnect(char*);
	char* getOut() { return "Gods"; }
	bool askReady();
};

class ArenaSelect : public Block {
public:
	//I/O Porty
	void *IPort1;	//BUH
	bool IPort1_Connected;
	bool IPort1_Initiated;

	void *IPort2;
	bool IPort2_Connected;
	bool IPort2_Initiated;

	Arena *OPort1; //BUH

	//metody

	ArenaSelect();
	void eval();
	PortStuff *tryConnect(char*);
	char* getOut() { return "Arena"; }
	bool askReady();
};



#endif 
