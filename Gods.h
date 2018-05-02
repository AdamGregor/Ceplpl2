#ifndef GODS_H
#define GODS_H
#include <string>
using namespace std;

//IMPLEMENTACE DATOVEHO TYPU GODS

//Deklarace/definice tridy God. Z ni budou dedit jednotlivi bohove
class Gods {
protected:
	double	Strenght;
    string	Name;


public:
	double			getStrenght() { return Strenght; }
	virtual double  getOriginalStrenght() = 0;
    string			getName() { return Name; }
	Gods*			setStrenght(double newStrenght) { Strenght = newStrenght; return this; }
	Gods* 			addStrenght(double change) { Strenght += change; return this; }
};

//Bohove Olympu
class Zeus : public Gods {
public:
	Zeus() {
		Name = "Zeus";
		Strenght = 100.0;
	}

	double getOriginalStrenght() { return 100.0; }
};
class Poseidon : public Gods {
public:
	Poseidon() {
		Name = "Poseidon";
		Strenght = 94.0;
	}

	double getOriginalStrenght() { return 94.0; }
};
class Athena : public Gods {
public:
	Athena() {
		Name = "Athena";
		Strenght = 89.0;
	}

	double getOriginalStrenght() { return 89.0; }
};


//Bohove Asgardu
class Odin : public Gods {
public:
	Odin() {
		Name = "Odin";
		Strenght = 103.0;
	}

	double getOriginalStrenght() { return 103.0; }
};
class Njord : public Gods {
public:
	Njord() {
		Name = "Njord";
		Strenght = 92.0;
	}

	double getOriginalStrenght() { return 92.0; }
};
class Mimir : public Gods {
public:
	Mimir() {
		Name = "Mimir";
		Strenght = 88.0;
	}

	double getOriginalStrenght() { return 88.0; }
};

#endif
