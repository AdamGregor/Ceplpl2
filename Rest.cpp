#include "Blocks.h"
#include "SupportClasses.h"
#include <iostream>
#include <typeinfo>

#define HIGHEST_EFFECT 1.0
#define LOWEST_EFFECT -0.5

// Konstruktory bloku, portum jsou nastaveny pocatecni hodnoty (nullptr, false)

Rest::Rest() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort1_Initiated = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
	OPort1_Initiated = false;
}

DiceThrow::DiceThrow() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort1_Initiated = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
	OPort1_Initiated = false;
}

Combat::Combat() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort1_Initiated = false;
	
	IPort2 = nullptr;
	IPort2_Connected = false;
	IPort2_Initiated = false;
	
	IPort3 = nullptr;
	IPort3_Connected = false;
	IPort3_Initiated = false;
	
	OPort1 = nullptr;
	OPort1_Connected = false;
	OPort1_Initiated = false;
}

ItemApply::ItemApply() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort1_Initiated = false;
	IPort2 = nullptr;
	IPort2_Connected = false;
	IPort2_Initiated = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
	OPort1_Initiated = false;
}

ArenaSelect::ArenaSelect() {
	IPort1 = nullptr;
	IPort1_Connected = false;
	IPort1_Initiated = false;
	IPort2 = nullptr;
	IPort2_Connected = false;
	IPort2_Initiated = false;
	OPort1 = nullptr;
	OPort1_Connected = false;
	OPort1_Initiated = false;
}


PortStuff Rest::tryConnect(char* typ) {
	PortStuff ret;
	if (typ == "Gods" && IPort1_Connected == false) {
		this->IPort1_Connected = true;
		ret.value = (void*)(this->IPort1);
		ret.init = &(this->IPort1_Initiated);
		return ret;
	}
	else
		ret.value = nullptr;
		return ret;
}

PortStuff DiceThrow::tryConnect(char* typ) {
	PortStuff ret;
	if (typ == "Gods" && IPort1_Connected == false) {
		this->IPort1_Connected = true;
		ret.value = (void*)(this->IPort1);
		ret.init = &(this->IPort1_Initiated);
		return ret;
	}
	else
		ret.value = nullptr;
		return ret;
}

PortStuff Combat::tryConnect(char* typ) {
	PortStuff ret;
	if (typ == "Gods" && IPort1_Connected == false) {
		this->IPort1_Connected = true;
		ret.value = (void*)(this->IPort1);
		ret.init = &(this->IPort1_Initiated);
		return ret;
	}
	else if (typ == "Gods" && IPort3_Connected == false) {
		this->IPort3_Connected = true;
		ret.value = (void*)(this->IPort3);
		ret.init = &(this->IPort3_Initiated);
		return ret;
	}
	else if (typ == "Arena" && IPort2_Connected == false) {
		ret.value = (void*)(this->IPort2);
		ret.init = &(this->IPort2_Initiated);
		return ret;
	}
	else
		ret.value = nullptr;
		return ret;
}

PortStuff ItemApply::tryConnect(char* typ) {
	PortStuff ret;
	if (typ == "Gods" && IPort1_Connected == false) {
		this->IPort1_Connected = true;
		ret.value = (void*)(this->IPort1);
		ret.init = &(this->IPort1_Initiated);
		return ret;
	}
	else
		ret.value = nullptr;
		return ret;
}

PortStuff ArenaSelect::tryConnect(char* typ) {
	PortStuff ret;
	if (typ == "Gods" && IPort1_Connected == false) {
		this->IPort1_Connected = true;
		ret.value = (void*)(this->IPort1);
		ret.init = &(this->IPort1_Initiated);
		return ret;
	}
	else if (typ == "Gods" && IPort2_Connected == false) {
		this->IPort2_Connected = true;
		ret.value = (void*)(this->IPort2);
		ret.init = &(this->IPort2_Initiated);
		return ret;
	}
	else
		ret.value = nullptr;
		return ret;
}


//eval bloku REST
void Rest::eval() {
	this->OPort1 = this->IPort1->setStrenght(this->IPort1->getOriginalStrenght());

	//distribuce vysledku
	ListItem *subscribes = this->subscriptions->getFirst();
	while (subscribes != nullptr) {
		subscribes->data->distributeResult();
		subscribes = subscribes->next;
	}
}

//Select areny na zaklade bohu
void ArenaSelect::eval() {
	char *name;
	//vypocteni, ci arena se pouzije
	int random = rand() % 2;

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

}

