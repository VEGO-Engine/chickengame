#include "Chickengame.h"

#include "Pickupables.h"
#include "TextureDict.h"

#include <iostream>
#include <map>
#include <Game.h>
#include <AssetManager.h>
#include <HealthComponent.h>
#include <Map.h>

void chickengame::init()
{
	engine::game->map->loadMap("assets/SDL_map_test.txt", 25, 20, engine::game, &(chickengame::tiles::tileDictionary));
	std::cout << "INIT!" << std::endl; 
}

void chickengame::update()
{
	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		engine::game->assets->createPowerup(
			engine::game->assets->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0] function
			std::get<1>(pickupable) // tuple[1] texture
		);
	}

	// needs to be in game.cpp to have access to internal functions
	for (auto& player : engine::game->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS)) {
		if (player->getComponent<HealthComponent>().getHealth() <= 0) {
			engine::game->setWinner(player->getTeam());
		}
	}
}

namespace engine {
	gamefunction init = chickengame::init;
	gamefunction update = chickengame::update;
}