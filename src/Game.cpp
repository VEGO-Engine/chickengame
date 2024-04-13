#include "Game.h"

#include "../engine/include/Game.h"
#include "AssetManager.h"
#include "HealthComponent.h"

void chickengame::init()
{
	std::cout << "INIT!" << std::endl; 
}

void chickengame::update()
{
	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		engine::game->assets->createPowerup(
			engine::game->assets->calculateSpawnPosition(),
			engine::game->assets->calculateType()
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