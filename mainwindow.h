/**
 *@file mainwindow.h
 *@author Zdenek Jelinek (xjelin47), Adam Gregor (xgrego18)
 *@brief mainwindow of app
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QGraphicsScene>
#include <QPen>
#include "mylabel.h"
#include "connection.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"
#include "Gods.h"
#include "Execute.h"
#include "SupportClasses.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class, inherits form QWainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief constructor
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief Checks placement of cursor given by the x and y
     * @param x
     * @param y
     */
    void checkPlacement(int* x, int* y);

    /**
     * @brief emits signal if window is resized
     * @param event
     */
    void resizeEvent(QResizeEvent* event);

    /**
     * @brief get God from user
     * @param ID of block
     * @return pointer to God
     */
    void* getGod(unsigned int ID);

    /**
     * @brief get Arena from user
     * @param ID of block
     * @return pointer to Arena
     */
    void* getArena(unsigned int ID);

    /**
     * @brief get Item from user
     * @param ID of block
     * @return pointer to Accessories
     */
    void* getItem(unsigned int ID);

private:
    /**
     * @brief X coordinate of spawn point
     */
    int Spawn_x;
    /**
     * @brief Y coordinate of spawn point
     */
    int Spawn_y;
    /**
     * @brief scene
     */
    QGraphicsScene* scene;
    /**
     * @brief pen
     */
    QPen* pen;
    /**
     * @brief current connection
     */
    connection* active_connection;

    /**
     * @brief list of existing blocks
     */
    BlockList* blocks;

    /**
     * @brief list of existing connections
     */
    blockConnect* listConn;

    /**
     * @brief ui
     */
    Ui::MainWindow *ui;
    /**
     * @brief this will generate ID for blocks
     */
    unsigned int blocks_ID;

    /**
     * @brief name of saved file
     */
    QString filename;


private slots:
    /**
     * @brief prints hHelp
     */
    void printHelp();
    /**
     * @brief add Combat block
     */
    void addCombat();
    /**
     * @brief add Dice throw block
     */
    void addDice_throw();
    /**
     * @brief add Item apply block
     */
    void addItem_apply();
    /**
     * @brief add Arena select block
     */
    void addArena_select();
    /**
     * @brief add Rest block
     */
    void addRest();
    /**
     * @brief mouse button release
     * @param block
     */
    void mouseRelease(MyLabel* block);
    /**
     * @brief mouse button Press
     * @param block
     */
    void mousePress(MyLabel* block);
   // void mouseDoubleClick(MyLabel* block);
    /**
     * @brief delete block or connection
     * @param block
     */
    void deleteSlot(MyLabel* block);
    /**
     * @brief run
     */
    void run();

    /**
     * @brief deletes all and makes a new scheme
     */
    void newScheme();

    /**
     * @brief load a scheme
     */
    void load();

    /**
     * @brief save a scheme under given name
     */
    void save_as();

    /**
     * @brief quick save
     */
    void quickSave();

    /**
     * @brief changes placement of blocks in order to be in window
     */
    void doResized();

    /**
     * @brief resets evaluation
     */
    void resetIt();

signals:
    void resized();

};

#endif // MAINWINDOW_H
