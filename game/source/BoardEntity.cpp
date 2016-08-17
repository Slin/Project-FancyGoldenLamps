//
// Created by Nils Daumann on 17.08.16.
//

#include "BoardEntity.h"

namespace FGL
{
	BoardEntity::BoardEntity()
	{
		_object = new sf::Sprite();
		_object->setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/background_test.png"));

		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->setScale(World::GetInstance()->GetScaleFactor(), World::GetInstance()->GetScaleFactor());
		_object->setPosition(World::GetInstance()->GetWindow()->getSize().x*0.5f, World::GetInstance()->GetWindow()->getSize().y*0.5f);
	}

	void BoardEntity::Update(float timeStep)
	{

	}

	void BoardEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);
	}
}
