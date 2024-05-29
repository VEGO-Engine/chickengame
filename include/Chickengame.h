#pragma once

#include "KeyboardController.h"
#include <Game.h>

namespace chickengame
{
	class GameImplementation : public Game { // name pending
		void init() override;
		void update() override;
	};

	KeyboardController* playerControllerA;
	KeyboardController* playerControllerB;

	REGISTER_GAME(GameImplementation);
};