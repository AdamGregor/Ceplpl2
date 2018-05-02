/**
 *@file mylabel.h
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief  blocks for gui
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
 * @brief Structure for list of blocks
 */
struct Listblock{
    MyLabel* data;
    Listblock* next;
};


/**
 * @brief The MyLabel class, inherits from QLabel
 */
class MyLabel : public QLabel{

    Q_OBJECT

private:

    /**
     * @brief ID
     */
    unsigned int block_ID;

    /**
     * @brief Label, ktery ukazuje ID bloku
     */
    MyLabel* IDlabel;

    /**
     * @brief type of block
     */
    blockType type;

    /**
     * @brief x coordinate of block
     */
    int x;

    /**
     * @brief y coordinate of block
     */
    int y;

    /**
     * @brief list of connections from out port
     */
    connectionList* out_List;

    /**
     * @brief list of connections from in port
     */
    connectionList* in_List;

    /**
     * @brief actuall block
     */
    Block* logicBlock;

    Connect* logicConnect;


public:
    /**
     * @brief constructor
     * @param parent
     */
    MyLabel(QWidget *parent = 0);

    /**
     * @brief sets ID for block
     * @param ID
     */
    void setID(unsigned int ID);

    /**
     * @brief return ID of block
     * @return unsigned int
     */
    unsigned int getID();

    /**
     * @brief sets type of a block
     * @param typ
     */
    void setType(blockType typ);
    /**
     * @brief returns a type of a block
     * @return blockType
     */
    blockType getType();
    /**
     * @brief sets coordinates of block
     * @param x
     * @param y
     */
    void setCoords(int x, int y);
    /**
     * @brief returns coordinates of a block in x and y
     * @param x
     * @param y
     */
    void getCoords(int* x, int *y);

    /**
     * @brief returns pointer to out list
     * @return connectionList*
     */
    connectionList* getOutList();
    /**
     * @brief returns pointer to in list
     * @return connectionList*
     */
    connectionList* getInList();

    /**
     * @brief nastavi ID label
     * @param label
     */
    void setIDlabel(MyLabel* label);

    /**
     * @brief vraci ID label
     * @return
     */
    MyLabel* getIDlabel();

public:
    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent* event);
    /**
     * @brief mousePressEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent* event);

    /**
     * @brief get logic block
     * @return pointer to logic block
     */
    Block* getLogicblock();

    /**
     * @brief set Logic block
     */
    void setLogicblock(Block* logicBl);

    /**
     * @brief nastavi logicke spojeni
     * @param conn
     */
    void setLogicconnect(Connect* conn);


signals:
    /**
     * @brief mouseRelease
     * @param block
     */
    void mouseRelease(MyLabel* label);
    /**
     * @brief mousePress
     * @param block
     */
    void mousePress(MyLabel* label);

    /**
     * @brief delete a block
     * @param block
     */
    void deleteSig(MyLabel* label);

};


/**
 * @brief BlockList class
 */
class BlockList{
    /**
     * @brief First item of list of blocks
     */
    Listblock* first;
    /**
     * @brief lenght of list
     */
    int lenght;

public:
    /**
     * @brief constructor
     */
    BlockList();

    /**
     * @brief insert block in blocks list
     * @param item
     */
    void insert(MyLabel* block);

    /**
     * @brief deletes a block
     * @param block_ID
     * @param out  finding block_ID in out list
     */
    void deleteBlock(unsigned int block_ID);

    /**
     * @brief getListLenght
     * @return lenght
     */
    int getListLenght();

    /**
     * @brief getFirst
     * @return pointer to first item of connections list
     */
    Listblock* getFirst();
};


#endif // MYLABEL_H
