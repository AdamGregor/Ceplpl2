#ifndef ACCESSORIES_H
#define ACCESSORIES_H
#include <string>
using namespace std;
#define ITEM_COUNT 5

//IMPLEMENTACE DATOVEHO TYPU ACCESSORIES

//Base class Accessories, dedi z ni konkretni predmety, kteri bohove mohou pouzivat
class Accessories {
protected:
	double	Effect;
    string	Name;

public:
	double	getEffect() { return Effect; }
    string	getName() { return Name; }
};

//Predmey

class LeviathanAxe : public Accessories {
public:
	LeviathanAxe() {
		Effect = 7.0;
		Name = "Leviathan Axe";
	}
};

class Curse : public Accessories {
public:
	Curse() {
		Effect = -10.0;
		Name = "Curse";
	}
};

class ScrollOfWisdom : public Accessories {
public:
	ScrollOfWisdom() {
		Effect = 4.0;
		Name = "Scroll Of Wisdom";
	}
};

class Piety : public Accessories {
public:
	Piety() {
		Effect = 3.0;
		Name = "Piety";
	}
};

class Impiety : public Accessories {
public:
	Impiety() {
		Effect = -3.0;
		Name = "Impiety";
	}
};


#endif
