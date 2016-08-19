//
// Created by Nils Daumann on 17.08.16.
//

#include "BoardEntity.h"

namespace FGL
{
	BoardEntity::BoardEntity()
	{
		_object = World::CreateSprite("assets/textures/background.png");

		_lightLeft.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/game_spawn.png"));
		_lightLeft.setOrigin(_lightLeft.getLocalBounds().width*0.5f, _lightLeft.getLocalBounds().height*0.5f);
		_lightLeft.setPosition(-538, 506);

		_lightRight.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/game_spawn2.png"));
		_lightRight.setOrigin(_lightRight.getLocalBounds().width*0.5f, _lightRight.getLocalBounds().height*0.5f);
		_lightRight.setPosition(538, 506);

		_lightBig.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/game_biglight.png"));
		_lightBig.setOrigin(_lightBig.getLocalBounds().width*0.5f, _lightBig.getLocalBounds().height*0.5f);

		b2Body *body = World::CreateStaticBoxCollider(sf::Vector2f(0, 1100), sf::Vector2u(1920, 1000));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(0, -1100), sf::Vector2u(1920, 1000));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(-1100, 0), sf::Vector2u(1000, 1080));
		_bodies.push_back(body);

		body = World::CreateStaticBoxCollider(sf::Vector2f(1100, 0), sf::Vector2u(1000, 1080));
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
		_timer += timeStep;

		_lightLeft.setColor(sf::Color(255, 255, 255, 128+127*(sin(_timer*3.0f)*0.5f+0.5f)));
		_lightRight.setColor(sf::Color(255, 255, 255, 128+127*(sin(_timer*3.0f)*0.5f+0.5f)));

		if(rand()%100 < 5)
		{
			_lightBig.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			_lightBig.setColor(sf::Color(255, 255, 255, 0));
		}
	}

	void BoardEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);

		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;
		window->draw(_lightLeft, renderStates);
		window->draw(_lightRight, renderStates);
		window->draw(_lightBig, renderStates);
	}
}
