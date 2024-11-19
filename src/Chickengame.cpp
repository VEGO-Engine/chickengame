#include "Chickengame.h"

#include "Pickupables.h"
#include "TextureDict.h"
#include "Animations.h"

#include "TextureEnumImplementation.h"

#include <iostream>
#include <vector>
#include <map>
#include <GameInternal.h>
#include <AssetManager.h>
#include <HealthComponent.h>
#include <InputComponent.h>
#include <Map.h>

vego::GameRegistryHelper<chickengame::GameImplementation> this_is_a_variable_so_the_constructor_get_called_without_using_a_define_macro("Chickengame");

void chickengame::GameImplementation::init()
{
	loadTextures();

	Map map("assets/grassy-river.tmx");
	map.generateTiles();

	//this->gameInternal->map->loadMap("assets/SDL_map_test.txt", 25, 20, this->gameInternal, &(chickengame::tiles::tileDictionary));
	chickengame::animations::initialize();
	Entities::getInstance().initialize(this);

	this->gameInternal->assets->addSoundEffect("steps", "assets/sound/steps.wav");
	this->gameInternal->assets->addSoundEffect("throw_egg", "assets/sound/throw_egg.wav");

	std::vector<Entity*>& players = this->gameInternal->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS);
	playerControllerA = new KeyboardController(&players[0]->getComponent<InputComponent>(), Key::W, Key::S, Key::A, Key::D, Key::E, Vector2D(2, 0));
	playerControllerB = new KeyboardController(&players[1]->getComponent<InputComponent>(), Key::UP, Key::DOWN, Key::LEFT, Key::RIGHT, Key::RIGHT_CTRL, Vector2D(-2, 0));
}


void chickengame::GameImplementation::update()
{
	playerControllerA->processMovement();
	playerControllerB->processMovement();

	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		this->gameInternal->assets->createPowerup(
			this->gameInternal->assets->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0] function
			std::get<1>(pickupable) // tuple[1] texture
		);
	}

	for (auto& player : this->gameInternal->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS))
	{
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
	this->gameInternal->stopGame();
}

chickengame::Entities::TeamLabel chickengame::GameImplementation::getWinner() const
{
    return this->winner;
}

void chickengame::GameImplementation::selectCharacters(Textures &playerSprite, Textures &enemySprite)
{
	/*
	// TODO: move this whereever it makes sense (maybe game as a member)
	std::map<int, std::pair<const char*, const char*>> characterSprites;
	characterSprites[0] = std::make_pair("assets/chicken_neutral_knight.png", "assets/chicken_knight_spritesheet.png");
	characterSprites[1] = std::make_pair("assets/chicken_neutral.png", "assets/chicken_spritesheet.png");
	characterSprites[2] = std::make_pair("assets/chicken_neutral_wizard.png", "assets/chicken_wizard_spritesheet.png");
	characterSprites[3] = std::make_pair("assets/chicken_neutral_mlady.png", "assets/chicken_mlady_spritesheet.png");

	SDL_Rect playerCharacterRects[CHARACTER_COUNT];
	SDL_Rect enemyCharacterRects[CHARACTER_COUNT];
	SDL_Texture* characterTextures[CHARACTER_COUNT];

	int playerSelection = 0;
	int enemySelection = 0;

	// load textures
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		characterTextures[i] = IMG_LoadTexture(this->gameInternal->renderer, characterSprites.find(i)->second.first);
	}

	// set up initial positions for character rects
	for (int i = 0; i < CHARACTER_COUNT; ++i)
	{
		playerCharacterRects[i] = { 134 + (i % 2) * 118, 272 + ((i >= 2) ? 114 : 0), 64, 64 };
		enemyCharacterRects[i] = { 485 + (i % 2) * 118, 273 + ((i >= 2) ? 114 : 0), 64, 64 };
	}

	bool hasQuit = false;

	while (!hasQuit)
	{
		SDL_PollEvent(&this->gameInternal->event);

		if (this->gameInternal->event.type == SDL_QUIT)
		{
			hasQuit = true;
		}

		if (this->gameInternal->event.type == SDL_KEYDOWN)
		{
			if (this->gameInternal->event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				break;
			}

			switch (this->gameInternal->event.key.keysym.scancode)
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

		SDL_Texture* backgroundTexture = this->gameInternal->textureManager->loadTexture(Textures::charSelection);
		SDL_RenderClear(this->gameInternal->renderer);
		SDL_RenderCopy(this->gameInternal->renderer, backgroundTexture, NULL, NULL);

		for (int i = 0; i < CHARACTER_COUNT; ++i)
		{
			SDL_RenderCopy(this->gameInternal->renderer, characterTextures[i], nullptr, &playerCharacterRects[i]);
			SDL_RenderCopy(this->gameInternal->renderer, characterTextures[i], nullptr, &enemyCharacterRects[i]);
		}

		SDL_SetRenderDrawColor(this->gameInternal->renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(this->gameInternal->renderer, &playerCharacterRects[playerSelection]);
		SDL_RenderDrawRect(this->gameInternal->renderer, &enemyCharacterRects[enemySelection]);

		SDL_RenderPresent(this->gameInternal->renderer);
	}

	if (hasQuit)
	{
		this->gameInternal->stopGame();
		return;
	}

	playerSprite = characterSprites.find(playerSelection)->second.second;
	enemySprite = characterSprites.find(enemySelection)->second.second;
	*/
	playerSprite = Textures::chickenKnight;
	enemySprite = Textures::chickenWizard;
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
    auto& heart(this->gameInternal->manager.addEntity());
    heart.addComponent<TransformComponent>(locationX,5,2);
    heart.addComponent<SpriteComponent>(Textures::heart, 10);
    heart.addGroup((size_t)Entity::GroupLabel::HEARTS);
	return &heart;
}

void chickengame::GameImplementation::loadTextures() {
	this->gameInternal->textureManager->addTextures({
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
	});
	std::cout << "Texture-Map created" << std::endl;
}
