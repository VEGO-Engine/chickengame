#pragma once

#include "Vector2D.h"
#include "Constants.h" // TODO: change so gamespecific constants are in own file
#include "SoundManager.h"
#include "InputComponent.h"

namespace chickengame::Controls
{	
	void initControls(std::vector<Entity*>& players);
	static uint32_t lastFireTime = 0;
};
