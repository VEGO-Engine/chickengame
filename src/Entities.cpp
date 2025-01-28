#include "Entities.h"

#include "Chickengame.h"

#include <VEGO.h>
#include <ProjectileComponent.h>

namespace chickengame {
    void Entities::initialize(GameImplementation* game)
    {
        this->player1 = &game->gameInternal->manager.addEntity();
        this->player2 = &game->gameInternal->manager.addEntity();

        Textures player1Sprite;
        Textures player2Sprite;

        game->selectCharacters(player1Sprite, player2Sprite);

        setTeam(TeamLabel::BLUE, this->player1);
        this->player1->addComponent<DataComponent>();
        addDefaultPlayerStats(this->player1);
        this->player1->addComponent<TransformComponent>(80,80,2); //posx, posy, scale
        this->player1->addComponent<SpriteComponent>(player1Sprite, true, &animations::animationMap, "IDLE", 5); //adds sprite (32x32px), path needed
        this->player1->addComponent<InputComponent>();
        this->player1->addComponent<ColliderComponent>("player", 0.8f); //ad, chickengame::animations::animationMap, "IDLE"ds tag (for further use, reference tag)
        this->player1->addComponent<HealthComponent>(5);
        this->player1->addComponent<StatEffectsComponent>();
        this->player1->addGroup((size_t) Entity::GroupLabel::PLAYERS); //tell programm what group it belongs to for rendering order


        setTeam(TeamLabel::RED, this->player2);
        this->player2->addComponent<DataComponent>();
        addDefaultPlayerStats(this->player2);
        this->player2->addComponent<TransformComponent>(600, 500, 2);
        this->player2->addComponent<SpriteComponent>(player2Sprite, true, &chickengame::animations::animationMap, "IDLE", 5);
        this->player2->addComponent<InputComponent>();
        this->player2->addComponent<ColliderComponent>("enemy", 0.8f);
        this->player2->addComponent<HealthComponent>(5);
        this->player2->addComponent<StatEffectsComponent>();
        this->player2->addGroup((size_t) Entity::GroupLabel::PLAYERS);
    }

    void Entities::createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, Textures textureEnum, Entity* owner)
    {
        auto& projectile(VEGO_Game().manager.addEntity());
        projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, scale); //32x32 is standard size for objects
        projectile.addComponent<SpriteComponent>(textureEnum, 4);
        projectile.addComponent<ProjectileComponent>(range, speed, velocity, owner);
        projectile.addComponent<ColliderComponent>("projectile", 0.6f);
        projectile.addComponent<DataComponent>();
        projectile.addGroup((size_t)Entity::GroupLabel::PROJECTILE);
        projectile.addComponent<DataComponent>();
        projectile.getComponent<DataComponent>().setEntry("speed", speed);
    }

}
