#include "StatImplementation.h"

void chickengame::addDefaultPlayerStats(Entity* player) {
    DataComponent& data = player->getComponent<DataComponent>();
    data.setEntry("speed", 180);
    data.setEntry("fireCooldown", 1000);
}
