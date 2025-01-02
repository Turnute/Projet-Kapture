//  TOURENNE    FERRY
//  Vincent     Antony

#include <iostream>
#include "./headers/GameManager.h"

int main()
{
	try {
		std::string configFile = "../../Kapture.txt";
		kpt::GameManager game(configFile);

		game.display(0);
		game.display(1);


		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << "Une erreur est survenue : " << e.what() << std::endl;
		return 1;
	}
}