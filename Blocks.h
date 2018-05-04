/*!
    *\author	Adam Gregor
    *\mainpage	blokový editor 2018
    *\section	Úvod
    * Tento kód vznikl v rámci projektu do předmětu ICP
    *\section	Kompilace
    *Program se kompiluje klasicky, příkazem 'make'
    \subsection Make
    * Napište make
*/

/**
 *@file Blocks.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor deklarujicí třídy bloků.
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
    *\brief Base class blokových tříd.
*/
class Block {
public:
    /**
     * @brief Ukazatel na seznam odchozích spojů bloku
     */
    SubscribeList*  subscriptions;
    /**
     * @brief Atribut značící, zda je k výstupnímu portu připojen nějaký spoj
     */
    bool            OPort1_Connected;
    /**
     * @brief Atribut značící, zda byl výstupní port tento výpočet již iniciován
     */
    bool            OPort1_Initiated;
    /**
     * @brief Atribut udávajicí jednoznačný ID bloku
     */
    unsigned int    ID_bloku;


    /**
    * @brief Konstruktor třídy, vytvoří seznam odchozích spojů a iniciuje atributy
    */
                    Block() { this->subscriptions = new SubscribeList; }
    /**
     * @brief Virtualní destruktor bloku, ruší odchozí spoje, odebíra blok ze seznamu bloků
     */
    virtual         ~Block();
    /**
     * @brief Metoda přidávajicí spoj do seznamu odchozích spojů
     * @param Ukazatel na spoj
     */
    virtual void    setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); this->OPort1_Connected = true; }
                    /**
     * @brief Čistě viruální metoda, vracejicí odchozí typ bloku
     * @return string typ_bloku
     */
    virtual string  getOut() = 0;
                    /**
     * @brief Metoda snažicí se vytvoři spoj, jdoucí do this
     * @param typ dat emitujicí out port na druhé straně spojení
     * @param ukazatel na spojení
     * @return struktura obsahujicí negativní výsledek nebo informace k propojení
     */
    virtual PortStuff* tryConnect(string typ, Connect* spoj) = 0;
                    /**
     * @brief Čistě virtuální metoda zajižtujicí načtení nenapojeních portů, výpočet bloku a distribuci výsledku
     */
    virtual void    eval() = 0;
    /**
     * @brief Čistě virtuální metoda zjišťujicí zda je blok připraven na eval()
     * @return true - ano, false - ne
     */
    virtual bool    askReady() = 0;
                    /**
     * @brief Čistě virtuální metoda resetujicí stav bloku
     */
    virtual void    Reset() = 0;
             /**
     * @brief Čistě virtuální metoda odpojujicí spoj od bloku
     * @param ukazatel na spoj
     */
    virtual void    Disconnect(Connect* spoj)=0;
      /**
       * @brief Čistě virtuální metoda vracejicí typ bloku
       * @return string typ_bloku
       */
    virtual string  getType()=0;
};

/**
 * @brief Derivace třídy Block, reprezentuje blok Rest (odpočinek)
 */
class Rest : public Block {
public:

    ///I/O Porty
    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort1 připojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort1  přiveden výsledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese výsledek výpočtu
     */
    Gods*       OPort1;



    ///METODY
    /**
                 * @brief Konstruktor, případě bloku jeho unikátní ID, inicializuje hodnoty atributu, přidá blok do
                 * seznamu bloků
                 */
                Rest(unsigned int);
    /**
    * @brief Destruktor bloku Rest, ruší příchozí spoje
    */
                ~Rest();
                /**
     * @brief Metoda doplňujicí chybějicí porty, provádějicí výpočet a distribujicí výsledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu připojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspěchu/neúspěchu/připojením portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datový typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() {return "Gods"; }
    /**
     * @brief Zjišťuje, zda je blok připraven na vyhodnocení
     * (IPorty, který berou data z jinéch bloků již mají hodnotu)
     * @return true-lze počítat, false-nelze počítat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadaného spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrací typ bloku
     * @return string "REST"
     */
    string      getType(){return "REST";}
};

/**
 * @brief Derivace třídy Block, reprezentuje blok Combat (Souboj)
 */
