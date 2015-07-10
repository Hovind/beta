#include <iostream>
#include "Exception.h"
#include "Game.h"

int main(int argc, char** argv) {
	Game game;
	try {
		game.run();
	} catch (Engine::Exception &e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
