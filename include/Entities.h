#pragma once

#include "Animations.h"

#include <Entity.h>
#include <Game.h>
#include <GameInternal.h>
#include <Manager.h>
#include <SpriteComponent.h>
#include <InputComponent.h>
#include <StatEffectsComponent.h>
#include <HealthComponent.h>
#include <TransformComponent.h>

namespace chickengame::entities
{
    inline Entity* player1;
    inline Entity* player2;

    inline void initialize(GameImplementation* game)
    {
        chickengame::entities::player1 = &game->gameInternal->manager.addEntity();
        chickengame::entities::player2 = &game->gameInternal->manager.addEntity();

        const char* player1Sprite;
        const char* player2Sprite;

        game->selectCharacters(player1Sprite, player2Sprite);

        player1->setTeam(Entity::TeamLabel::BLUE);
        player1->addComponent<TransformComponent>(80,80,2); //posx, posy, scale
        player1->addComponent<SpriteComponent>(player1Sprite, true, &chickengame::animation::animationMap, "IDLE"); //adds sprite (32x32px), path needed
        player1->addComponent<InputComponent>();
        player1->addComponent<ColliderComponent>("player", 0.8f); //ad, chickengame::animation::animationMap, "IDLE"ds tag (for further use, reference tag)
        player1->addComponent<HealthComponent>(5);
        player1->addComponent<StatEffectsComponent>();
        player1->addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


        player2->setTeam(Entity::TeamLabel::RED);
        player2->addComponent<TransformComponent>(600, 500, 2);
        player2->addComponent<SpriteComponent>(player2Sprite, true, &chickengame::animation::animationMap, "IDLE");
        player2->addComponent<InputComponent>();
        player2->addComponent<ColliderComponent>("enemy", 0.8f);
        player2->addComponent<HealthComponent>(5);
        player2->addComponent<StatEffectsComponent>();
        player2->addGroup((size_t) Entity::GroupLabel::PLAYERS);
    }
}
