#pragma once

#include "Vector2D.h"
#include "Constants.h" // TODO: change so gamespecific constants are in own file
#include "SoundManager.h"
#include "InputComponent.h"

class TransformComponent;
class SpriteComponent;

class KeyboardController
{
public:
	KeyboardController(InputComponent* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity);
	~KeyboardController() = default;
	
	// void init();
	void processMovement();

private:
	InputComponent* input;
	Key up;
	Key down;
	Key left;
	Key right;
	Key fire;

	TransformComponent* transform;
	SpriteComponent* sprite;

	TransformComponent* player; //for starting position of projectile
	Vector2D fireVelocity; //decide source of projectile and flying direction

	//for attack cooldown in between shots
	uint32_t lastFireTime = 0;
};
