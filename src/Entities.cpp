#include "Entities.h"

#include "Chickengame.h"

namespace chickengame {
    void Entities::initialize(GameImplementation* game)
    {
        Entity& player1 = game->gameInternal->manager.addEntity();
        Entity& player2 = game->gameInternal->manager.addEntity();

        const char* player1Sprite;
        const char* player2Sprite;

        game->selectCharacters(player1Sprite, player2Sprite);

        setTeam(TeamLabel::BLUE, &player1);
        player1.addComponent<TransformComponent>(80,80,2); //posx, posy, scale
        player1.addComponent<SpriteComponent>(player1Sprite, true, &chickengame::animations::animationMap, "IDLE"); //adds sprite (32x32px), path needed
        player1.addComponent<InputComponent>();
        player1.addComponent<ColliderComponent>("player", 0.8f); //ad, chickengame::animations::animationMap, "IDLE"ds tag (for further use, reference tag)
        player1.addComponent<HealthComponent>(5, Direction::LEFT, "assets/heart.png");
        player1.addComponent<StatEffectsComponent>();
        player1.addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


        setTeam(TeamLabel::RED, &player2);
        player2.addComponent<TransformComponent>(600, 500, 2);
        player2.addComponent<SpriteComponent>(player2Sprite, true, &chickengame::animations::animationMap, "IDLE");
        player2.addComponent<InputComponent>();
        player2.addComponent<ColliderComponent>("enemy", 0.8f);
        player2.addComponent<HealthComponent>(5, Direction::RIGHT, "assets/heart.png");
        player2.addComponent<StatEffectsComponent>();
        player2.addGroup((size_t) Entity::GroupLabel::PLAYERS);
    }

}
