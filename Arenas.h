#ifndef ARENAS_H
#define ARENAS_H
#include <string>
using namespace std;
//IMPLEMENTACE DATOVEHO TYPU ARENAS

//Base class Arena, dedi z ni konkretni areny
class Arena {
protected:
    double	Effect;
    string	Name;

public:
    virtual ~Arena(){delete &Effect; delete &Name;}
    double	getEffect() { return Effect; }
    string	getName() { return Name; }
};

//Areny

//Areny reckych bohu
class Olymp : public Arena {
public:
    ~Olymp(){;}
    Olymp() {
        Effect = 8.0;
        Name = "Olymp";
    }
};

class AegeanSea : public Arena {
public:
    ~AegeanSea(){;}
    AegeanSea() {
        Effect = 5.0;
        Name = "Aegean Sea";
    }
};

class LibraryOfAlexandria : public Arena {
public:
    ~LibraryOfAlexandria(){;}
    LibraryOfAlexandria() {
        Effect = 3.0;
        Name = "Library Of Alexandria";
    }
};

//Areny norskych bohu
class Asgartd : public Arena {
public:
    ~Asgartd(){;}
    Asgartd() {
        Effect = 9.0;
        Name = "Asgartd";
    }
};

class NorwegianSea : public Arena {
public:
    ~NorwegianSea(){;}
    NorwegianSea() {
        Effect = 5.0;
        Name = "Norwegian Sea";
    }
};

class Alfheim : public Arena {
public:
    ~Alfheim(){;}
    Alfheim() {
        Effect = 4.0;
        Name = "Alfheim";
    }
};

//Neutralni bojiste
class ValleyOfTheKings : public Arena {
public:
    ~ValleyOfTheKings(){;}
    ValleyOfTheKings() {
        Effect = 0.0;
        Name = "Valley Of Kings";
    }
};


#endif
