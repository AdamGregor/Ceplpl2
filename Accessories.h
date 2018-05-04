/**
 *@file Accessories.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor imlementujicí datový typ Předmět
 */


#ifndef ACCESSORIES_H
#define ACCESSORIES_H
#include <string>
using namespace std;
/**
 * celkový počet předmětů
 */
#define ITEM_COUNT 5




/**
 * @brief Base class Accessories, dedi z ni konkretni predmety, kteri bohove mohou pouzivat
 */
class Accessories {
protected:
    /**
     * @brief Atributa určujicí efektivitu zbraně
     */
    double	Effect;
    /**
     * @brief Jméno předmětu
     */
    string	Name;

public:
    /**
     * @brief Viruální destruktor
     */
    virtual ~Accessories(){;}
    /**
     * @brief Metoda vrací efekt předmětu
     * @return double Effect
     */
    double	getEffect() { return Effect; }
    /**
     * @brief Metoda navracejicí jméno předmětu
     * @return string Name
     */
    string	getName() { return Name; }
};

//Predmey

/**
 * @brief Třída reprezentujicí předmět "Leviathan Axe"
 */
class LeviathanAxe : public Accessories {
public:
    ~LeviathanAxe(){;}
    LeviathanAxe() {
        Effect = 7.0;
        Name = "Leviathan Axe";
    }
};

/**
 * @brief Třída reprezentujicí předmět "Curse"
 */
class Curse : public Accessories {
public:
    ~Curse(){;}
    Curse() {
        Effect = -10.0;
        Name = "Curse";
    }
};

/**
 * @brief Třída reprezentujicí předmět "Scroll of Wisdom"
 */
class ScrollOfWisdom : public Accessories {
public:
    ~ScrollOfWisdom(){;}
    ScrollOfWisdom() {
        Effect = 4.0;
        Name = "Scroll Of Wisdom";
    }
};

/**
 * @brief Třída reprezentujicí předmět "Piety"
 */
class Piety : public Accessories {
public:
    ~Piety(){;}
    Piety() {
        Effect = 3.0;
        Name = "Piety";
    }
};

/**
 * @brief Třída reprezentujicí předmět "Impiety"
 */
class Impiety : public Accessories {
public:
    ~Impiety(){;}
    Impiety() {
        Effect = -3.0;
        Name = "Impiety";
    }
};


#endif
