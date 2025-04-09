#include "Controls.h"

#include "GameInternal.h"
#include "MusicAndSoundImplementation.h"
#include "SpriteComponent.h"
#include "TextureEnumImplementation.h"
#include "TransformComponent.h"
#include "Entities.h"
#include "ConsoleListener.h"
#include <DataComponent.h>
#include <InteractionEventdataStruct.h>
#include <VEGO_Event.h>
#include <VEGO.h>
#include <Entity.h>

void chickengame::Controls::initControls(std::vector<Entity*>& players)
{
	VEGO_Game().inputManager->registerAction("WalkLeft", {InputManager::Key::A, InputManager::Key::LEFT}, [players](bool isKeyUp) {
		std::cout << "Walk Left action triggered!" << std::endl;
		if (isKeyUp){
			players[0]->getComponent<TransformComponent>().direction.x += 1;
			return;
		}
		players[0]->getComponent<TransformComponent>().direction.x = -1;
		players[0]->getComponent<SpriteComponent>().playAnimation("WALK");
		players[0]->getComponent<SpriteComponent>().setDirection(Direction::LEFT);
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}, "Gameplay");
	
	VEGO_Game().inputManager->registerAction("WalkRight", {InputManager::Key::D, InputManager::Key::RIGHT}, [players](bool isKeyUp) {
		std::cout << "Walk Right action triggered!" << std::endl;
		if (isKeyUp){
			players[0]->getComponent<TransformComponent>().direction.x -= 1;
			return;
		}
		players[0]->getComponent<TransformComponent>().direction.x = 1;
		players[0]->getComponent<SpriteComponent>().playAnimation("WALK");
		players[0]->getComponent<SpriteComponent>().setDirection(Direction::RIGHT);
		SoundManager::playSound(SoundEffects::steps, false, PLAY_ONCE, MAX_VOLUME, 1);
	}, "Gameplay");
	
	VEGO_Game().inputManager->registerAction("SwitchToGameplay", {InputManager::Key::TAB}, [](bool isKeyUp) {
		if (isKeyUp) return;
		std::cout << "Switching to Gameplay context!" << std::endl;
		VEGO_Game().inputManager->setActiveContext("Gameplay");
	}, "Default");
	
	VEGO_Game().inputManager->registerAction("SwitchToDefault", {InputManager::Key::TAB}, [](bool isKeyUp) {
		if (isKeyUp) return;
		std::cout << "Switching to Default context!" << std::endl;
		VEGO_Game().inputManager->setActiveContext("Default");
	}, "Gameplay");

	VEGO_Game().inputManager->registerAction("test", {InputManager::Key::U}, [](bool isKeyUp){
		if (isKeyUp) return;
	
		InteractionEventdataStruct* data = new InteractionEventdataStruct();
		data->data = new std::string("test data");
		data->strategy = static_cast<std::underlying_type<InteractionManager::TargetingStrategy>::type>(InteractionManager::TargetingStrategy::closest);
		data->targetingReference = std::make_shared<Vector2D>(0,0);
	
		data->triggerEvent();
	}, "Default");
}
