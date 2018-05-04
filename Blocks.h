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
 *@brief  Hlavi�kov? soubor deklarujic? t??dy blok?.
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
     * @brief Atribut zna�?c?, zda je k v?stypn?mu portu p?ipojen n?jak? spoj
     */
    bool            OPort1_Connected;
    /**
     * @brief Atribut zna�?c?, zda byl v?stupn? port tento v?po�et ji� iniciov?n
     */
    bool            OPort1_Initiated;
    /**
     * @brief Atribut ud?vajic? jednozna�n� ID bloku
     */
    unsigned int    ID_bloku;


    /**
    * @brief Konstruktor t??dy, vytvo?? seznam odchoz?ch spoj? a iniciuje atributy
    */
                    Block() { this->subscriptions = new SubscribeList; }
    /**
     * @brief Virtualn? destruktor bloku, ru�? odchoz? spoje, odeb?ra blok ze seznamu blok?
     */
    virtual         ~Block();
    /**
     * @brief Metoda p?id?vajic? spoj do seznamu odchoz?ch spoj?
     * @param Ukazatel na spoj
     */
    virtual void    setSubscribe(Connect *data) { this->subscriptions->InsertItem(data); this->OPort1_Connected = true; }
                    /**
     * @brief �ist? viru?ln? metoda, vracejic? odchoz? typ bloku
     * @return string typ_bloku
     */
    virtual string  getOut() = 0;
                    /**
     * @brief Metoda sna�ic? se vytvo?i spoj, jdouc? do this
     * @param typ dat emitujic? out port na druh� stran? spojen?
     * @param ukazatel na spojen?
     * @return struktura obsahujic? negativn? v?sledek nebo informace k propojen?
     */
    virtual PortStuff* tryConnect(string typ, Connect* spoj) = 0;
                    /**
     * @brief �ist? virtu?ln? metoda zaji�tujic? na�ten? nenapojen?ch port?, v?po�et bloku a distribuci v?sledku
     */
    virtual void    eval() = 0;
    /**
     * @brief �ist? virtu?ln? metoda zji�?ujic? zda je blok p?ipraven na eval()
     * @return true - ano, false - ne
     */
    virtual bool    askReady() = 0;
                    /**
     * @brief �ist? virtu?ln? metoda resetujic? stav bloku
     */
    virtual void    Reset() = 0;
             /**
     * @brief �ist? virtu?ln? metoda odpojujic? spoj od bloku
     * @param ukazatel na spoj
     */
    virtual void    Disconnect(Connect* spoj)=0;
      /**
       * @brief �ist? virtu?ln? metoda vracejic? typ bloku
       * @return string typ_bloku
       */
    virtual string  getType()=0;
};

/**
 * @brief Derivace t��dy Block, reprezentuje blok Rest (odpo�inek)
 */
class Rest : public Block {
public:

    ///I/O Porty
    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 1. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort1 p�ipojen k jin�mu bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort1  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese v�sledek v�po�tu
     */
    Gods*       OPort1;



    ///METODY
    /**
                 * @brief Konstruktor, p�i�ad� bloku jeho unik�tn� ID, inicializuje hodnoty atributu, p�id� blok do
                 * seznamu blok�
                 */
                Rest(unsigned int);
    /**
    * @brief Destruktor bloku Rest, ru�� p��choz� spoje
    */
                ~Rest();
                /**
     * @brief Metoda dopl�ujic� chyb�jic� porty, prov�d�jic� v�po�et a distribujic� v�sledek
     */
    void        eval();
    /**
     * @brief Metoda, vol�na pri pokusu p�ipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujic� inormace o �sp�chu/ne�sp�chu/p�ipojen�m portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrac� datov� typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() {return "Gods"; }
    /**
     * @brief Zji��uje, zda je blok p�ipraven na vyhodnocen�
     * (IPorty, kter� berou data z jin�ch blok� ji� maj� hodnotu)
     * @return true-lze po��tat, false-nelze po��tat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadan�ho spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrac� typ bloku
     * @return string "REST"
     */
    string      getType(){return "REST";}
};

/**
 * @brief Derivace t��dy Block, reprezentuje blok Combat (Souboj)
 */
class Combat : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 1. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort1 p�ipojen k jin�mu bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort1  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort1_Connection;


    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 2. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Arena*)
     */
    void*       IPort2; //ARENA
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort2 p�ipojen k jin�mu bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort2  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort2 p�ivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 3. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort3; //BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort3 p�ipojen k jin�mu bloku
     */
    bool        IPort3_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort3  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort3_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort2 p�ivedeno
     */
    Connect*    IPort3_Connection;


    /**
     * @brief Ukazatel na Gods, nese v�sledek v�po�tu
     */
    Gods*       OPort1;


    ///metody
    /**
                 * @brief Konstruktor, p�i�ad� bloku jeho unik�tn� ID, inicializuje hodnoty atributu, p�id� blok do
                 * seznamu blok�
                 */
                Combat(unsigned int);
    /**
                * @brief Destruktor bloku Combat, ru�� p��choz� spoje
                */
                ~Combat();
                /**
     * @brief Metoda dopl�ujic� chyb�jic� porty, prov�d�jic� v�po�et a distribujic� v�sledek
     */
    void        eval();
    /**
     * @brief Metoda, vol�na pri pokusu p�ipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujic� inormace o �sp�chu/ne�sp�chu/p�ipojen�m portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrac� datov� typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zji��uje, zda je blok p�ipraven na vyhodnocen�
     * (IPorty, kter� berou data z jin�ch blok� ji� maj� hodnotu)
     * @return true-lze po��tat, false-nelze po��tat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadan�ho spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrac� typ bloku
     * @return string "COMBAT"
     */
    string      getType(){return "COMBAT";}

};


