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
	void modifyAtkSpeed(int8_t modifier);

private:
	InputComponent* m_input;
	Key m_up;
	Key m_down;
	Key m_left;
	Key m_right;
	Key m_fire;

	TransformComponent* m_transform;
	SpriteComponent* m_sprite;

	TransformComponent* m_player; //for starting position of projectile
	Vector2D m_fireVelocity; //decide source of projectile and flying direction

	//for attack cooldown in between shots
	uint32_t m_lastFireTime = 0;
	uint32_t m_fireCooldown = 1000; //in ms can be adjusted to change possible attack-speed
};
