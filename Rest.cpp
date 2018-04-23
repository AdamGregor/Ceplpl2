#include "Blocks.h"
#include <iostream>
#include <typeinfo>

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

//eval bloku REST
void ArenaSelect::eval() {
	std::cout << "Trida boha 1 je: " << this->IPort1->getName() << "\n";
}

void Combat::eval() {
	std::cout << "Trida boha 1 je: \n";
}

void ItemApply::eval() {
	std::cout << "Trida boha 1 je: \n";
}


void DiceThrow::eval() {
	std::cout << "Trida boha 1 je: \n";
}