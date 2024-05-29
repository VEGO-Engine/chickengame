#include "Chickengame.h"

#include "Pickupables.h"
#include "TextureDict.h"

#include <iostream>
#include <vector>
#include <map>
#include <GameInternal.h>
#include <AssetManager.h>
#include <HealthComponent.h>
#include <InputComponent.h>
#include <Map.h>

void chickengame::GameImplementation::init()
{
	GameFactory::instance().get()->gameInternal->map->loadMap("assets/SDL_map_test.txt", 25, 20, GameFactory::instance().get()->gameInternal, &(chickengame::tiles::tileDictionary));

	std::vector<Entity*>& players = GameFactory::instance().get()->gameInternal->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS);
	playerControllerA = new KeyboardController(&players[0]->getComponent<InputComponent>(), Key::W, Key::S, Key::A, Key::D, Key::E, Vector2D(2, 0));
	playerControllerB = new KeyboardController(&players[1]->getComponent<InputComponent>(), Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT, Key::RIGHT_CTRL, Vector2D(-2, 0));
}

void chickengame::GameImplementation::update()
{
	playerControllerA->processMovement();
	playerControllerB->processMovement();

	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		GameFactory::instance().get()->gameInternal->assets->createPowerup(
			GameFactory::instance().get()->gameInternal->assets->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0] function
			std::get<1>(pickupable) // tuple[1] texture
		);
	}

	// needs to be in game.cpp to have access to internal functions
	for (auto& player : GameFactory::instance().get()->gameInternal->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS))
	{
		if (player->getComponent<HealthComponent>().getHealth() <= 0)
		{
			GameFactory::instance().get()->gameInternal->setWinner(player->getTeam());
		}
	}
}