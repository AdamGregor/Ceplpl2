/**
 *@file Execute.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor pro to třídy obsluhujicí Run/Step/Reset/Remove
 */

#ifndef  EXECUTE_H
#define EXECUTE_H
#include "Blocks.h"
/**
 * @brief Struktura, jíž je tvořen seznam vytvořených bloků
 */
struct BlocklistElem {
    Block*          Data;
    BlocklistElem*  next;
};

/**
 * @brief Třída zprostředkujicí seznam bloků a práci nad ním
 */
class  Blocklist {
public:
    /**
     * @brief Ukazatel na prví položku seznamu bloků
     */
    BlocklistElem*  first;

    /**
     * @brief Konstruktor, nastaví první prvek seznamu bloků na null
     */
    Blocklist() { first = nullptr; }

    /**
     * @brief Metoda přidavajicí prvek do seznamu bloků
     */
    void            addItem(Block*);

    /**
     * @brief Metoda zjištujicí první prvek seznamu bloků
     * @return Odkaz na strukturu obsahujicí první blok v seznamu bloků
     */
    BlocklistElem*	getFirst() { return first; }
};

/**
 * @brief Třída obsluhujicí hlavní funkčnost programu (Run/Step/Remove/Reset)
 */
class Execute{
    /**
     * @brief Ukazatel na třídu BLOCKLIST, obsluhujicí seznam bloků
     */
    Blocklist*      Blocks;
    /**
     * @brief Atribut uchovávajicí záznam kolik bloků již bylo vyhodnoceno od posledního RESETu
     */
    int             Done;
    /**
     * @brief Atribut uchovávajicí záznam kolik bloků v řadě nebylo možno vyhodnotit. Využívá se při detekci cyklu
     */
    int             NotReadyInRow;
    /**
     * @brief Atribut poskytujicí údaj zda byly všechny bloky vyhodnoceny
     */
    bool            Completed;
    /**
     * @brief Uchovává číslo naposledy zvýrazněného bloku
     */
    unsigned int previous;

public:
    /**
     * @brief Celkový počet aktivních bloků
     */
    int Block_count;

    /**
     * @brief Konstruktor, inicializuje seznam bloků, nastaví výchozí hodnoty atributů
     */
    Execute();

    /**
     * @brief Metoda přidávající blok do seznamu bloků
     * @param Odkaz na přidávaný blok
     */
    void            AddBlock(Block *new_block);
    /**
     * @brief Spouštěč všech bloků, seznam bloků je dokola projížděn vykonávajíce bloky jež jsou připraveny.
     *  Končí vykonáním všech bloků nebo nalezením cyklu.
     */
    void            Run();
    /**
     * @brief Krokovač, seznam bloků je dokola projížděn vykonávajíce bloky jež jsou připraveny.
     *  Končí vykonáním všech bloků nebo nalezením cyklu.
     */
    void            Step();
    /**
     * @brief Reset výpočtu, schéma je vráceno do stavu před výpočtem
     */
    void            Reset();
    /**
     * @brief Metoda odstraňujicí bloky ze seznamu
     * @param Adresa bloku k odstranění
     */
    void            Remove(Block* Block_to_remove);
};

#endif // ! EXECUTE_H
