#pragma once

#include <Game.h>
#include <GameRegistryHelper.h>
#include <HealthComponent.h>
#include <Entity.h>

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

		// this is scuffed, but since we are just lousy game devs and no wise engine devs, this is ok
		std::vector<Entity*> heartElementsPlayerA;
		std::vector<Entity*> heartElementsPlayerB;
		void drawPlayerHealthUI(HealthComponent* playerHealthComponent, std::vector<Entity*>& heartElements, int startCoord, int offset);
		Entity* createHeartComponents(int locationX) const;
	};
};
