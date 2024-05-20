#include "Chickengame.h"

#include "Pickupables.h"
#include "TextureDict.h"
#include "Animations.h"
#include "Entities.h"

#include <iostream>
#include <map>
#include <Game.h>
#include <AssetManager.h>
#include <HealthComponent.h>
#include <Map.h>

void chickengame::init()
{
	engine::game->map->loadMap("assets/SDL_map_test.txt", 25, 20, engine::game, &(chickengame::tiles::tileDictionary));
	chickengame::animation::initialize();
	chickengame::entities::initialize(engine::game->manager);
}

void chickengame::update()
{
	int powerupSpawn = rand() % 500;

	if (powerupSpawn == 0)
	{
		int pickupableType = rand() % chickengame::pickupables::pickupableList.size();
		std::tuple pickupable = chickengame::pickupables::pickupableList.at(pickupableType);
		// gen rand tuple
		engine::game->assets->createPowerup(
			engine::game->assets->calculateSpawnPosition(),
			std::get<0>(pickupable), // tuple[0] function
			std::get<1>(pickupable) // tuple[1] texture
		);
	}

	// needs to be in game.cpp to have access to internal functions
	for (auto& player : engine::game->manager.getGroup((size_t) Entity::GroupLabel::PLAYERS)) {
		if (player->getComponent<HealthComponent>().getHealth() <= 0) {
			engine::game->setWinner(player->getTeam());
		}
	}
}

void chickengame::selectCharacters(const char* &playerSprite, const char* &enemySprite)
{
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
		characterTextures[i] = IMG_LoadTexture(engine::game->renderer, characterSprites.find(i)->second.first);
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
		SDL_PollEvent(&engine::game->event);

		if (engine::game->event.type == SDL_QUIT)
		{
			hasQuit = true;
		}

		if (engine::game->event.type == SDL_KEYDOWN)
		{
			if (engine::game->event.key.keysym.scancode == SDL_SCANCODE_RETURN)
			{
				break;
			}

			switch (engine::game->event.key.keysym.scancode)
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

		SDL_Texture* backgroundTexture = engine::game->textureManager->loadTexture("assets/characterSelection.png");
		SDL_RenderClear(engine::game->renderer);
		SDL_RenderCopy(engine::game->renderer, backgroundTexture, NULL, NULL);

		for (int i = 0; i < CHARACTER_COUNT; ++i)
		{
			SDL_RenderCopy(engine::game->renderer, characterTextures[i], nullptr, &playerCharacterRects[i]);
			SDL_RenderCopy(engine::game->renderer, characterTextures[i], nullptr, &enemyCharacterRects[i]);
		}

		SDL_SetRenderDrawColor(engine::game->renderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(engine::game->renderer, &playerCharacterRects[playerSelection]);
		SDL_RenderDrawRect(engine::game->renderer, &enemyCharacterRects[enemySelection]);

		SDL_RenderPresent(engine::game->renderer);
	}

	if (hasQuit)
	{
		engine::game->setRunning(false);
		return;
	}

	playerSprite = characterSprites.find(playerSelection)->second.second;
	enemySprite = characterSprites.find(enemySelection)->second.second;
	engine::game->setRunning(true);
}

namespace engine {
	gamefunction init = chickengame::init;
	gamefunction update = chickengame::update;
}