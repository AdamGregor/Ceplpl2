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
 * @brief Třída MainWindow, dědí od QMainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor
     * @param rodič
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief Ověří umístění bloku v okně
     * @param Xová souřadnice bloku
     * @param Yová souřadnice bloku
     */
    void checkPlacement(int* x, int* y);

    /**
     * @brief Emituje signál v případě, že velikost okna byla změněna
     * @param událost změny okna
     */
    void resizeEvent(QEvent* event);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně boha
     * @param ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořeného boha
     */
    void* getGod(unsigned int ID);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně arény
     * @param ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořenou arenu
     */
    void* getArena(unsigned int ID);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně věc
     * @param ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořenou věc
     */
    void* getItem(unsigned int ID);

    /**
     * @brief zvýraznění bloku s daným ID
     * @param ID
     */
    void highlightBlock(unsigned int ID);

    /**
     * @brief zruší zvýraznění bloku
     * @param ID
     */
    void unhighlightBlock(unsigned int ID);

    /**
     * @brief Vypíše výsledek přepočtu bloku
     * @param typ bloku (0 = buh, 1 = arena, 2 = vec)
     * @param ID bloku
     * @param ukazatel na výsledek
     */
    void printResult(int typ, unsigned int ID, void* data);

    /**
     * @brief Vypíše hlášku o cyklech v bloku
     */
    void printCycle();

private:
    /**
     * @brief Xová souřadnice bodu při vytvoření bloku
     */
    int Spawn_x;

    /**
     * @brief Yová souřadnice bodu při vytvoření bloku
     */
    int Spawn_y;

    /**
     * @brief ukazatel na grafickou scénu
     */
    QGraphicsScene* scene;

    /**
     * @brief ukazatel na pero, kterým se malují spoje
     */
    QPen* pen;

    /**
     * @brief ukazatel na právě tvořený spoj
     */
    connection* active_connection;

    /**
     * @brief seznam existujících bloků
     */
    BlockList* blocks;

    /**
     * @brief sezanm existujících spojení
     */
    blockConnect* listConn;

    /**
     * @brief userinterface
     */
    Ui::MainWindow *ui;

    /**
     * @brief hodnota pro generování ID bloků
     */
    unsigned int blocks_ID;

    /**
     * @brief název souboru pro ukládání/načítaní
     */
    QString filename;


private slots:

    /**
     * @brief vypíše help
     */
    void printHelp();

    /**
     * @brief vytvoří Combat blok
     */
    void addCombat();

    /**
     * @brief vytvoří Dice blok
     */
    void addDice_throw();

    /**
     * @brief vytvoří Item blok
     */
    void addItem_apply();

    /**
     * @brief vytvoří Arena blok
     */
    void addArena_select();

    /**
     * @brief vytvoří Rest blok
     */
    void addRest();

    /**
     * @brief přemístí blok tam, kde se nachází kursor myši pří puštění pravého tlačítka myši
     * @param blok, který se má přemístit
     */
    void mouseRelease(MyLabel* block);

    /**
     * @brief vytváří spojení mezi bloky na které se klikne
     * @param blok pro spojení
     */
    void mousePress(MyLabel* block);

    /**
     * @brief smaže blok
     * @param blok pro vymazání
     */
    void deleteSlot(MyLabel* block);

    /**
     * @brief spustí výpočet
     */
    void run();

    /**
     * @brief provede krok výpočtu
     */
    void stepIt();

    /**
     * @brief vše smaže a vytvoří nové schéma
     */
    void newScheme();

    /**
     * @brief načte schéma ze souboru
     */
    void load();

    /**
     * @brief uloží schéma do souboru
     */
    void save_as();

    /**
     * @brief provede rychlé uložení
     */
    void quickSave();

    /**
     * @brief změní umístění bloků při změně velikosti okna
     */
    void doResized();

    /**
     * @brief resetuje výpočet
     */
    void resetIt();

signals:
    /**
     * @brief signál při změně velikosti okna
     */
    void resized();

};

#endif // MAINWINDOW_H
