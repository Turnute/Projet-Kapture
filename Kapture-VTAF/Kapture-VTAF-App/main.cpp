//  TOURENNE    FERRY
//  Vincent     Antony

#include <iostream>
#include <windows.h>
#include "../Kapture-VTAF/headers/GameManager.h"

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	try {
		std::string configFile = argc > 1 ? argv[1] : "../../Kapture.txt";
		kpt::GameManager game(configFile);

		game.gameLoop();

		return 0;
	}
	catch (const std::exception& e) {
		std::cerr << "Une erreur est survenue : " << e.what() << std::endl;
		return 1;
	}
}