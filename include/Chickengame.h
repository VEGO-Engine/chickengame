#pragma once

#include <memory>

#include <Game.h>
#include <GameRegistrar.h>
#include <HealthComponent.h>
#include <Entity.h>

#include "Controls.h"
#include "Entities.h"
#include "TextureEnumImplementation.h"
#include "ConsoleListener.h"

namespace chickengame
{
	class GameImplementation;
	static vego::GameRegistrar<GameImplementation> game_registrar;
	
	class GameImplementation : public Game { // name pending
	public:

		void init() override;
		void update(uint_fast16_t diffTime) override;
        void selectCharacters(Textures &playerSprite, Textures &enemySprite);
		void startScreen();

		Entities::TeamLabel getWinner() const;
		void setWinner(Entities::TeamLabel winningTeam);
		std::optional<std::string> setConfigFilePath() override;

	private:
		Entities::TeamLabel winner;

		// this is scuffed, but since we are just lousy game devs and no wise engine devs, this is ok
		std::vector<Entity*> heartElementsPlayerA;
		std::vector<Entity*> heartElementsPlayerB;
		void drawPlayerHealthUI(HealthComponent* playerHealthComponent, std::vector<Entity*>& heartElements, int startCoord, int offset);
		Entity* createHeartComponents(int locationX) const;
		void loadTextures();
		void loadSoundEffects();

		std::shared_ptr<ConsoleListener> consoleListener = std::make_shared<ConsoleListener>();
	};
};
