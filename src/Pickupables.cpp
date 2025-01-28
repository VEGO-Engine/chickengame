#include "Pickupables.h"
#include <HealthComponent.h>
#include <StatEffectsComponent.h>
#include <iostream>

void chickengame::pickupables::heartEffect(Entity* player)
{
    if (player->getComponent<HealthComponent>().getHealth() < 5) {
        player->getComponent<HealthComponent>().modifyHealth(1);
    }
}

void chickengame::pickupables::movementSpeedEffect(Entity* player)
{
    int basePlayerSpeed = player->getComponent<DataComponent>().getEntry<int>("speed").value_or(0);
    player->getComponent<DataComponent>().setEntry("speed", 4);
    player->getComponent<StatEffectsComponent>().addEffect(BUFF_DURATION, [=]() {
        player->getComponent<DataComponent>().setEntry("speed", basePlayerSpeed);
    });
}

void chickengame::pickupables::atkSpeedEffect(Entity* player)
{
    int baseFireCooldown = player->getComponent<DataComponent>().getEntry<int>("fireCooldown").value_or(INT_MAX);
    player->getComponent<DataComponent>().setEntry("fireCooldown", 500);
    player->getComponent<StatEffectsComponent>().addEffect(BUFF_DURATION, [=]() {
        player->getComponent<DataComponent>().setEntry("fireCooldown", baseFireCooldown);
    });
}