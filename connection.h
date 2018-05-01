/**
 *@file connection.h
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief  connection between blocks for gui
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
 * @brief Structure for list of connections
 */

struct ListItem{
    connection* data;
    ListItem* next;
};

/**
 * @brief Structure for list of IDs of blocks, that are connectet
 */
struct blockConn{
    unsigned int first_ID;
    unsigned int second_ID;
    blockConn* next;
};

/**
 * @brief The connection class, inherits from QGraphicsLineItem
 */

class connection : public QGraphicsLineItem{

    /**
     * @brief This blocks out port is connected
     */
    MyLabel* outBlock;
    /**
     * @brief X coordinate of out port
     */
    int out_x;
    /**
     * @brief Y coordinate of out port
     */
    int out_y;

    /**
     * @brief This blocks in port is connected
     */
    MyLabel* inBlock;
    /**
     * @brief X coordinate of in port
     */
    int in_x;
    /**
     * @brief Y coordinate of in port
     */
    int in_y;

    /**
     * @brief Number of clicks, if ==2, it will make a connection
     */
    int num_of_clicks;


public:
    /**
     * @brief Construktor
     * @param parent
     */
    connection(QWidget* parent = 0);
    /**
     * @brief Sets out block
     * @param block
     */
    void setOutblock(MyLabel* block);
    /**
     * @brief Sets in block
     * @param block
     */
    void setInblock(MyLabel* block);
    /**
     * @brief Sets coordinates of Out port
     * @param x
     * @param y
     */
    void setOutcoords(int* x, int* y);
    /**
     * @brief Loads coordinates of Out port in x, y
     * @param x
     * @param y
     */
    void getOutcoords(int* x, int* y);
    /**
     * @brief Sets coordinates of In port
     * @param x
     * @param y
     */
    void setIncoords(int* x, int* y);
    /**
     * @brief Loads coordinates of In port in x, y
     * @param x
     * @param y
     */
    void getIncoords(int* x, int* y);
    /**
     * @brief Increment number of clicks
     */
    void incNumOfClicks();
    /**
     * @brief Get number of clicks
     * @return value of number of clicks
     */
    int getNumOfClicks();
    /**
     * @brief Get Out block
     * @return out block
     */
    MyLabel* getOutBlock();
    /**
     * @brief Get In block
     * @return in block
     */
    MyLabel* getInBlock(){return inBlock;}
};

/**
 * @brief The connectionList class
 */
class connectionList{
    /**
     * @brief First item of list of connections
     */
    ListItem* first;
    /**
     * @brief lenght of list
     */
    int lenght;

public:
    /**
     * @brief constructor
     */
    connectionList();
    /**
     * @brief insert connection in connection list
     * @param item
     */
    void insert(connection* item);

    /**
     * @brief deletes a connection between blocks that are connected with block with block_ID
     * @param block_ID
     * @param out  finding block_ID in out list
     */
    void deleteConnection(unsigned int block_ID, bool out);

    /**
     * @brief getListLenght
     * @return lenght
     */
    int getListLenght();

    /**
     * @brief getFirst
     * @return pointer to first item of connections list
     */
    ListItem* getFirst();
};



class blockConnect{
    blockConn* first;
    int lenght;

public:
    /**
     * @brief constructor
     */
    blockConnect();

    /**
     * @brief insert IDs of blocks that are connected
     * @param first ID
     * @param second ID
     */
    void insert(int first_ID, int second_ID);

    /**
     * @brief getFirst
     * @return pointer to first item of list of IDs pf blocks that are connected
     */
    blockConn* getFirst();

    /**
     * @brief delete item of list, that has same IDs as those given by parametres
     * @param first ID
     * @param second ID
     */
    void deleteConn(int first_ID, int second_ID);

    /**
     * @brief returns lenght of list of blocks that are connected
     * @return int
     */
    int getListlenght();
};



#endif // CONNECTION_H





