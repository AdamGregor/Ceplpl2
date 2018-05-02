/*!
    *\author	Adam Gregor
    *\mainpage	Blokov? editor 2018
    *\section	?vod
    * Tento kód vznikl v r?mci projektu do p¸edm?tu ICP
    *\section	Kompilace
    *Program se kompiluje klasicky, p¸?kazem 'make'
    \subsection Make
    * Napiðte make
*/


#ifndef BLOCK_H
#define BLOCK_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "SupportClasses.h"
#include <typeinfo>
#include <string>
using namespace std;

/// Hlavicky jednotlivych bloku
/*!
    *\brief Base class vðech blokov?ch t¸?d. Obsahuje deklarace metod, jeþ jsou d?d?ny vðemi t¸?dami blok?.
*/
class Block {
public:
    SubscribeList *subscriptions;
    bool OPort1_Connected;
    bool OPort1_Initiated;
    unsigned int ID_bloku;

    Block() { this->subscriptions = new SubscribeList; }
    virtual void setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); this->OPort1_Connected = true; }
    virtual string getOut() = 0;
    virtual PortStuff *tryConnect(string) = 0;
    virtual void eval() = 0;
    virtual bool askReady() = 0;
    virtual void Reset() = 0;
};

class Rest : public Block {
public:
    //I/O Porty
    void *IPort1;	//BUH
    bool IPort1_Connected;
    bool IPort1_Initiated;

    Gods *OPort1;


    Rest(unsigned int);
    void eval();
    PortStuff *tryConnect(string);
    string getOut() {return "Gods"; }
    bool askReady();
    void Reset();
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

    Combat(unsigned int);
    void eval();
    PortStuff *tryConnect(string);
    string getOut() { return "Gods"; }
    bool askReady();
    void Reset();

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

    ItemApply(unsigned int);
    void eval();
    PortStuff *tryConnect(string);
    string getOut() { return "Gods"; }
    bool askReady();
    void Reset();
};

class DiceThrow : public Block {
public:
    //I/O Porty
    void*IPort1; //BUH
    bool IPort1_Connected;
    bool IPort1_Initiated;

    Gods *OPort1;

    //metody

    DiceThrow(unsigned int);
    void eval();
    PortStuff *tryConnect(string);
    string getOut() { return "Gods"; }
    bool askReady();
    void Reset();
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

    ArenaSelect(unsigned int);
    void eval();
    PortStuff *tryConnect(string);
    string getOut() { return "Arena"; }
    bool askReady();
    void Reset();
};



#endif
