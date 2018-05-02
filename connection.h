/**
 *@file connection.h
 *@author Zdeněk Jelínek (xjelin47), Adam Gregor (xgrego18)
 *@brief  Hlavičkový soubor pro grafické spoje mezi bloky
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include "mylabel.h"

#include <QObject>
#include <QWidget>
#include <QGraphicsLineItem>
#include <QGraphicsItem>
#include <QHoverEvent>

class connection;
class MyLabel;

/**
 * @brief Struktura pro seznam spojů
 */

struct ListItem{
    connection* data;
    ListItem* next;
};

/**
 * @brief Struktura pro seznam ID bloků, které jsou spojeny
 */
struct blockConn{
    unsigned int first_ID;
    unsigned int second_ID;
    blockConn* next;
};

/**
 * @brief Třída connection, dědí od QGraphicsLineItem
 */

class connection : public QObject, public QGraphicsLineItem{

    Q_OBJECT
    /**
     * @brief Ukazatel na blok, jehož out port je spojen
     */
    MyLabel* outBlock;
    /**
     * @brief Xová souřadnice out portu
     */
    int out_x;
    /**
     * @brief Yová souřadnice out portu
     */
    int out_y;

    /**
     * @brief Ukazatel na blok, jehož in port je spojen
     */
    MyLabel* inBlock;
    /**
     * @brief Xová souřadnice in portu
     */
    int in_x;
    /**
     * @brief Yová souřadnice in portu
     */
    int in_y;

    /**
     * @brief Počet kliků pravého tlačítka na myši, pokud se rovná 2, nakreslí se spojení
     */
    int num_of_clicks;

public:
    /**
     * @brief Kontruktor
     */
    connection();

    /**
     * @brief Nastaví outBlock
     * @param ukazatel na blok
     */
    void setOutblock(MyLabel* block);

    /**
     * @brief Nastaví inBlock
     * @param ukazatel na blok
     */
    void setInblock(MyLabel* block);

    /**
     * @brief Nastaví koordináty out portu
     * @param Xová souřadnice
     * @param Yová souřadnice
     */
    void setOutcoords(int* x, int* y);

    /**
     * @brief Nahraje souřadnice out portu do parametrů x, y
     * @param x
     * @param y
     */
    void getOutcoords(int* x, int* y);

    /**
     * @brief Nastaví koordináty in portu
     * @param x
     * @param y
     */
    void setIncoords(int* x, int* y);

    /**
     * @brief Nahraje souřadnice in portu do parametrů x, y
     * @param x
     * @param y
     */
    void getIncoords(int* x, int* y);

    /**
     * @brief Inkrementuje hodnotu num_of_clicks
     */
    void incNumOfClicks();

    /**
     * @brief Vrátí hodnotu num_of_clicks
     * @return integer
     */
    int getNumOfClicks();

    /**
     * @brief Vrátí ukazatel outBlocku
     * @return ukazatel na MyLabel
     */
    MyLabel* getOutBlock();

    /**
     * @brief Vrátí ukazatel inBlocku
     * @return ukazatel na MyLabel
     */
    MyLabel* getInBlock(){return inBlock;}

    /**
     * @brief Událost, kdy je myš nad spojem, nastaví tooltip spoje
     * @param událost
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

    /**
     * @brief Udalost, kdy mys opousti spoj
     * @param udalost
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

};

/**
 * @brief Třída connectionList, ukládá ukazatele na connection v strukture ListItem
 */
class connectionList{
    /**
     * @brief První prvek seznamu
     */
    ListItem* first;
    /**
     * @brief délka seznamu
     */
    int lenght;

public:
    /**
     * @brief konstruktor
     */
    connectionList();
    /**
     * @brief Vloží ukazatel na connection do seznamu
     * @param ukazatel na connection
     */
    void insert(connection* item);

    /**
     * @brief odstraní connection ze seznamu,
     * @param ID bloku, který obsahuje connection
     * @param out  hledá blok v out listu pokud je true
     */
    void deleteConnection(unsigned int block_ID, bool out);

    /**
     * @brief zjistí délku seznamu
     * @return vrací hodnotu délky seznamu
     */
    int getListLenght();

    /**
     * @brief vrací první prvek seznamu
     * @return ukazatel na první prvek seznamu
     */
    ListItem* getFirst();
};


/**
 * @brief Třída blockConnect, ukládá ID dvojice ID bloků, které jsoú spojeny
 */
class blockConnect{
    /**
     * @brief ukazatel na první prvek seznamu
     */
    blockConn* first;

    /**
     * @brief délka seznamu
     */
    int lenght;

public:
    /**
     * @brief konstruktor
     */
    blockConnect();

    /**
     * @brief vloží do seznamu dvojici ID bloků, které jsou spojeny
     * @param první ID
     * @param druhé ID
     */
    void insert(int first_ID, int second_ID);

    /**
     * @brief vrací ukazatel na první prvek seznamu
     * @return ukazatel na první prvek sezanmu
     */
    blockConn* getFirst();

    /**
     * @brief odstraní prvek seznamu, který má stejná ID jako dané parametry
     * @param první ID
     * @param druhé ID
     */
    void deleteConn(unsigned int first_ID, unsigned int second_ID);

    /**
     * @brief vrací délku seznamu
     * @return délka seznamu
     */
    int getListlenght();
};



#endif // CONNECTION_H





