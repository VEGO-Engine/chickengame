#include "Pickupables.h"

#include <HealthComponent.h>
#include <StatEffectsComponent.h>

void chickengame::pickupables::heartEffect(Entity* player)
{
    if(player->getComponent<HealthComponent>().getHealth() < 5)
        player->getComponent<HealthComponent>().modifyHealth(1);
}

void chickengame::pickupables::movementSpeedEffect(Entity* player)
{
    player->getComponent<StatEffectsComponent>().modifyStatDur(Stats::MOVEMENT_SPEED, BUFF_DURATION, BUFF_VALUE);
}

void chickengame::pickupables::atkSpeedEffect(Entity* player)
{
    player->getComponent<StatEffectsComponent>().modifyStatDur(Stats::ATTACK_SPEED, BUFF_DURATION, BUFF_VALUE);
}