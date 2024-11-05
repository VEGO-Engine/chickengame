#include "Entities.h"

#include "Chickengame.h"

namespace chickengame {
    void Entities::initialize(GameImplementation* game)
    {
        this->player1 = &game->gameInternal->manager.addEntity();
        this->player2 = &game->gameInternal->manager.addEntity();

        TexturesEnum player1Sprite;
        TexturesEnum player2Sprite;

        game->selectCharacters(player1Sprite, player2Sprite);

        setTeam(TeamLabel::BLUE, player1);
        this->player1->addComponent<TransformComponent>(80,80,2); //posx, posy, scale
        this->player1->addComponent<SpriteComponent>(player1Sprite, true, &chickengame::animations::animationMap, "IDLE"); //adds sprite (32x32px), path needed
        this->player1->addComponent<InputComponent>();
        this->player1->addComponent<ColliderComponent>("player", 0.8f); //ad, chickengame::animations::animationMap, "IDLE"ds tag (for further use, reference tag)
        this->player1->addComponent<HealthComponent>(5);
        this->player1->addComponent<StatEffectsComponent>();
        this->player1->addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


        setTeam(TeamLabel::RED, player2);
        this->player2->addComponent<TransformComponent>(600, 500, 2);
        this->player2->addComponent<SpriteComponent>(player2Sprite, true, &chickengame::animations::animationMap, "IDLE");
        this->player2->addComponent<InputComponent>();
        this->player2->addComponent<ColliderComponent>("enemy", 0.8f);
        this->player2->addComponent<HealthComponent>(5);
        this->player2->addComponent<StatEffectsComponent>();
        this->player2->addGroup((size_t) Entity::GroupLabel::PLAYERS);
    }

}
