/**
 *@file mylabel.h
 *@author Zdeněk Jelínek (xjelin47)
 *@author Adam Gregor (xgrego18)
 *@brief  Hlavičkový soubor pro grafické bloky
 */

#ifndef MYLABEL_H
#define MYLABEL_H

#include "connection.h"
#include "Blocks.h"
#include "SupportClasses.h"

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class connection;
class connectionList;
class MyLabel;

/**
 * @brief typy bloků
 */
enum blockType {COMBAT, ITEM, DICE, REST, ARENA};


/**
 * @brief struktura pro seznam bloků
 */
struct Listblock{

    /**
     * @brief blok
     */
    MyLabel* data;

    /**
     * @brief ukazatel na další prvek seznamu
     */
    Listblock* next;
};


/**
 * @brief Třída MyLabel, dědí od QLabel, zaštiťuje především grafickou část bloků
 */
class MyLabel : public QLabel{

    Q_OBJECT

private:

    /**
     * @brief ID bloku
     */
    unsigned int block_ID;

    /**
     * @brief Ukazatel na label, do kterého se nahraje ID bloku a to se zobrazí v levém horním rohu bloku
     */
    MyLabel* IDlabel;

    /**
     * @brief typ bloku
     */
    blockType type;

    /**
     * @brief Xová souřadnice bloku
     */
    int x;

    /**
     * @brief Yová souřadnice bloku
     */
    int y;

    /**
     * @brief seznam spojů, které obsahuje out port tohoto bloku
     */
    connectionList* out_List;

    /**
     * @brief sezanm spojů, které obsahuje in port tohoto bloku
     */
    connectionList* in_List;

    /**
     * @brief logický blok, obsahující skutečná data
     */
    Block* logicBlock;

    /**
     * @brief logické spojení, tvořící skutečné spojení
     */
    Connect* logicConnect;


public:
    /**
     * @brief konstruktor
     * @param parent
     */
    MyLabel(QWidget *parent = 0);

    ~MyLabel();

    /**
     * @brief nastaví ID bloku
     * @param ID
     */
    void setID(unsigned int ID);

    /**
     * @brief vrací ID bloku
     * @return hodnota ID bloku
     */
    unsigned int getID();

    /**
     * @brief nastaví typ bloku
     * @param typ typ bloku
     */
    void setType(blockType typ);

    /**
     * @brief vrací typ bloku
     * @return typ bloku
     */
    blockType getType();

    /**
     * @brief nastaví koordináty bloku
     * @param x Xová souřadnice
     * @param y Yová souřadnice
     */
    void setCoords(int x, int y);

    /**
     * @brief nahraje koordináty bloku do parametrů
     * @param x
     * @param y
     */
    void getCoords(int* x, int *y);

    /**
     * @brief vrací ukazatel na out list
     * @return ukazatel na connectionList
     */
    connectionList* getOutList();

    /**
     * @brief vrací ukazatel na in list
     * @return ukazatel na connectionList
     */
    connectionList* getInList();

    /**
     * @brief nastaví ID label
     * @param label
     */
    void setIDlabel(MyLabel* label);

    /**
     * @brief vrací ukazatel na ID label
     * @return ukazatel na MyLabel
     */
    MyLabel* getIDlabel();

    /**
     * @brief vrací ukazatel na logické spojení
     * @return
     */
    Connect* getLogicconnect(){return logicConnect;}

public:

    /**
     * @brief událost, kdy se pustí tlačítko myši
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent* event);

    /**
     * @brief událost, kdy se zmáčkne tlačítko myši
     * @param event
     */
    void mousePressEvent(QMouseEvent* event);

    /**
     * @brief vrací ukazatel na logic block
     * @return ukazatel na Block
     */
    Block* getLogicblock();

    /**
     * @brief nastaví logic blok
     * @param logicBl ukazatel na Block
     */
    void setLogicblock(Block* logicBl);

    /**
     * @brief nastaví logicconnect
     * @param conn ukazatel na Connect
     */
    void setLogicconnect(Connect* conn);


signals:

    /**
     * @brief signál pro událost, kdy se na bloku pustí tlačítko myši
     * @param label blok na kterém se pustilo tlačítko myši
     */
    void mouseRelease(MyLabel* label);

    /**
     * @brief signál pro událost, kdy se na bloku zmáčkne tlačítko myši
     * @param label blok na kterém se zmáčklo tlačítko myši
     */
    void mousePress(MyLabel* label);

    /**
     * @brief signál pro smazání bloku
     * @param label blok, který se má smazat
     */
    void deleteSig(MyLabel* label);

};


/**
 * @brief Třída Blocklist, funguje jako začátek seznamu
 */
class BlockList{

    /**
     * @brief první prvek seznamu
     */
    Listblock* first;

    /**
     * @brief délka seznamu
     */
    int lenght;

public:

    /**
     * @brief konstruktor
     */
    BlockList();

    /**
     * @brief vloží blok do seznamu bloků
     * @param block blok, který se má vložit
     */
    void insert(MyLabel* block);

    /**
     * @brief smaže blok s daným ID
     * @param block_ID
     */
    void deleteBlock(unsigned int block_ID);

    /**
     * @brief vrací délku seznamu
     * @return délka seznamu
     */
    int getListLenght();

    /**
     * @brief vrací první prvek seznamu bloků
     * @return ukazatel na prvek seznamu
     */
    Listblock* getFirst();
};


#endif // MYLABEL_H
