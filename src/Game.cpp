#include "Game.h"

#include "../engine/include/Game.h"

void my_game::init()
{
	std::cout << "INIT!" << std::endl; 
}

void my_game::update()
{
	std::cout << "UPDATE!" << std::endl;
}

namespace engine {
	gamefunction init = my_game::init;
	gamefunction update = my_game::update;
}