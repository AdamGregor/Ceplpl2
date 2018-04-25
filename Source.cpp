#include <stdlib.h>
#include <iostream>
#include <typeinfo>
#include <time.h> 


#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"
#include "SupportClasses.h"

int main() {
	srand(time(0));
	Zeus DIE;
	Athena Aty;
	Poseidon Pos;
	int c;
	Olymp arena;
	Curse buff;
	ArenaSelect aren;
	DiceThrow thro;
	SubscribeList list;
	Connect *connection = new Connect(&thro, &aren);
	std::cout << list.getLenght() << " " << list.getFirst()<<"\n";
	list.InsertItem(connection);
	std::cout << list.getLenght() << " " << list.getFirst() << "\n";
	Connect con(&thro, &aren);
	std::cout << aren.IPort1_Connected << " " << aren.IPort2_Connected << "\n";

	Rest rest;
	rest.IPort1 = &Aty;
	thro.IPort1 = &Aty;
	std::cout << Aty.getStrenght() << " \n";
	thro.eval();
	std::cout << Aty.getStrenght() << " \n";
	rest.eval();
	std::cout << Aty.getStrenght() << " \n";


	aren.IPort1 = &DIE;
	aren.IPort2 = &Pos;
	aren.eval();
	std::cout << aren.OPort1->getName() << "\n";
	std::cout << "Hello, guyz, my strengo ensto " << DIE.getStrenght() << " soy " << DIE.getName() << "\n";
	DIE.addStrenght(12);
	if (typeid(DIE) == typeid(Zeus))
		std::cout << "Yiss\n";
	std::cout << "I PUMPED DEM MUSKLES! I fight in " << typeid(arena).name() << " with "
		"help of " << typeid(buff).name() << "wich has power of " << buff.getEffect() << "\n";
	aren.eval();
	std::cout << "\n\n" << typeid(typeid(rest.OPort1)).name() ;

	std::cin >> c;

	return 0;
}