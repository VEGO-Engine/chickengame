#include "Animations.h"
namespace chickengame::animations {
    std::map<std::string, std::unique_ptr<Animation>> animationMap;

    void initialize()
    {
        animationMap.emplace("IDLE", std::make_unique<Animation>(0, 2, 200));
        animationMap.emplace("WALK", std::make_unique<Animation>(1, 2, 200));
    }
}