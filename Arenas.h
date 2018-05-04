/**
 *@file Arenas.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor imlementujicí datový typ Aréna
 */

#ifndef ARENAS_H
#define ARENAS_H
#include <string>
using namespace std;

/**
 * @brief Base class Arena, dedi z ni konkretni areny
 */
class Arena {
protected:
    /**
     * @brief Atributa určujicí obecnout efektivitu. Konkrétní efekt se liší v závislosti na bohu
     */
    double	Effect;
    /**
     * @brief Jméno arény
     */
    string	Name;

public:
    /**
     * @brief Virtuální destruktor třídy Arena
     */
    virtual ~Arena(){;}
    /**
     * @brief Metoda vracející obecnou efektivitu arény
     * @return double Effect
     */
    double	getEffect() { return Effect; }
    /**
     * @brief Metoda vracející jméno arény
     * @return
     */
    string	getName() { return Name; }
};


///Areny reckych bohu

/**
 * @brief Třída reprezentujicí arénu "Olymp"
 */
class Olymp : public Arena {
public:
    ~Olymp(){;}
    Olymp() {
        Effect = 8.0;
        Name = "Olymp";
    }
};

/**
 * @brief Třída reprezentujicí arénu "Eegean Sea"
 */
class AegeanSea : public Arena {
public:
    ~AegeanSea(){;}
    AegeanSea() {
        Effect = 5.0;
        Name = "Aegean Sea";
    }
};

/**
 * @brief Třída reprezentujicí arénu "Library of Alexandria"
 */
class LibraryOfAlexandria : public Arena {
public:
    ~LibraryOfAlexandria(){;}
    LibraryOfAlexandria() {
        Effect = 3.0;
        Name = "Library Of Alexandria";
    }
};

///Areny norskych bohu
/**
 * @brief Třída reprezentujicí arénu "Asgartd"
 */
class Asgartd : public Arena {
public:
    ~Asgartd(){;}
    Asgartd() {
        Effect = 9.0;
        Name = "Asgartd";
    }
};

/**
 * @brief Třída reprezentujicí arénu "Norwegian Sea"
 */
class NorwegianSea : public Arena {
public:
    ~NorwegianSea(){;}
    NorwegianSea() {
        Effect = 5.0;
        Name = "Norwegian Sea";
    }
};

/**
 * @brief Třída reprezentujicí arénu "Alfheim"
 */
class Alfheim : public Arena {
public:
    ~Alfheim(){;}
    Alfheim() {
        Effect = 4.0;
        Name = "Alfheim";
    }
};

///Neutralni bojiste

/**
 * @brief Třída reprezentujicí arénu "Valley of Kings"
 */
class ValleyOfTheKings : public Arena {
public:
    ~ValleyOfTheKings(){;}
    ValleyOfTheKings() {
        Effect = 0.0;
        Name = "Valley Of Kings";
    }
};


#endif
