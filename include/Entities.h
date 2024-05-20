#pragma once

#include "Animations.h"

#include <Entity.h>
#include <Game.h>
#include <Manager.h>
#include <SpriteComponent.h>
#include <KeyboardController.h>
#include <StatEffectsComponent.h>
#include <HealthComponent.h>
#include <TransformComponent.h>

namespace chickengame::entities
{
    void initialize(Manager& manager)
    {
        Entity& player1 = manager.addEntity();
        Entity& player2 = manager.addEntity();

        const char* player1Sprite;
        const char* player2Sprite;

        chickengame::selectCharacters(player1Sprite, player2Sprite);

        player1.setTeam(Entity::TeamLabel::BLUE);
        player1.addComponent<TransformComponent>(80,80,2); //posx, posy, scale
        player1.addComponent<SpriteComponent>(player1Sprite, true, &chickengame::animation::animationMap, "IDLE"); //adds sprite (32x32px), path needed
        player1.addComponent<KeyboardController>(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_E, Vector2D(2, 0));//custom keycontrols can be added
        player1.addComponent<ColliderComponent>("player", 0.8f); //ad, chickengame::animation::animationMap, "IDLE"ds tag (for further use, reference tag)
        player1.addComponent<HealthComponent>(5, Direction::LEFT, "assets/heart.png");
        player1.addComponent<StatEffectsComponent>();
        player1.addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


        player2.setTeam(Entity::TeamLabel::RED);
        player2.addComponent<TransformComponent>(600, 500, 2);
        player2.addComponent<SpriteComponent>(player2Sprite, true, &chickengame::animation::animationMap, "IDLE");
        player2.addComponent<KeyboardController>(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_RCTRL, Vector2D(-2, 0));
        player2.addComponent<ColliderComponent>("enemy", 0.8f);
        player2.addComponent<HealthComponent>(5, Direction::RIGHT, "assets/heart.png");
        player2.addComponent<StatEffectsComponent>();
        player2.addGroup((size_t) Entity::GroupLabel::PLAYERS);
    }
}
