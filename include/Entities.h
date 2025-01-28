#pragma once

#include <unordered_map>
#include <vector> // Ensure vector is included for std::vector
#include "Entity.h" // Ensure you have the correct include paths
#include "Game.h"
#include "GameInternal.h"
#include "Manager.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "StatEffectsComponent.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include "DataComponent.h"
#include "Animations.h"
#include "StatImplementation.h"

namespace chickengame
{
    class GameImplementation;

    using Team = std::size_t;

    class Entities
    {
    public:
        enum class TeamLabel
        {
            NONE, //!< No team
            BLUE, //!< Team blue
            RED   //!< Team red
        };

        static Entities& getInstance()
        {
            static Entities instance;
            return instance;
        }

        // Public methods
        void setTeam(TeamLabel teamLabel, Entity* mEntity)
        {
            entityToTeam[mEntity] = static_cast<Team>(teamLabel);
        }

        TeamLabel getTeam(Entity* mEntity)
        {
            return static_cast<TeamLabel>(entityToTeam.at(mEntity));
        }

        void refreshTeams(Entity& mEntity)
        {
            std::vector<Entity*> entitiesToRemove;
            
            for (auto& entry : entityToTeam) {
                Entity* entity = entry.first;
                
                if (!entity->isActive() || getTeam(entity) != static_cast<TeamLabel>(entry.second)) {
                    entitiesToRemove.push_back(entity);
                }
            }

            for (Entity* entity : entitiesToRemove) {
                entityToTeam.erase(entity);
            }
        }

        void initialize(GameImplementation* game);
        static void createProjectile(Vector2D pos, Vector2D velocity, int scale, int range, int speed, Textures textureEnum, Entity* owner);

        Entity* getPlayer1() { return this->player1; };
        Entity* getPlayer2() { return this->player2; };

    private:
        Entities() {}

        ~Entities() {}

        Entities(const Entities&) = delete;
        Entities& operator=(const Entities&) = delete;

        std::unordered_map<Entity*, Team> entityToTeam;

        Entity* player1;
        Entity* player2;
    };
}
