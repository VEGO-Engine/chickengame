#include "Chickengame.h"

#include "Pickupables.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "Animations.h"

#include "TextureEnumImplementation.h"

#include <iostream>
#include <vector>
#include <map>
#include <GameInternal.h>
#include <HealthComponent.h>
#include <InputComponent.h>
#include <Map.h>
#include <VEGO.h>

#include "MusicAndSoundImplementation.h"
#include "Controls.h"

vego::GameRegistryHelper<chickengame::GameImplementation> this_is_a_variable_so_the_constructor_get_called_without_using_a_define_macro("Chickengame");

void chickengame::GameImplementation::init()
{
	loadTextures();
	loadSoundEffects();

	this->startScreen();

	Map map("assets/grassy-river.tmx");
	map.generateTiles();

	chickengame::animations::initialize();
	Entities::getInstance().initialize(this);
	
	std::vector<Entity*>& players = VEGO_Game().manager.getGroup((size_t) Entity::GroupLabel::PLAYERS);
	Controls::initControls(players);
	VEGO_Game().interactionManager->registerListener(this->consoleListener);
	
}

void chickengame::GameImplementation::update(uint_fast16_t diffTime)
{
	int powerupSpawn = rand() % (8000 * (diffTime > 0 ? diffTime : 1));;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		VEGO_Game().pickupManager->createPowerup(
			VEGO_Game().pickupManager->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0] function
			std::get<1>(pickupable) // tuple[1] texture
		);
	}

	for (auto& player : VEGO_Game().manager.getGroup((size_t) Entity::GroupLabel::PLAYERS))
	{
		if (player->getComponent<TransformComponent>().direction.x == 0 
		&& player->getComponent<TransformComponent>().direction.y == 0)
		{
			player->getComponent<SpriteComponent>().playAnimation("IDLE");
		}
		if (player->getComponent<HealthComponent>().getHealth() <= 0)
		{
			this->setWinner(Entities::getInstance().getTeam(player));
		}
	}

	drawPlayerHealthUI(&chickengame::Entities::getInstance().getPlayer1()->getComponent<HealthComponent>(), this->heartElementsPlayerA, 10, 50);
	drawPlayerHealthUI(&chickengame::Entities::getInstance().getPlayer2()->getComponent<HealthComponent>(), this->heartElementsPlayerB, 730, -50);
}

void chickengame::GameImplementation::setWinner(Entities::TeamLabel winningTeam)
{
	this->winner = winningTeam;
	VEGO_Game().stopGame();
}

std::optional<std::string> chickengame::GameImplementation::setConfigFilePath() {
	return std::optional<std::string>("./configs/mainConfig.json");
}

chickengame::Entities::TeamLabel chickengame::GameImplementation::getWinner() const
{
    return this->winner;
}

void chickengame::GameImplementation::startScreen()
{
	SDL_Texture* backgroundTexture = VEGO_Game().textureManager->loadTexture(Textures::startScreen);
	SDL_Renderer* renderer = VEGO_Game().renderer;

	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, backgroundTexture, NULL, NULL);
	SDL_RenderPresent(renderer);

	//SDL_Event event;
	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_PollEvent(&(VEGO_Game().event));

		if ((VEGO_Game().event).type == SDL_EVENT_QUIT)
		{
			hasQuit = true;
			break;
		}

		if ((VEGO_Game().event).type == SDL_EVENT_KEY_DOWN)
		{
			if ((VEGO_Game().event).key.scancode == SDL_SCANCODE_RETURN)
			{
				std::cout << "Enter pressed > Game start..." << std::endl;
				break;
			}

			if ((VEGO_Game().event).key.scancode == SDL_SCANCODE_ESCAPE)
			{
				std::cout << "Escape pressed > Game quit..." << std::endl;
				hasQuit = true;
			}
		}
	}

	if (hasQuit)
	{
		VEGO_Game().setRunning(false);
		return;
	}

	if (VEGO_Game().isRunning() == false) return;

}

