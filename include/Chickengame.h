#pragma once

#include <Game.h>
#include <GameRegistryHelper.h>
#include <memory>

#include "KeyboardController.h"

namespace chickengame
{
	class GameImplementation : public Game { // name pending
	public:
		void init() override;
		void update() override;
        void selectCharacters(const char* &playerSprite, const char* &enemySprite);
		bool shouldPlayerIdle(InputSystemComponent* input, Key up, Key down, Key left, Key right);

	private:
		std::unique_ptr<KeyboardController> playerControllerA;
		std::unique_ptr<KeyboardController> playerControllerB;
	};
};
