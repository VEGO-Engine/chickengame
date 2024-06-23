#include "KeyboardController.h"

#include <thread>
#include <chrono>

#include "GameInternal.h"
#include "AssetManager.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

KeyboardController::KeyboardController(InputSystemComponent* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity)
    : m_input(input), m_up(up), m_down(down), m_left(left), m_right(right), m_fire(fire), m_fireVelocity(fireVelocity)
{
	m_sprite = &m_input->entity->getComponent<SpriteComponent>();
	m_transform = &m_input->entity->getComponent<TransformComponent>();

	initInputActions();
}

// this is an ugly solution.
void KeyboardController::idle()
{
	m_transform->direction.x = 0;
	m_transform->direction.y = 0;
	m_sprite->playAnimation("IDLE");
}

void KeyboardController::modifyAtkSpeed(int8_t modifier)
{
	this->m_fireCooldown -= modifier * 400;
}

void KeyboardController::initInputActions()
{
	// need to use std::bind because passed functions are member functions
	m_input->bindAction("MoveUp", m_up, std::bind(&KeyboardController::moveUp, this));
    m_input->bindAction("MoveDown", m_down, std::bind(&KeyboardController::moveDown, this));
    m_input->bindAction("MoveLeft", m_left, std::bind(&KeyboardController::moveLeft, this));
    m_input->bindAction("MoveRight", m_right, std::bind(&KeyboardController::moveRight, this));
    m_input->bindAction("Fire", m_fire, std::bind(&KeyboardController::fire, this));
}

void KeyboardController::moveUp()
{
	m_transform->direction.y = -1;
	m_sprite->playAnimation("WALK");
	SoundManager::playSound(m_input->entity->getManager().getGame(), STEPS);
}

void KeyboardController::moveDown()
{
	m_transform->direction.y = 1;
	m_sprite->playAnimation("WALK");
	SoundManager::playSound(m_input->entity->getManager().getGame(), STEPS);
}

void KeyboardController::moveLeft()
{
	m_transform->direction.x = -1;
	m_sprite->playAnimation("WALK");
	m_sprite->setDirection(Direction::LEFT);
	SoundManager::playSound(m_input->entity->getManager().getGame(), STEPS);
}

void KeyboardController::moveRight()
{
	m_transform->direction.x = 1;
	m_sprite->playAnimation("WALK");
	m_sprite->setDirection(Direction::RIGHT);
	SoundManager::playSound(m_input->entity->getManager().getGame(), STEPS);
}

void KeyboardController::fire()
{
	Uint32 currentTicks = SDL_GetTicks();

	if (currentTicks - m_lastFireTime >= m_fireCooldown)
	{

		m_player = &m_input->entity->getComponent<TransformComponent>();

		//checks player source via the firing velocity
		//TODO: adding actual projectile textures
		if (m_fireVelocity.x > 0)
		{
			m_sprite->setDirection(Direction::RIGHT);
			m_input->entity->getManager().getGame()->assets->createProjectile(Vector2D(m_player->position.x, m_player->position.y), m_fireVelocity,
				1, 180, 2, "assets/egg.png", m_input->entity->getTeam());
		}

		else
		{
			m_sprite->setDirection(Direction::LEFT);
			m_input->entity->getManager().getGame()->assets->createProjectile(Vector2D(m_player->position.x, m_player->position.y), m_fireVelocity,
				1, 180, 2, "assets/egg.png", m_input->entity->getTeam());
		}

		m_lastFireTime = currentTicks;
	}
}