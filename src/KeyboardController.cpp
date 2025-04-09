#include "KeyboardController.h"

#include "GameInternal.h"
#include "MusicAndSoundImplementation.h"
#include "SpriteComponent.h"
#include "TextureEnumImplementation.h"
#include "TransformComponent.h"
#include "Entities.h"
#include <DataComponent.h>

KeyboardController::KeyboardController(InputComponent* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity)
    : input(input), up(up), down(down), left(left), right(right), fire(fire), fireVelocity(fireVelocity)
{
	sprite = &input->entity->getComponent<SpriteComponent>();
	transform = &input->entity->getComponent<TransformComponent>();
}

// void KeyboardController::init()
// {
// 	sprite = &input->entity->getComponent<SpriteComponent>();
// 	transform = &input->entity->getComponent<TransformComponent>();
// }

void KeyboardController::processMovement()
{
	transform->direction.x = 0;
	transform->direction.y = 0;
	sprite->playAnimation("IDLE");

	if (input->isKeyDown(left))
	{
		transform->direction.x = -1;
		sprite->playAnimation("WALK");
		sprite->setDirection(Direction::LEFT);
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (input->isKeyDown(right))
	{
		transform->direction.x = 1;
		sprite->playAnimation("WALK");
		sprite->setDirection(Direction::RIGHT);
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (input->isKeyDown(up))
	{
		transform->direction.y = -1;
		sprite->playAnimation("WALK");
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (input->isKeyDown(down))
	{
		transform->direction.y = 1;
		sprite->playAnimation("WALK");
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}

	if (input->isKeyDown(fire))
	{
		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - lastFireTime >= (this->input->entity->hasComponent<DataComponent>()
			? this->input->entity->getComponent<DataComponent>().getEntry<int>("fireCooldown").value_or(INT_MAX)
			: INT_MAX))
		{
			lastFireTime = currentTicks;

			// player is a missleading name for a component
			player = &input->entity->getComponent<TransformComponent>();

			//checks player source via the firing velocity
			//TODO: adding actual projectile textures
			if (fireVelocity.x > 0)
			{
				sprite->setDirection(Direction::RIGHT);
				chickengame::Entities::createProjectile(
					Vector2D(player->position.x, player->position.y),
					fireVelocity,
					1,
					180,
					120,
					Textures::egg,
					input->entity,
					SoundEffects::eggThrow
				);
			}

			else
			{
				sprite->setDirection(Direction::LEFT);
				chickengame::Entities::createProjectile(
					Vector2D(player->position.x, player->position.y),
					fireVelocity,
					1,
					180,
					120,
					Textures::egg,
					input->entity,
					SoundEffects::eggThrow
				);
			}

		}
	}
}