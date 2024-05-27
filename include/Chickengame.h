#pragma once

#include "KeyboardController.h"

namespace chickengame
{
	void init();
	void update();

	KeyboardController* playerControllerA;
	KeyboardController* playerControllerB;
}