#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	try {
		game.run();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