void Combat::eval() {
	double effect = this->IPort2->getEffect();
	char *arena = this->IPort2->getName();
	char *God1 = this->IPort1->getName();
	double God1_S = this->IPort1->getStrenght();

	char *God2 = this->IPort3->getName();
	double God2_S = this->IPort3->getStrenght();

	//pokud je 1. buh recky a arena take, prida mu cast sily
	if ((arena == "Olymp" || arena == "Aegean Sea" || arena == "Library Of Alexandria") &&
		(God1 == "Zeus" || God1 == "Poseidon" || God1 == "Athena"))
		God1_S += 0.5 * effect;

	//pokud je 1. buh seversky a arena take, prida mu cast sily
	else if ((arena == "Asgartd" || arena == "Norwegian Sea" || arena == "Alfheim") &&
		(God1 == "Odin" || God1 == "Njord" || God1 == "Mimir"))
		God1_S += 0.5 * effect;


	//pokud je 2. buh recky a arena take, prida mu cast sily
	if ((arena == "Olymp" || arena == "Aegean Sea" || arena == "Library Of Alexandria") &&
		(God2 == "Zeus" || God2 == "Poseidon" || God2 == "Athena"))
		God2_S += 0.5 * effect;


	//pokud je 2. buh seversky a arena take, prida mu cast sily
	else if ((arena == "Asgartd" || arena == "Norwegian Sea" || arena == "Alfheim") &&
		(God2 == "Odin" || God2 == "Njord" || God2 == "Mimir"))
		God2_S += 0.5 * effect;

	//bonusy na zaklade lokace pro boha1;
	if(arena == "Olymp" && God1 == "Zeus")
		God1_S += 0.5 * effect;
	else if (arena == "Asgartd" && God1 == "Odin")
		God1_S += 0.5 * effect;
	else if ((arena == "Aegean Sea" || arena == "Norwegian Sea") && 
		(God1 == "Poseidon" || God1 == "Njord"))
		God1_S += 0.5 * effect;
	else if ((arena == "Library Of Alexandria" || arena == "Alfheim") &&
		(God1 == "Athena" || God1 == "Mimir"))
		God1_S += 0.5 * effect;

	//bonusy na zaklade lokace pro boha2;
	if (arena == "Olymp" && God2 == "Zeus")
		God2_S += 0.5 * effect;
	else if (arena == "Asgartd" && God2 == "Odin")
		God2_S += 0.5 * effect;
	else if ((arena == "Aegean Sea" || arena == "Norwegian Sea") &&
		(God2 == "Poseidon" || God2 == "Njord"))
		God2_S += 0.5 * effect;
	else if ((arena == "Library Of Alexandria" || arena == "Alfheim") &&
		(God2 == "Athena" || God2 == "Mimir"))
		God2_S += 0.5 * effect;

	//zvitezi 1. buh
	if (God1_S > God2_S) {
		this->IPort1->setStrenght(God1_S - God2_S);
		this->IPort3->setStrenght(0.0);
		this->OPort1 = this->IPort1;
	}
	//zvitezi 2.buh
	else if (God1_S < God2_S) {
		this->IPort3->setStrenght(God2_S - God1_S);
		this->IPort1->setStrenght(0.0);
		this->OPort1 = this->IPort3;
	}
	//remiza, 'strihnou' si
	else if (God1_S == God2_S) {
		if (rand() % 2 == 1) {
			this->IPort1->setStrenght(0.01);
			this->IPort3->setStrenght(0.0);
			this->OPort1 = this->IPort1;
		}
		else {
			this->IPort3->setStrenght(0.01);
			this->IPort1->setStrenght(0.0);
			this->OPort1 = this->IPort3;
		}
	}
}

void ItemApply::eval() {
	double effect = this->IPort2->getEffect();

	effect *= (double)((rand() % 155) - 25) / 100.0;

	IPort1->addStrenght(effect);
	if (IPort1->getStrenght() < 0.0)
		IPort1->setStrenght(0.0);

	this->OPort1 = this->IPort1;

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
	//this->OPort1_Connected = true;
}

void SubscribeList::InsertItem(Connect *data) {
	ListItem *neu = new ListItem;
	ListItem *first = this->getFirst();
	neu->data = data;
	neu->next = first;
	this->first = neu;
	this->listLenght++;
}

void Rest::distribute() {


}

///TODO pridat tento spoj do seznamu odchozcich v bloku
Connect::Connect(Block* Blok1, Block *Blok2) {
	this->transfered = false;
	
	this->Data_type = Blok1->getOut();
	this->reaction = Blok2->tryConnect(this->Data_type);
	if (reaction.value != nullptr) {
		Blok1->setSubscribe(this);
		std::cout << "je to fajn \n";
		this->in = Blok1;
		this->out = Blok2;
	}
	else {
		std::cout << "ses posral, ne? ";
	}
		//nejaka chyba

}

/*
Connect::DistributeResult()
	
}
*/

/*
Connect::Delete() {


}*/