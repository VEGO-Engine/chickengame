#include "Game.h"

#include "../engine/include/Game.h"

void chickengame::init()
{
	std::cout << "INIT!" << std::endl; 
}

void chickengame::update()
{
	std::cout << "UPDATE!" << std::endl;
}

namespace engine {
	gamefunction init = chickengame::init;
	gamefunction update = chickengame::update;
}