class ItemApply : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 1. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort1 p�ipojen k jin�mu bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort1  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 2. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (ACCESSORIES*)
     */
    void*       IPort2;	//PREDMET
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort2 p�ipojen k jin�mu bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort2  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort2 p�ivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Gods, nese v�sledek v�po�tu
     */
    Gods*       OPort1;


    ///metody

    /**
                 * @brief Konstruktor, p�i�ad� bloku jeho unik�tn� ID, inicializuje hodnoty atributu, p�id� blok do
                 * seznamu blok�
                 */
                ItemApply(unsigned int);
    /**
                * @brief Destruktor bloku ItemApply, ru�� p��choz� spoje
                */
                ~ItemApply();
     /**
     * @brief Metoda dopl�ujic� chyb�jic� porty, prov�d�jic� v�po�et a distribujic� v�sledek
     */
    void        eval();
    /**
     * @brief Metoda, vol�na pri pokusu p�ipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujic� inormace o �sp�chu/ne�sp�chu/p�ipojen�m portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrac� datov� typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zji��uje, zda je blok p�ipraven na vyhodnocen�
     * (IPorty, kter� berou data z jin�ch blok� ji� maj� hodnotu)
     * @return true-lze po��tat, false-nelze po��tat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadan�ho spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrac� typ bloku
     * @return string "ITEMAPPLY"
     */
    string        getType(){return "ITEMAPPLY";}
};

class DiceThrow : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 1. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort1; //BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort1 p�ipojen k jin�mu bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort1  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief Ukazatel na Gods, nese v�sledek v�po�tu
     */
    Gods*       OPort1;

    ///metody

    /**
                * @brief Konstruktor, p�i�ad� bloku jeho unik�tn� ID, inicializuje hodnoty atributu, p�id� blok do
                * seznamu blok�
                */
                DiceThrow(unsigned int);
    /**
                * @brief Destruktor bloku DiceThrow, ru�� p��choz� spoje
                */
                ~DiceThrow();
    /**
                * @brief Metoda dopl�ujic� chyb�jic� porty, prov�d�jic� v�po�et a distribujic� v�sledek
                */
    void        eval();
    /**
     * @brief Metoda, vol�na pri pokusu p�ipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujic� inormace o �sp�chu/ne�sp�chu/p�ipojen�m portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrac� datov� typ OPortu bloku
     * @return string "Gods"
     */
    string      getOut() { return "Gods"; }
    /**
     * @brief Zji��uje, zda je blok p�ipraven na vyhodnocen�
     * (IPorty, kter� berou data z jin�ch blok� ji� maj� hodnotu)
     * @return true-lze po��tat, false-nelze po��tat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadan�ho spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrac� typ bloku
     * @return string "DICETHROW"
     */
    string      getType(){return "DICETHROW";}
};

class ArenaSelect : public Block {
public:
    ///I/O Porty

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 1. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort1;	//BUH
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort1 p�ipojen k jin�mu bloku
     */
    bool        IPort1_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort1  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort1_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort1_Connection;

    /**
     * @brief void ukazatel, implicitn� NULL, data reprezentuje data jdouc� do 2. portu.
     * V r�mci bloku je ukazatel p�etypov�n na (Gods*)
     */
    void*       IPort2;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda je IPort2 p�ipojen k jin�mu bloku
     */
    bool        IPort2_Connected;
    /**
     * @brief Booleansk� prom�nn�, ud�v�, zda byla v r�mci v�po�tu do IPort2  p�iveden v�sledek jin�ho bloku
     */
    bool        IPort2_Initiated;
    /**
     * @brief Ukazatel na Connect, ud�v� spojen�, kter� je do IPort1 p�ivedeno
     */
    Connect*    IPort2_Connection;

    /**
     * @brief Ukazatel na Arena, nese v�sledek v�po�tu
     */
    Arena*      OPort1; //BUH

    ///metody

    /**
                * @brief Konstruktor, p�i�ad� bloku jeho unik�tn� ID, inicializuje hodnoty atributu, p�id� blok do
                * seznamu blok�
                */
                ArenaSelect(unsigned int);
    /**
                * @brief Destruktor bloku ArenaSelect, ru�� p��choz� spoje
                */
                ~ArenaSelect();
    /**
                * @brief Metoda dopl�ujic� chyb�jic� porty, prov�d�jic� v�po�et a distribujic� v�sledek
                */
    void        eval();
    /**
     * @brief Metoda, vol�na pri pokusu p�ipojit se k IN portu bloku
     * @return Odkaz na strukturu PortStuff, obsahujic� inormace o �sp�chu/ne�sp�chu/p�ipojen�m portu
     */
    PortStuff*  tryConnect(string, Connect*);
    /**
     * @brief Vrac� datov� typ OPortu bloku
     * @return string "Arena"
     */
    string      getOut() { return "Arena"; }
    /**
     * @brief Zji��uje, zda je blok p�ipraven na vyhodnocen�
     * (IPorty, kter� berou data z jin�ch blok� ji� maj� hodnotu)
     * @return true-lze po��tat, false-nelze po��tat
     */
    bool        askReady();
    /**
     * @brief Provede reset hodnot v bloku
     */
    void        Reset();
    /**
     * @brief Odpojuje blok od zadan�ho spoje
     */
    void        Disconnect(Connect*);
    /**
     * @brief Vrac� typ bloku
     * @return string "ARENASELECT"
     */
    string      getType(){return "ARENASELECT";}
};



#endif
