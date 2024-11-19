#include "KeyboardController.h"

#include "GameInternal.h"
#include "AssetManager.h"
#include "SpriteComponent.h"
#include "TextureEnumImplementation.h"
#include "TransformComponent.h"

KeyboardController::KeyboardController(InputComponent* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity)
    : m_input(input), m_up(up), m_down(down), m_left(left), m_right(right), m_fire(fire), m_fireVelocity(fireVelocity)
{
	m_sprite = &m_input->entity->getComponent<SpriteComponent>();
	m_transform = &m_input->entity->getComponent<TransformComponent>();
}

// void KeyboardController::init()
// {
// 	m_sprite = &m_input->entity->getComponent<SpriteComponent>();
// 	m_transform = &m_input->entity->getComponent<TransformComponent>();
// }

void KeyboardController::processMovement()
{
	m_transform->direction.x = 0;
	m_transform->direction.y = 0;
	m_sprite->playAnimation("IDLE");

	if (m_input->isKeyDown(m_left))
	{
		m_transform->direction.x = -1;
		m_sprite->playAnimation("WALK");
		m_sprite->setDirection(Direction::LEFT);
		SoundManager::playSound(m_input->entity->getManager().getGame(), "steps", false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (m_input->isKeyDown(m_right))
	{
		m_transform->direction.x = 1;
		m_sprite->playAnimation("WALK");
		m_sprite->setDirection(Direction::RIGHT);
		SoundManager::playSound(m_input->entity->getManager().getGame(), "steps", false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (m_input->isKeyDown(m_up))
	{
		m_transform->direction.y = -1;
		m_sprite->playAnimation("WALK");
		SoundManager::playSound(m_input->entity->getManager().getGame(), "steps", false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (m_input->isKeyDown(m_down))
	{
		m_transform->direction.y = 1;
		m_sprite->playAnimation("WALK");
		SoundManager::playSound(m_input->entity->getManager().getGame(), "steps", false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (m_input->isKeyDown(m_fire))
	{
		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - m_lastFireTime >= m_fireCooldown)
		{

			// m_player is a missleading name for a component
			m_player = &m_input->entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (m_fireVelocity.x > 0)
			{
				m_sprite->setDirection(Direction::RIGHT);
				m_input->entity->getManager().getGame()->assets->createProjectile(
					Vector2D(m_player->position.x, m_player->position.y),
					m_fireVelocity,
					1,
					180,
					2,
					Textures::egg,
					m_input->entity
				);
			}

			else
			{
				m_sprite->setDirection(Direction::LEFT);
				m_input->entity->getManager().getGame()->assets->createProjectile(
					Vector2D(m_player->position.x, m_player->position.y),
					m_fireVelocity,
					1,
					180,
					2,
					Textures::egg,
					m_input->entity
				);
			}

			m_lastFireTime = currentTicks;
		}
	}
}

void KeyboardController::modifyAtkSpeed(int8_t modifier)
{
	this->m_fireCooldown -= modifier * 400;
}