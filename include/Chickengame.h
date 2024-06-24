#pragma once

#include "KeyboardController.h"
#include <Game.h>
#include <GameRegistryHelper.h>
#include <HealthComponent.h>
#include <Entity.h>

namespace chickengame
{
	class GameImplementation : public Game { // name pending
	public:
		void init() override;
		void update() override;
        void selectCharacters(const char* &playerSprite, const char* &enemySprite);

	private:
		KeyboardController* playerControllerA;
		KeyboardController* playerControllerB;

		// this is scuffed, but since we are just lousy game devs and no wise engine devs, this is ok
		std::vector<Entity*> heartElementsPlayerA;
		std::vector<Entity*> heartElementsPlayerB;
		void drawPlayerHealthUI(HealthComponent* playerHealthComponent, std::vector<Entity*>& heartElements, int startCoord, int offset);
		Entity* createHeartComponents(int locationX, Entity::TeamLabel team) const;
	};
};
