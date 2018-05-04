/*!
    *\author	Adam Gregor
    *\mainpage	Blokov? editor 2018
    *\section	?vod
    * Tento k?d vznikl v r?mci projektu do p?edm?tu ICP
    *\section	Kompilace
    *Program se kompiluje klasicky, p??kazem 'make'
    \subsection Make
    * Napi?te make
*/

/**
 *@file Blocks.h
 *@author Adam Gregor (xgrego18)
 *@author Zden?k Jel?nek (xjelin47)
 *@brief  Hlavièkov? soubor deklarujic? t??dy blok?.
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
    *\brief Base class blokov?ch t??d.
*/
class Block {
public:
    /**
     * @brief Ukazatel na seznam odchoz?ch spoj? bloku
     */
    SubscribeList*  subscriptions;
    /**
     * @brief Atribut znaè?c?, zda je k v?stypn?mu portu p?ipojen n?jak? spoj
     */
    bool            OPort1_Connected;
    /**
     * @brief Atribut znaè?c?, zda byl v?stupn? port tento v?poèet jiş iniciov?n
     */
    bool            OPort1_Initiated;
    /**
     * @brief Atribut ud?vajic? jednoznaèné ID bloku
     */
    unsigned int    ID_bloku;


    /**
    * @brief Konstruktor t??dy, vytvo?? seznam odchoz?ch spoj? a iniciuje atributy
    */
                    Block() { this->subscriptions = new SubscribeList; }
    /**
     * @brief Virtualn? destruktor bloku, ruğ? odchoz? spoje, odeb?ra blok ze seznamu blok?
     */
    virtual         ~Block();
    /**
     * @brief Metoda p?id?vajic? spoj do seznamu odchoz?ch spoj?
     * @param Ukazatel na spoj
     */
    virtual void    setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); this->OPort1_Connected = true; }
                    /**
     * @brief Èist? viru?ln? metoda, vracejic? odchoz? typ bloku
     * @return string typ_bloku
     */
    virtual string  getOut() = 0;
                    /**
     * @brief Metoda snaşic? se vytvo?i spoj, jdouc? do this
     * @param typ dat emitujic? out port na druhé stran? spojen?
     * @param ukazatel na spojen?
     * @return struktura obsahujic? negativn? v?sledek nebo informace k propojen?
     */
    virtual PortStuff* tryConnect(string typ, Connect* spoj) = 0;
                    /**
     * @brief Èist? virtu?ln? metoda zajiğtujic? naèten? nenapojen?ch port?, v?poèet bloku a distribuci v?sledku
     */
    virtual void    eval() = 0;
    /**
     * @brief Èist? virtu?ln? metoda zjiğ?ujic? zda je blok p?ipraven na eval()
     * @return true - ano, false - ne
     */
    virtual bool    askReady() = 0;
                    /**
     * @brief Èist? virtu?ln? metoda resetujic? stav bloku
     */
    virtual void    Reset() = 0;
             /**
     * @brief Èist? virtu?ln? metoda odpojujic? spoj od bloku
     * @param ukazatel na spoj
     */
    virtual void    Disconnect(Connect* spoj)=0;
      /**
       * @brief Èist? virtu?ln? metoda vracejic? typ bloku
       * @return string typ_bloku
       */
    virtual string  getType()=0;
};

/**
 * @brief Derivace tøídy Block, reprezentuje blok Rest (odpoèinek)
 */
class Rest : public Block {
public:

    ///I/O Porty
    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort1 pøipojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort1  pøiveden vısledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese vısledek vıpoètu
     */
    Gods*       OPort1;



    ///METODY
    /**
                 * @brief Konstruktor, pøiøadí bloku jeho unikátní ID, inicializuje hodnoty atributu, pøidá blok do
                 * seznamu blokù
                 */
                Rest(unsigned int);
    /**
    * @brief Destruktor bloku Rest, ruší pøíchozí spoje
    */
                ~Rest();
                /**
     * @brief Metoda doplòujicí chybìjicí porty, provádìjicí vıpoèet a distribujicí vısledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu pøipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspìchu/neúspìchu/pøipojeném portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datovı typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() {return "Gods"; }
    /**
     * @brief Zjišuje, zda je blok pøipraven na vyhodnocení
     * (IPorty, které berou data z jinıch blokù ji mají hodnotu)
     * @return true-lze poèítat, false-nelze poèítat
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
 * @brief Derivace tøídy Block, reprezentuje blok Combat (Souboj)
 */
class Combat : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort1 pøipojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort1  pøiveden vısledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort1_Connection;


    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel pøetypován na (Arena*)
     */
    void*       IPort2; //ARENA
    /**
     * @brief Booleanská promìnná, udává, zda je IPort2 pøipojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort2  pøiveden vısledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort2 pøivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 3. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort3; //BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort3 pøipojen k jinému bloku
     */
    bool        IPort3_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort3  pøiveden vısledek jiného bloku
     */
    bool        IPort3_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort2 pøivedeno
     */
    Connect*    IPort3_Connection;