void chickengame::GameImplementation::selectCharacters(Textures &playerSprite, Textures &enemySprite)
{
	// TODO: move this whereever it makes sense (maybe game as a member)
	std::map<int, std::pair<Textures, Textures>> characterSprites;
	characterSprites[0] = std::make_pair(Textures::chickenNeutralKnight, Textures::chickenKnight);
	characterSprites[1] = std::make_pair(Textures::chickenNeutralPessant, Textures::chickenPessant);
	characterSprites[2] = std::make_pair(Textures::chickenNeutralWizard, Textures::chickenWizard);
	characterSprites[3] = std::make_pair(Textures::chickenNeutralMLady, Textures::chickenMLady);

	SDL_FRect playerCharacterRects[CHARACTER_COUNT];
	SDL_FRect enemyCharacterRects[CHARACTER_COUNT];
	SDL_Texture* characterTextures[CHARACTER_COUNT];

	int playerSelection = 0;
	int enemySelection = 0;


	// load textures
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		characterTextures[i] = VEGO_Game().textureManager->loadTexture(characterSprites.find(i)->second.first);
	}

	// set up initial positions for character rects
	for (uint8_t i = 0; i < CHARACTER_COUNT; ++i)
	{
		playerCharacterRects[i] = { static_cast<float>(134 + (i % 2) * 118), static_cast<float>(272 + ((i >= 2) ? 114 : 0)), 64, 64 };
		enemyCharacterRects[i] = { static_cast<float>(485 + (i % 2) * 118), static_cast<float>(273 + ((i >= 2) ? 114 : 0)), 64, 64 };
	}

	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_PollEvent(&VEGO_Game().event);

		if (VEGO_Game().event.type == SDL_EVENT_QUIT)
		{
			hasQuit = true;
		}

		if (VEGO_Game().event.type == SDL_EVENT_KEY_DOWN)
		{
			if (VEGO_Game().event.key.scancode == SDL_SCANCODE_RETURN)
			{
				break;
			}

			switch (VEGO_Game().event.key.scancode)
			{
			case SDL_SCANCODE_A:
				playerSelection = (playerSelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
				break;
			case SDL_SCANCODE_D:
				playerSelection = (playerSelection + 1) % CHARACTER_COUNT;
				break;

			case SDL_SCANCODE_LEFT:
				enemySelection = (enemySelection - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
				break;
			case SDL_SCANCODE_RIGHT:
				enemySelection = (enemySelection + 1) % CHARACTER_COUNT;
				break;

			default:
				break;
			}
		}

		SDL_Texture* backgroundTexture = VEGO_Game().textureManager->loadTexture(Textures::charSelection);
		SDL_RenderClear(VEGO_Game().renderer);
		SDL_RenderTexture(VEGO_Game().renderer, backgroundTexture, NULL, NULL);

		for (int i = 0; i < CHARACTER_COUNT; ++i)
		{
			SDL_RenderTexture(VEGO_Game().renderer, characterTextures[i], nullptr, &playerCharacterRects[i]);
			SDL_RenderTexture(VEGO_Game().renderer, characterTextures[i], nullptr, &enemyCharacterRects[i]);
		}

		SDL_SetRenderDrawColor(VEGO_Game().renderer, 0, 255, 0, 255);
		SDL_RenderRect(VEGO_Game().renderer, &playerCharacterRects[playerSelection]);
		SDL_RenderRect(VEGO_Game().renderer, &enemyCharacterRects[enemySelection]);

		SDL_RenderPresent(VEGO_Game().renderer);
	}

	if (hasQuit)
	{
		VEGO_Game().stopGame();
		return;
	}

	playerSprite = characterSprites.find(playerSelection)->second.second;
	enemySprite = characterSprites.find(enemySelection)->second.second;
}

void chickengame::GameImplementation::drawPlayerHealthUI(HealthComponent* playerHealthComponent, std::vector<Entity*>& heartElements, int startCoord, int offset)
{
	// clear hearts
    for (auto& heart : heartElements) {
        heart->destroy();
    }
	
	heartElements.clear();

    for(int i = 0; i < playerHealthComponent->getHealth(); i++) {
        heartElements.emplace_back(createHeartComponents(startCoord));
        startCoord += offset;
    }
}

Entity* chickengame::GameImplementation::createHeartComponents(int locationX) const
{
    auto& heart(VEGO_Game().manager.addEntity());
    heart.addComponent<TransformComponent>(locationX,5,2);
    heart.addComponent<SpriteComponent>(Textures::heart, 10);
    heart.addGroup((size_t)Entity::GroupLabel::HEARTS);
	return &heart;
}

void chickengame::GameImplementation::loadTextures() {
	VEGO_Game().textureManager->addTextures({
		{Textures::charSelection, "assets/characterSelection.png"},
		{Textures::heart, "assets/heart.png"},
		{Textures::egg, "assets/egg.png"},
		{Textures::waterTile, "assets/water.png"},
		{Textures::grassTile, "assets/grass.png"},
		{Textures::dirtTile, "assets/dirt.png"},
		{Textures::grassWaterLeftTile, "assets/grass_water_left.png"},
		{Textures::grassWaterRightTile, "assets/grass_water_right.png"},
		{Textures::heartPowerup, "assets/heart_powerup.png"},
		{Textures::msPowerup, "assets/movement_speed_powerup.png"},
		{Textures::asPowerup, "assets/atk_speed_powerup.png"},
		{Textures::chickenKnight, "assets/chicken_knight_spritesheet.png"},
		{Textures::chickenWizard, "assets/chicken_wizard_spritesheet.png"},
		{Textures::chickenPessant, "assets/chicken_spritesheet.png"},
		{Textures::chickenMLady, "assets/chicken_mlady_spritesheet.png"},
		{Textures::chickenNeutralPessant, "assets/chicken_neutral.png"},
		{Textures::chickenNeutralKnight, "assets/chicken_neutral_knight.png"},
		{Textures::chickenNeutralWizard, "assets/chicken_neutral_wizard.png"},
		{Textures::chickenNeutralMLady, "assets/chicken_neutral_mlady.png"},
		{Textures::startScreen, "assets/startscreen.png"},
	});
	std::cout << "Texture-Map created" << std::endl;
}

void chickengame::GameImplementation::loadSoundEffects() {
	this->gameInternal->soundManager->getInstance()->addSoundEffects({
		{SoundEffects::eggThrow, "assets/sound/throw_egg.wav"},
		{SoundEffects::steps, "assets/sound/steps.wav"}
	});
	std::cout << "SoundEffects-Map created" << std::endl;
}


