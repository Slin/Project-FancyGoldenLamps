//
// Created by Nils Daumann on 17.08.16.
//

#include "PlayerEntity.h"

namespace FGL
{
	PlayerEntity::PlayerEntity()
	{
		_object = World::CreateSprite("assets/textures/player.png");
		_object->move(0.0f, -64.0f);

		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(_object->getPosition().x/World::GetInstance()->GetScaleFactor()*WORLD_TO_BOX2D, _object->getPosition().y/World::GetInstance()->GetScaleFactor()*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(_object->getLocalBounds().width*0.5f*WORLD_TO_BOX2D, _object->getLocalBounds().height*0.5f*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		_body->CreateFixture(&fixtureDef);
	}

	PlayerEntity::~PlayerEntity()
	{
		delete _object;
	}

	void PlayerEntity::Update(float timeStep)
	{
		if(_object && _body)
		{
			_object->setPosition(_body->GetPosition().x*World::GetInstance()->GetScaleFactor()/WORLD_TO_BOX2D, _body->GetPosition().y*World::GetInstance()->GetScaleFactor()/WORLD_TO_BOX2D);
			_object->setRotation(_body->GetAngle()*180.0f/3.14f);
		}
	}

	void PlayerEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);
	}
}