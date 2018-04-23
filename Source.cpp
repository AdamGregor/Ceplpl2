#include <stdlib.h>
#include <iostream>
#include <typeinfo>


#include "Gods.h"
#include "Arenas.h"
#include "Accessories.h"
#include "Blocks.h"

int main() {
	Zeus DIE;
	Athena Aty;
	int c;
	Olymp arena;
	Curse buff;
	ArenaSelect aren;
	aren.IPort1 = &DIE;
	std::cout << "Hello, guyz, my strengo ensto " << DIE.getStrenght() << " soy " << DIE.getName() << "\n";
	DIE.addStrenght(12);
	if (typeid(DIE) == typeid(Zeus))
		std::cout << "Yiss\n";
	std::cout << "I PUMPED DEM MUSKLES! I fight in " << typeid(arena).name() << " with "
		"help of " << typeid(buff).name() << "wich has power of " << buff.getEffect() << "\n";
	aren.eval();


	std::cin >> c;

	return 0;
}