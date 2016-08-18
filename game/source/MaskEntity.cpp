//
// Created by Nils Daumann on 18.08.16.
//

#include "MaskEntity.h"

namespace FGL
{
	MaskEntity::MaskEntity(sf::Vector2f position)
	{
		_object = World::CreateSprite("assets/textures/mask.png");
		_object->setPosition(position);

		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(_object->getPosition().x/World::GetInstance()->GetScaleFactor()*WORLD_TO_BOX2D, _object->getPosition().y/World::GetInstance()->GetScaleFactor()*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(_object->getLocalBounds().width*0.5f*WORLD_TO_BOX2D, _object->getLocalBounds().height*0.5f*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.3f;
		fixtureDef.friction = 3.0f;
		fixtureDef.filter.categoryBits = 0x0004;
		fixtureDef.filter.maskBits = 0x0001|0x0004;
		_body->CreateFixture(&fixtureDef);
	}

	MaskEntity::~MaskEntity()
	{

	}

	void MaskEntity::Update(float timeStep)
	{
		if(_object && _body)
		{
			_object->setPosition(_body->GetPosition().x*World::GetInstance()->GetScaleFactor()/WORLD_TO_BOX2D, _body->GetPosition().y*World::GetInstance()->GetScaleFactor()/WORLD_TO_BOX2D);
			_object->setRotation(_body->GetAngle()*180.0f/3.14f);
		}
	}

	void MaskEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
		{
			window->draw(*_object);
		}
	}

	void MaskEntity::Throw(sf::Vector2f direction)
	{
		_body->ApplyLinearImpulse(b2Vec2(direction.x, direction.y), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
	}
}
