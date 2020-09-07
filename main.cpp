#include <iostream>
#include "BaseUnit.h"

//Everything happens here for now
int main()
{
	BaseUnit Unit1("Kenobi", 100, 20);
	BaseUnit Unit2("Maul", 50, 30);

	BaseUnit* attacker = &Unit1;
	BaseUnit* defender = &Unit2;
	BaseUnit* tmp;

	//fighting loop, just for showcase, must be redesigned later for actual in-game use
	do
	{
		tmp = attacker;
		attacker = defender;
		defender = tmp;

		std::cout << Unit1.getName() << " HP:" << Unit1.getHP() << " DMG:" << Unit1.getDMG() << std::endl;
		std::cout << Unit2.getName() << " HP:" << Unit2.getHP() << " DMG:" << Unit2.getDMG() << std::endl << std::endl;

		std::cin.get();

		std::cout << attacker->getName() << " -> " << defender->getName() << std::endl;

	} while (defender->gotHit(attacker->getDMG()));

	

	std::cout << Unit1.getName() << " HP:" << Unit1.getHP() << " DMG:" << Unit1.getDMG() << std::endl;
	std::cout << Unit2.getName() << " HP:" << Unit2.getHP() << " DMG:" << Unit2.getDMG() << std::endl;

	std::cout << defender->getName() << " died, " << attacker->getName() << " wins";

	std::cin.get();
}