    /**
     * @brief Ukazatel na Gods, nese vısledek vıpoètu
     */
    Gods*       OPort1;


    ///metody
    /**
                 * @brief Konstruktor, pøiøadí bloku jeho unikátní ID, inicializuje hodnoty atributu, pøidá blok do
                 * seznamu blokù
                 */
                Combat(unsigned int);
    /**
                * @brief Destruktor bloku Combat, ruší pøíchozí spoje
                */
                ~Combat();
                /**
     * @brief Metoda doplòujicí chybìjicí porty, provádìjicí vıpoèet a distribujicí vısledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu pøipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspìchu/neúspìchu/pøipojeném portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datovı typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišuje, zda je blok pøipraven na vyhodnocení
     * (IPorty, které berou data z jinıch blokù ji mají hodnotu)
     * @return true-lze poèítat, false-nelze poèítat
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
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort1 pøipojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort1  pøiveden vısledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel pøetypován na (ACCESSORIES*)
     */
    void*       IPort2;	//PREDMET
    /**
     * @brief Booleanská promìnná, udává, zda je IPort2 pøipojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort2  pøiveden vısledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort2 pøivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Gods, nese vısledek vıpoètu
     */
    Gods*       OPort1;


    ///metody

    /**
                 * @brief Konstruktor, pøiøadí bloku jeho unikátní ID, inicializuje hodnoty atributu, pøidá blok do
                 * seznamu blokù
                 */
                ItemApply(unsigned int);
    /**
                * @brief Destruktor bloku ItemApply, ruší pøíchozí spoje
                */
                ~ItemApply();
     /**
     * @brief Metoda doplòujicí chybìjicí porty, provádìjicí vıpoèet a distribujicí vısledek
     */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu pøipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspìchu/neúspìchu/pøipojeném portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datovı typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišuje, zda je blok pøipraven na vyhodnocení
     * (IPorty, které berou data z jinıch blokù ji mají hodnotu)
     * @return true-lze poèítat, false-nelze poèítat
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
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort1 pøipojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort1  pøiveden vısledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese vısledek vıpoètu
     */
    Gods*       OPort1;

    ///metody

    /**
                * @brief Konstruktor, pøiøadí bloku jeho unikátní ID, inicializuje hodnoty atributu, pøidá blok do
                * seznamu blokù
                */
                DiceThrow(unsigned int);
    /**
                * @brief Destruktor bloku DiceThrow, ruší pøíchozí spoje
                */
                ~DiceThrow();
    /**
                * @brief Metoda doplòujicí chybìjicí porty, provádìjicí vıpoèet a distribujicí vısledek
                */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu pøipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspìchu/neúspìchu/pøipojeném portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datovı typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zjišuje, zda je blok pøipraven na vyhodnocení
     * (IPorty, které berou data z jinıch blokù ji mají hodnotu)
     * @return true-lze poèítat, false-nelze poèítat
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
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 1. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleanská promìnná, udává, zda je IPort1 pøipojen k jinému bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort1  pøiveden vısledek jiného bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitnì NULL, data reprezentuje data jdoucí do 2. portu.
     * V rámci bloku je ukazatel pøetypován na (Gods*)
     */
    void*       IPort2;
    /**
     * @brief Booleanská promìnná, udává, zda je IPort2 pøipojen k jinému bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleanská promìnná, udává, zda byla v rámci vıpoètu do IPort2  pøiveden vısledek jiného bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, udává spojení, které je do IPort1 pøivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Arena, nese vısledek vıpoètu
     */
    Arena*      OPort1; //BUH

    ///metody

    /**
                * @brief Konstruktor, pøiøadí bloku jeho unikátní ID, inicializuje hodnoty atributu, pøidá blok do
                * seznamu blokù
                */
                ArenaSelect(unsigned int);
    /**
                * @brief Destruktor bloku ArenaSelect, ruší pøíchozí spoje
                */
                ~ArenaSelect();
    /**
                * @brief Metoda doplòujicí chybìjicí porty, provádìjicí vıpoèet a distribujicí vısledek
                */
    void        eval();
    /**
     * @brief Metoda, volána pri pokusu pøipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujicí inormace o úspìchu/neúspìchu/pøipojeném portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrací datovı typ OPortu bloku
     * @return string "Arena"
     */
    string      getOut() { return "Arena"; }
    /**
     * @brief Zjišuje, zda je blok pøipraven na vyhodnocení
     * (IPorty, které berou data z jinıch blokù ji mají hodnotu)
     * @return true-lze poèítat, false-nelze poèítat
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
