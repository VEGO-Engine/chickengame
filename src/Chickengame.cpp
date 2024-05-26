#include "Chickengame.h"

#include "Pickupables.h"
// #include "KeyboardController.h"

#include <iostream>
#include <vector>
#include <Game.h>
#include <AssetManager.h>
#include <HealthComponent.h>
#include <InputComponent.h>

void chickengame::init()
{
	std::cout << "INIT!" << std::endl;

	std::vector<Entity*>& players = engine::game->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS);
	std::cout << "getting players succeeded" << std::endl;
	std::cout << players.size() << std::endl;

	playerControllerA = new KeyboardController(&players[0]->getComponent<InputComponent>(), Key::W, Key::S, Key::A, Key::D, Key::E, Vector2D(2, 0));
	playerControllerB = new KeyboardController(&players[1]->getComponent<InputComponent>(), Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT, Key::LEFT_CTRL, Vector2D(-2, 0));
}

void chickengame::update()
{
	playerControllerA->processMovement();
	playerControllerB->processMovement();

	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		engine::game->assets->createPowerup(
			engine::game->assets->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0]
			std::get<1>(pickupable) // tuple[1]
		);
	}

	// needs to be in game.cpp to have access to internal functions
	for (auto& player : engine::game->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS))
	{
		if (player->getComponent<HealthComponent>().getHealth() <= 0)
		{
			engine::game->setWinner(player->getTeam());
		}
	}
}

namespace engine {
	gamefunction init = chickengame::init;
	gamefunction update = chickengame::update;
}