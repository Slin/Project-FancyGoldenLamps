//
// Created by Nils Daumann on 17.08.16.
//

#include "BoardEntity.h"

namespace FGL
{
	BoardEntity::BoardEntity()
	{
		_object = World::CreateSprite("assets/textures/background_test2.png");

		b2Body *body = World::CreateStaticBoxCollider(sf::Vector2f(0, 650), sf::Vector2u(1920, 100));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, -650), sf::Vector2u(1920, 100));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-650, 0), sf::Vector2u(100, 1080));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(650, 0), sf::Vector2u(100, 1080));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, 562), sf::Vector2u(285, 75));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-354, 487), sf::Vector2u(77, 226));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(354, 487), sf::Vector2u(77, 226));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(443, 200), sf::Vector2u(110, 158));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-443, 200), sf::Vector2u(110, 158));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, 25), sf::Vector2u(300, 35));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-200, 0), sf::Vector2u(150, 35), 30);
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(200, 0), sf::Vector2u(150, 35), -30);
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
