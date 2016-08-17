//
// Created by Nils Daumann on 17.08.16.
//

#include "BoardEntity.h"

namespace FGL
{
	BoardEntity::BoardEntity()
	{
		_object = World::CreateSprite("assets/textures/background_test.png");

		b2Body *body = World::CreateStaticBoxCollider(sf::Vector2u(960, 1250), sf::Vector2u(1920, 100));
		_bodies.push_back(body);
	}

	BoardEntity::~BoardEntity()
	{
		delete _object;
		for(b2Body *body : _bodies)
		{
			World::GetInstance()->GetPhysicsWorld()->DestroyBody(body);
		}
		_bodies.clear();
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
