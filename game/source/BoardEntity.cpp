//
// Created by Nils Daumann on 17.08.16.
//

#include "BoardEntity.h"

namespace FGL
{
	BoardEntity::BoardEntity()
	{
		_object = World::CreateSprite("assets/textures/background.png");

		b2Body *body = World::CreateStaticBoxCollider(sf::Vector2f(0, 650), sf::Vector2u(1920, 100));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, -650), sf::Vector2u(1920, 100));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-650, 0), sf::Vector2u(100, 1080));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(650, 0), sf::Vector2u(100, 1080));
		_bodies.push_back(body);



		body = World::CreateStaticBoxCollider(sf::Vector2f(-125, 575), sf::Vector2u(50, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-425, 575), sf::Vector2u(50, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-250, 325), sf::Vector2u(200, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-550, 225), sf::Vector2u(100, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-350, -25), sf::Vector2u(100, 150));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-500, -375), sf::Vector2u(200, 50));
		_bodies.push_back(body);


		body = World::CreateStaticBoxCollider(sf::Vector2f(125, 575), sf::Vector2u(50, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(425, 575), sf::Vector2u(50, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(250, 325), sf::Vector2u(200, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(550, 225), sf::Vector2u(100, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(350, -25), sf::Vector2u(100, 150));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(500, -375), sf::Vector2u(200, 50));
		_bodies.push_back(body);


		body = World::CreateStaticBoxCollider(sf::Vector2f(0, 75), sf::Vector2u(100, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, -225), sf::Vector2u(100, 50));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, -525), sf::Vector2u(100, 150));
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