class Combat : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort1 připojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort1  přiveden výsledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort1_Connection;


    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel přetypován na (Arena*)
     */
    void*       IPort2; //ARENA
    /**
     * @brief Booleanská proměnná, udává, zda je IPort2 připojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort2  přiveden výsledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort2 přivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 3. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort3; //BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort3 připojen k jinému bloku
     */
    bool        IPort3_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort3  přiveden výsledek jiného bloku
     */
    bool        IPort3_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort2 přivedeno
     */
    Connect*    IPort3_Connection;


    /**
     * @brief Ukazatel na Gods, nese výsledek výpočtu
     */
    Gods*       OPort1;


    ///metody
    /**
                 * @brief Konstruktor, případě bloku jeho unikátní ID, inicializuje hodnoty atributu, přidá blok do
                 * seznamu bloků
                 */
                Combat(unsigned int);
    /**
                * @brief Destruktor bloku Combat, ruší příchozí spoje
                */
                ~Combat();
                /**
     * @brief Metoda doplňujicí chybějicí porty, provádějicí výpočet a distribujicí výsledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu připojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspěchu/neúspěchu/připojením portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datový typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišťuje, zda je blok připraven na vyhodnocení
     * (IPorty, který berou data z jinéch bloků již mají hodnotu)
     * @return true-lze počítat, false-nelze počítat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadaného spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrací typ bloku
     * @return string "COMBAT"
     */
    string      getType(){return "COMBAT";}

};


class ItemApply : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort1 připojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort1  přiveden výsledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel přetypován na (ACCESSORIES*)
     */
    void*       IPort2;	//PREDMET
    /**
     * @brief Booleanská proměnná, udává, zda je IPort2 připojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort2  přiveden výsledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort2 přivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Gods, nese výsledek výpočtu
     */
    Gods*       OPort1;


    ///metody

    /**
                 * @brief Konstruktor, případě bloku jeho unikátní ID, inicializuje hodnoty atributu, přidá blok do
                 * seznamu bloků
                 */
                ItemApply(unsigned int);
    /**
                * @brief Destruktor bloku ItemApply, ruší příchozí spoje
                */
                ~ItemApply();
     /**
     * @brief Metoda doplňujicí chybějicí porty, provádějicí výpočet a distribujicí výsledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu připojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspěchu/neúspěchu/připojením portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datový typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišťuje, zda je blok připraven na vyhodnocení
     * (IPorty, který berou data z jinéch bloků již mají hodnotu)
     * @return true-lze počítat, false-nelze počítat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadaného spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrací typ bloku
     * @return string "ITEMAPPLY"
     */
    string        getType(){return "ITEMAPPLY";}
};

class DiceThrow : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort1 připojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort1  přiveden výsledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese výsledek výpočtu
     */
    Gods*       OPort1;

    ///metody

    /**
                * @brief Konstruktor, případě bloku jeho unikátní ID, inicializuje hodnoty atributu, přidá blok do
                * seznamu bloků
                */
                DiceThrow(unsigned int);
    /**
                * @brief Destruktor bloku DiceThrow, ruší příchozí spoje
                */
                ~DiceThrow();
    /**
                * @brief Metoda doplňujicí chybějicí porty, provádějicí výpočet a distribujicí výsledek
                */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu připojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspěchu/neúspěchu/připojením portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datový typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišťuje, zda je blok připraven na vyhodnocení
     * (IPorty, který berou data z jinéch bloků již mají hodnotu)
     * @return true-lze počítat, false-nelze počítat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadaného spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrací typ bloku
     * @return string "DICETHROW"
     */
    string      getType(){return "DICETHROW";}
};

class ArenaSelect : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská proměnná, udává, zda je IPort1 připojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort1  přiveden výsledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitní NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel přetypován na (Gods*)
     */
    void*       IPort2;
    /**
     * @brief Booleanská proměnná, udává, zda je IPort2 připojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská proměnná, udává, zda byla v rámci výpočtu do IPort2  přiveden výsledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, který je do IPort1 přivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Arena, nese výsledek výpočtu
     */
    Arena*      OPort1; //BUH

    ///metody

    /**
                * @brief Konstruktor, případě bloku jeho unikátní ID, inicializuje hodnoty atributu, přidá blok do
                * seznamu bloků
                */
                ArenaSelect(unsigned int);
    /**
                * @brief Destruktor bloku ArenaSelect, ruší příchozí spoje
                */
                ~ArenaSelect();
    /**
                * @brief Metoda doplňujicí chybějicí porty, provádějicí výpočet a distribujicí výsledek
                */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu připojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspěchu/neúspěchu/připojením portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datový typ OPortu bloku
     * @return string "Arena"
     */
    string      getOut() { return "Arena"; }
    /**
     * @brief Zjišťuje, zda je blok připraven na vyhodnocení
     * (IPorty, který berou data z jinéch bloků již mají hodnotu)
     * @return true-lze počítat, false-nelze počítat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadaného spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrací typ bloku
     * @return string "ARENASELECT"
     */
    string      getType(){return "ARENASELECT";}
};



#endif
