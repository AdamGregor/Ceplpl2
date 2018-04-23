#ifndef ARENAS_H
#define ARENAS_H

//IMPLEMENTACE DATOVEHO TYPU ARENAS

//Base class Arena, dedi z ni konkretni areny
class Arena {
protected:
	double	Effect;

public:
	double	getEffect() { return Effect; }
};

//Areny

//Areny reckych bohu
class Olymp : public Arena {
public:
	Olymp() {Effect = 8.0;}
};

class AegeanSea : public Arena {
public:
	AegeanSea() {Effect = 5.0;}
};

class LibraryOfAlexandria : public Arena {
public:
	LibraryOfAlexandria() {Effect = 3.0;}
};

//Areny norskych bohu
class Asgartd : public Arena {
public:
	Asgartd() {Effect = 9.0;}
};

class NorwegianSea : public Arena {
public:
	NorwegianSea() {Effect = 5.0;}
};

class Alfheim : public Arena {
public:
	Alfheim() {Effect = 4.0;}
};

//Neutralni bojiste
class ValleyOfTheKings : public Arena {
public:
	ValleyOfTheKings() {Effect = 0.0;}
};


#endif

