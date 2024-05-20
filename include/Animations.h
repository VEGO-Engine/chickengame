#pragma once

#include <string>
#include <map>
#include <memory>

#include <AnimationHandler.h>

 //Idea is that each animation type is assigned a number that number is then the number of the row
 //the animation sprites are on the spritesheet e.g. row 0 are the frames next to each other that play out the idle animation
 //therefore IDLE

namespace chickengame::animation {
    std::map<std::string, std::unique_ptr<Animation>> animationMap;

    void initialize()
    {
        animationMap.emplace("IDLE", std::make_unique<Animation>(0, 2, 200));
        animationMap.emplace("WALK", std::make_unique<Animation>(1, 2, 200));
    }
}
