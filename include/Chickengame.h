#pragma once

#include <memory>

#include <Game.h>
#include <GameRegistryHelper.h>
#include <HealthComponent.h>
#include <Entity.h>

#include "KeyboardController.h"
#include "Entities.h"
#include "TextureEnumImplementation.h"

namespace chickengame
{
	class GameImplementation : public Game { // name pending
	public:

		void init() override;
		void update(uint_fast16_t diffTime) override;
        void selectCharacters(Textures &playerSprite, Textures &enemySprite);
		void startScreen();

		Entities::TeamLabel getWinner() const;
		void setWinner(Entities::TeamLabel winningTeam);
		std::optional<std::string> getConfigFilePath() override;

	private:
		std::unique_ptr<KeyboardController> playerControllerA;
		std::unique_ptr<KeyboardController> playerControllerB;
		Entities::TeamLabel winner;

		// this is scuffed, but since we are just lousy game devs and no wise engine devs, this is ok
		std::vector<Entity*> heartElementsPlayerA;
		std::vector<Entity*> heartElementsPlayerB;
		void drawPlayerHealthUI(HealthComponent* playerHealthComponent, std::vector<Entity*>& heartElements, int startCoord, int offset);
		Entity* createHeartComponents(int locationX) const;
		void loadTextures();
	};
};
