/**
 *@file mainwindow.h
 *@author Zdeněk Jelínek (xjelin47)
 *@author Adam Gregor (xgrego18)
 *@brief hlavičkový soubor pro hlavní okno aplikace
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
 * @brief Třída MainWindow, dědí od QMainWindow, představuje hlavní okno aplikace.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor.
     * Nastaví se velikost okna podle velikosti monitoru a jeho další potřebné nastavení. Dále se nastaví grafická scéna. Propojí se signály okna s odpovídajícími sloty.
     * Alokuje se paměť pro seznam s bloky spojeními.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    /**
     * @brief Ověří umístění bloku v okně.
     * Kontrola souřadnic bloku. Pokud jsou mimo okno, přepočítá se na nejbližší možné místo v okně.
     * @param x Xová souřadnice bloku
     * @param y Yová souřadnice bloku
     */
    void checkPlacement(int* x, int* y);

    /**
     * @brief Emituje signál v případě, že velikost okna byla změněna.
     * @param event událost změny okna
     */
    void resizeEvent(QEvent* event);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně boha.
     * @param ID ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořeného boha
     */
    void* getGod(unsigned int ID);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně arény.
     * @param ID  ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořenou arenu
     */
    void* getArena(unsigned int ID);

    /**
     * @brief Zažádá uživatele o zadání vstupu, konkrétně věc.
     * @param ID ID bloku do kterého se zadá vstup
     * @return ukazatel na vytvořenou věc
     */
    void* getItem(unsigned int ID);

    /**
     * @brief zvýraznění bloku s daným ID.
     * @param ID
     */
    void highlightBlock(unsigned int ID);

    /**
     * @brief zruší zvýraznění bloku.
     * @param ID
     */
    void unhighlightBlock(unsigned int ID);

    /**
     * @brief Vypíše výsledek přepočtu bloku.
     * @param typ typ bloku (0 = buh, 1 = arena, 2 = vec)
     * @param ID ID bloku
     * @param data ukazatel na výsledek
     */
    void printResult(int typ, unsigned int ID, void* data);

    /**
     * @brief Vypíše hlášku o cyklech v bloku.
     */
    void printCycle();

    /**
     * @brief vypíše hlášku o resetování výpočtu.
     */
    void printReset();

private:
    /**
     * @brief Xová souřadnice bodu při vytvoření bloku.
     */
    int Spawn_x;

    /**
     * @brief Yová souřadnice bodu při vytvoření bloku.
     */
    int Spawn_y;

    /**
     * @brief ukazatel na grafickou scénu.
     */
    QGraphicsScene* scene;

    /**
     * @brief ukazatel na pero, kterým se malují spoje.
     */
    QPen* pen;

    /**
     * @brief ukazatel na právě tvořený spoj.
     */
    connection* active_connection;

    /**
     * @brief seznam existujících bloků.
     */
    BlockList* blocks;

    /**
     * @brief sezanm existujících spojení.
     */
    blockConnect* listConn;

    /**
     * @brief userinterface.
     */
    Ui::MainWindow *ui;

    /**
     * @brief hodnota pro generování ID bloků.
     */
    unsigned int blocks_ID;

    /**
     * @brief název souboru pro ukládání/načítaní.
     */
    QString filename;

    /**
     * @brief počet vytvořených bloků, pokud je větší jak 50, Spawn_x a Spawn_y se resetuje na původní hodnoty, stejně tak tato hodnota.
     */
    int spawnCount;


private slots:

    /**
     * @brief vypíše nápovědu k používání aplikace.
     */
    void printHelp();

    /**
     * @brief vytvoří Combat blok.
     * Nastaví se ID a typ (COMBAT) bloku. Propojí se signály s odpovídajícími sloty. Nastaví se umístění bloku v okně.
     * Vytvoří se label, který grafiky zobrazuje ID bloku. Vytvoří se logický blok COMBAT.
     */
    void addCombat();

    /**
     * @brief vytvoří Dice blok.
     * Nastaví se ID a typ (DICE) bloku. Propojí se signály s odpovídajícími sloty. Nastaví se umístění bloku v okně.
     * Vytvoří se label, který grafiky zobrazuje ID bloku. Vytvoří se logický blok DICE.
     */
    void addDice_throw();

    /**
     * @brief vytvoří Item blok.
     * Nastaví se ID a typ (ITEM) bloku. Propojí se signály s odpovídajícími sloty. Nastaví se umístění bloku v okně.
     * Vytvoří se label, který grafiky zobrazuje ID bloku. Vytvoří se logický blok ITEM.
     */
    void addItem_apply();

    /**
     * @brief vytvoří Arena blok.
     * Nastaví se ID a typ (ARENA) bloku. Propojí se signály s odpovídajícími sloty. Nastaví se umístění bloku v okně.
     * Vytvoří se label, který grafiky zobrazuje ID bloku. Vytvoří se logický blok ARENA.
     */
    void addArena_select();

    /**
     * @brief vytvoří Rest blok.
     * Nastaví se ID a typ (REST) bloku. Propojí se signály s odpovídajícími sloty. Nastaví se umístění bloku v okně.
     * Vytvoří se label, který grafiky zobrazuje ID bloku. Vytvoří se logický blok REST.
     */
    void addRest();

    /**
     * @brief přemístí blok tam, kde se nachází kursor myši pří puštění pravého tlačítka myši.
     * Při změně pozice bloku se zkontroluje, jestli má povolené souřadnice. Pokud ne, umístí se
     * na nejbližší možné místo. Dále se přepočítá pozice všech spojů, které jsou napojeny na tento blok.
     * @param block blok, který se má přemístit
     */
    void mouseRelease(MyLabel* block);

    /**
     * @brief vytváří spojení mezi bloky na které se klikne.
     * Při tvoření spojení se kontroluje, zda má blok kompatibilní porty a zda je nemá zaplněné.
     * Pokud je možné spojení vytvořit, bloky se graficky spojí a alokuje se paměť pro logické spojení.
     * @param block blok pro spojení
     */
    void mousePress(MyLabel* block);

    /**
     * @brief smaže blok.
     * Pokud je tlačítko Delete zamáčknuté, může se blok odstranit. Při tom se odtraní i logický blok a grafické i logické
     * spoje.
     * @param block blok pro vymazání
     */
    void deleteSlot(MyLabel* block);

    /**
     * @brief spustí výpočet.
     */
    void run();

    /**
     * @brief provede krok výpočtu.
     */
    void stepIt();

    /**
     * @brief vše smaže a připraví aplikaci pro nové schéma.
     */
    void newScheme();

    /**
     * @brief načte schéma ze souboru.
     * Požádá uživatele o zadání souboru ze kterého se má schéma načíst.
     * Po zadání se rozpracované schéma odstraní a načtou se bloky se spoji.
     */
    void load();

    /**
     * @brief uloží schéma do souboru.
     */
    void save_as();

    /**
     * @brief provede rychlé uložení.
     */
    void quickSave();

    /**
     * @brief změní umístění bloků při změně velikosti okna.
     */
    void doResized();

    /**
     * @brief resetuje výpočet.
     */
    void resetIt();

    /**
     * @brief vypíše informace o aplikaci.
     */
    void printAbout();

signals:
    /**
     * @brief signál při změně velikosti okna.
     */
    void resized();

};

#endif // MAINWINDOW_H
