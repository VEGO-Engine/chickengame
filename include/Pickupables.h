#pragma once

#include <tuple>
#include <Entity.h>
#include <functional>
#include <KeyboardController.h>

#include "TextureEnumImplementation.h"

namespace chickengame
{
    namespace pickupables
    {
        constexpr int BUFF_DURATION = 3000; // milliseconds

        void heartEffect(Entity* player);
        void movementSpeedEffect(Entity* player);
        void atkSpeedEffect(Entity* player);

        static std::vector<std::tuple<std::function<void (Entity*)>, Textures>> pickupableList =
        {
            std::make_tuple(chickengame::pickupables::heartEffect, Textures::heartPowerup),
            std::make_tuple(chickengame::pickupables::movementSpeedEffect, Textures::msPowerup),
            std::make_tuple(chickengame::pickupables::atkSpeedEffect, Textures::asPowerup)
        };
    }
}