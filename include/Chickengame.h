#pragma once

#include <Game.h>
#include <GameRegistryHelper.h>

#include "KeyboardController.h"
#include "Entities.h"

namespace chickengame
{
	class GameImplementation : public Game { // name pending
	public:

		void init() override;
		void update() override;
        void selectCharacters(const char* &playerSprite, const char* &enemySprite);
		
		Entities::TeamLabel getWinner() const;
		void setWinner(Entities::TeamLabel winningTeam);

	private:
		KeyboardController* playerControllerA;
		KeyboardController* playerControllerB;
		Entities::TeamLabel winner;
	};
};
