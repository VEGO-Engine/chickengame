#pragma once

#include <tuple>
#include <Entity.h>
#include <functional>
#include <KeyboardController.h>

namespace chickengame
{
    namespace pickupables
    {
        constexpr int BUFF_DURATION = 3000;

        void heartEffect(Entity* player);
        void movementSpeedEffect(Entity* player);
        void atkSpeedEffect(Entity* player);

        static std::vector<std::tuple<std::function<void (Entity*)>, std::string>> pickupableList =
        {
            std::make_tuple(chickengame::pickupables::heartEffect, "assets/heart_powerup.png"),
            std::make_tuple(chickengame::pickupables::movementSpeedEffect, "assets/movement_speed_powerup.png"),
            std::make_tuple(chickengame::pickupables::atkSpeedEffect, "assets/atk_speed_powerup.png")
        };
    }
}