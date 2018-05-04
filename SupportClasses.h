/**
 *@file SupportClasses.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor deklarujicí třídy řídící program a jejich metody.
 */

#ifndef SUPP_H
#define SUPP_H
#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"
#include <string>
using namespace std;

class Block;

/**
 * @brief Struktura, kterou vrací blok po pokusu o navázání kontaktu
 */
struct PortStuff {
    ///ukazatel na připojený port (null pokud nedošlo ke spojení)
    void*           value;
    ///ukazatel na booleanskou proměnnou, říkajicí zda je v portu hodnota
    bool*           init;
    ///typ bloku
    string          blockType;
};

/**
 * @brief Třída zprostředkujicí spoje bloků
 */
class Connect {
public:
    /**
 * @brief string nesoucí typ přenášených dat
 */
    string          Data_type;
    /**
 * @brief boolean, říkajicí zda již byl v aktualním výpočtu spoj využit
 */
    bool            transfered;
    /**
 * @brief Struktura, jež je vracena portem, ke kterému se chce spoj připojit
 */
    PortStuff*      reaction;
    /**
 * @brief Číselná hodnota, která spojem prošla
 */
    double          value;
    /**
 * @brief Řetězec, jež spojem  prošel
 */
    string          name;

    /**
 * @brief Ukazat na blok, k jehož OUTpotru je spoj připojen
 */
    Block*          in;
    /**
 * @brief Typ bloku, k němuž je spoj připojen
 */
    string          in_name;
      /**
 * @brief Ukazat na blok, k jehož INpotru je spoj připojen
 */
    Block*          out;
        /**
 * @brief Typ bloku, k němuž je spoj připojen
 */
    string          out_name;

        /**
     * @brief Konstruktor spoje, snaží se propojit 2 bloky
     * @param Odkaz na blok, k jehož OPortu se chci připojit
     * @param Odkaz na blok, k jehož IPortu se chci připojit
     * @param Odkaz na proměnnou, do níž zapíši, zda se spojení povedlo
     */
                    Connect(Block *blok, Block *blok2, bool* ok);
    /**
     * @brief Metoda posílajicí inormaci o přenosu informace
     * @return true-informace již prošla, false-ještě ne
     */
    bool            GetTransfered(){return transfered;}
    /**
     * @brief Metoda posílajicí inormaci o přenosu informace
     * @return číselná hodnota, jež spojem prošla
     */
    double          GetValue(){return value;}
    /**
     * @brief Metoda posílajicí inormaci o přenosu informace
     * @return řetězec obsahjujicí typ dat, který prošel spojem
     */
    string          GetName(){return name;}
        /**
     * @brief Metoda odpojujicí jeden z konců spoje.
     * @param 0-cho odpojit Block2 (out), 1-Chci odpojit Block1 (in)
     */
    void            Disconnect(int);
        /**
     * @brief Metoda posílajicí data z OPortu prvího bloku do IPortu druhého bloku
     */
    void            DistributeResult(void *,double, string);
        /**
     * @brief Metoda resetujicí informace o přenosu informace
     */
    void            Reset(){transfered = false; value = -1; name = "None";}
};

/**
 * @brief Struktura, jejíž seznam obsahuji OPorty, aby si zapamatovaly veškeré své odběratele
 */
struct ListItemLogic {
    Connect*        data;
    ListItemLogic*  next;
};

/**
 * @brief Třída seznam spojů jdoucích z OPortu
 */
class SubscribeList {
public:
    /**
 * @brief Ukazatel na první prvek seznamu
 */
    ListItemLogic*  first;
    /**
 * @brief Atribut udávajicí délku seznamu
 */
    int             listLenght;

        /**
     * @brief Konstruktor, inicializuje počáteční hodnoty
     */
                    SubscribeList() { this->first = nullptr ;  this->listLenght = 0; }
        /**
     * @brief Metoda vracejicí délku seznamu
     */    
    int             getLenght() { return this->listLenght; }
     /**
     * @brief Metoda vracejicí ukazatel na prví položku seznamu
     */
    ListItemLogic*  getFirst() { return this->first; }
            /**
     * @brief Metoda vkládajicí nový prvek do seznamu
     */
    void            InsertItem(Connect *);
        /**
     * @brief Metoda odebírajicí prvek ze seznamu
     */
    void            RemoveItem(Connect *);
};

#endif
