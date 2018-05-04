/**
 *@file Gods.h
 *@author Adam Gregor (xgrego18)
 *@author Zdeněk Jelínek (xjelin47)
 *@brief  Hlavičkový soubor imlementujicí datový typ Bohové
 */

#ifndef GODS_H
#define GODS_H
#include <string>
using namespace std;

//IMPLEMENTACE DATOVEHO TYPU GODS

/**
 * @brief Třída reprezentujicí datový typ Gods
 */
class Gods {
protected:
    /**
     * @brief Atribut reprezentujicí sílu boha
     */
    double	Strenght;
    /**
     * @brief Atribut obsahujicí jméno boha
     */
    string	Name;


public:
    /**
     * @brief Virtualní destruktor třídy
     */
    virtual         ~Gods(){;}
    /**
     * @brief Čistě virtuální metoda vracejicí počáteční sílu boha
     * @return double s počátěční silou
     */
    virtual double  getOriginalStrenght() = 0;
    /**
     * @brief Metoda vracejicí aktuální sílu boha
     * @return double Strenght
     */
    double			getStrenght() { return Strenght; }
    /**
     * @brief Metoda vracejicí jméno boha
     * @return string Name
     */
    string			getName() { return Name; }
    /**
     * @brief Metoda nastavujicí novou sílu boha
     * @param double nova_sila
     * @return ukazatel na takto modifikovaného boha
     */
    Gods*			setStrenght(double newStrenght) { Strenght = newStrenght; return this; }
    /**
     * @brief Metoda upravující sílu boha
     * @param double diference
     * @return ukazatel na takto modifikovaného boha
     */
    Gods* 			addStrenght(double change) { Strenght += change; return this; }
};

///Bohove Olympu
/**
 * @brief Třída reprezentujicí boha Dia
 */
class Zeus : public Gods {
public:
    ~Zeus(){;}
    Zeus() {
        Name = "Zeus";
        Strenght = 100.0;
    }
    double getOriginalStrenght() { return 100.0; }
};

/**
 * @brief Třída reprezentujicí boha Poseidona
 */
class Poseidon : public Gods {
public:
    ~Poseidon(){;}
    Poseidon() {
        Name = "Poseidon";
        Strenght = 94.0;
    }

    double getOriginalStrenght() { return 94.0; }
};

/**
 * @brief Třída reprezentujicí bohyni Athenu
 */
class Athena : public Gods {
public:
    ~Athena(){;}
    Athena() {
        Name = "Athena";
        Strenght = 89.0;
    }

    double getOriginalStrenght() { return 89.0; }
};


///Bohove Asgardu

/**
 * @brief Třída reprezentujicí boha Odina
 */
class Odin : public Gods {
public:
    ~Odin(){;}
    Odin() {
        Name = "Odin";
        Strenght = 103.0;
    }

    double getOriginalStrenght() { return 103.0; }
};

/**
 * @brief Třída reprezentujicí boha Njorda
 */
class Njord : public Gods {
public:
    ~Njord(){;}
    Njord() {
        Name = "Njord";
        Strenght = 92.0;
    }

    double getOriginalStrenght() { return 92.0; }
};

/**
 * @brief Třída reprezentujicí boha Mimira
 */
class Mimir : public Gods {
public:
    ~Mimir(){;}
    Mimir() {
        Name = "Mimir";
        Strenght = 88.0;
    }

    double getOriginalStrenght() { return 88.0; }
};

#endif
