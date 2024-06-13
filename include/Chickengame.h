#pragma once

#include "KeyboardController.h"
#include <Game.h>
#include <GameRegistryHelper.h>

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
	};
};
