#include "Blocks.h"
#include <iostream>
#include <typeinfo>

#define HIGHEST_EFFECT 1.0
#define LOWEST_EFFECT -0.5

// Konstruktory bloku, portum jsou nastaveny pocatecni hodnoty (nullptr, false)

Rest::Rest() {
	IPort1				= nullptr;
	IPort1_Connected	= false;
	OPort1				= nullptr;
	OPort1_Connected	= false;
}

DiceThrow::DiceThrow() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
}

Combat::Combat() {
	IPort1				= nullptr;
	IPort1_Connected	= false;
	IPort2				= nullptr;
	IPort2_Connected	= false;
	IPort3				= nullptr;
	IPort3_Connected	= false;
	OPort1				= nullptr;
	OPort1_Connected	= false;
}

ItemApply::ItemApply() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort2 = nullptr;
	IPort2_Connected = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
}

ArenaSelect::ArenaSelect() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort2 = nullptr;
	IPort2_Connected = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
}

//eval bloku REST
void Rest::eval() {
	this->OPort1 = this->IPort1->setStrenght(this->IPort1->getOriginalStrenght());
	this->OPort1_Connected = true;
}

//Select areny na zaklade bohu
void ArenaSelect::eval() {
	char *name;
	//vypocteni, ci arena se pouzije
	int random = rand()%2;
	
	//nastaveni areny podle vylosovaneho boha
	if (random == 0) 
		name = this->IPort1->getName();
	else
		name = this->IPort2->getName();

	if (name == "Zeus")
		this->OPort1 = new Olymp;
	else if (name == "Poseidon")
		this->OPort1 = new AegeanSea;
	else if (name == "Athena")
		this->OPort1 = new LibraryOfAlexandria;
	else if (name == "Odin")
		this->OPort1 = new Asgartd;
	else if (name == "Njord")
		this->OPort1 = new NorwegianSea;
	else if (name == "Mimir")
		this->OPort1 = new Alfheim;

	this->OPort1_Connected = true;
}

void Combat::eval() {
	std::cout << "Trida boha 1 je: \n";
}

void ItemApply::eval() {

	float effect = LOWEST_EFFECT + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HIGHEST_EFFECT - LOWEST_EFFECT)));

}

//Bohovi bude sebrano 10% zdravi a za to dostane nahodny predmet
void DiceThrow::eval() {
	//nastavi se zivot na 90% stavajiciho
	double strenght = this->IPort1->getStrenght();
	strenght *= 0.9;
	

	//vybere se nahodny predmet a ten se na nej aplikuje
	int random = rand();
	double boost;
	random = random % ITEM_COUNT;
	
	if (random == 0) {
		LeviathanAxe *tmp = new LeviathanAxe;
		boost = tmp->getEffect();
		delete tmp;
	}

	else if (random == 1) {
		Curse *tmp = new Curse;
		boost = tmp->getEffect();
		delete tmp;
	}

	else if (random == 2) {
		ScrollOfWisdom *tmp = new ScrollOfWisdom;
		boost = tmp->getEffect();
		delete tmp;
	}

	else if (random == 3) {
		Piety *tmp = new Piety;
		boost = tmp->getEffect();
		delete tmp;
	}

	else if (random == 4) {
		Impiety *tmp = new Impiety;
		boost = tmp->getEffect();
		delete tmp;
	} 

	strenght += boost;
	if (strenght < 0.0)
		strenght = 0.0;

	this->IPort1->setStrenght(strenght);
	
	this->OPort1 = this->IPort1;
	this->OPort1_Connected = true;
}