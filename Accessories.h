#ifndef ACCESSORIES_H
#define ACCESSORIES_H

//IMPLEMENTACE DATOVEHO TYPU ACCESSORIES

//Base class Accessories, dedi z ni konkretni predmety, kteri bohove mohou pouzivat
class Accessories {
protected:
	double	Effect;

public:
	double	getEffect() { return Effect; }
};

//Predmey

class LeviathanAxe : public Accessories {
public:
	LeviathanAxe() { Effect = 7.0; }
};

class Curse : public Accessories {
public:
	Curse()	{ Effect = -10.0; }
};

class ScrollOfWisdom : public Accessories {
public:
	ScrollOfWisdom() { Effect = 4.0; }
};

class Piety : public Accessories {
public:
	Piety() { Effect = 3.0; }
};

class Impiety : public Accessories {
public:
	Impiety() { Effect = -3.0; }
};


#endif

