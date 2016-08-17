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
		fixtureDef.friction = 0.2f;
		_boxFixture = _body->CreateFixture(&fixtureDef);
		_body->SetFixedRotation(true);
		_body->SetBullet(true);
	}

	PlayerEntity::~PlayerEntity()
	{
		delete _object;
	}

	bool PlayerEntity::IsGrounded()
	{
		b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
		while(contact)
		{
			if(contact->IsTouching() && (contact->GetFixtureA() == _boxFixture || contact->GetFixtureB() == _boxFixture))
			{
				b2Vec2 pos = _body->GetPosition();
				b2WorldManifold manifold;
				contact->GetWorldManifold(&manifold);
				bool below = true;
				for(int j = 0; j < b2_maxManifoldPoints; j++)
				{
					below = (below && (manifold.points[j].y - pos.y > 0.5f) && fabsf(manifold.normal.y) > 0.8f);
				}

				if(below)
				{
					return true;
				}

				return false;
			}

			contact = contact->GetNext();
		}
		return false;
	}

	void PlayerEntity::Update(float timeStep)
	{
		sf::Vector2f moveDirection;
		moveDirection.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D)-sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		moveDirection.y = sf::Keyboard::isKeyPressed(sf::Keyboard::W);//-sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		moveDirection *= 1.0f;

		if(moveDirection.y > 0.0f && IsGrounded())
		{
			_body->ApplyLinearImpulse(b2Vec2(0.0f, -3.0f), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
		}

		if(fabsf(moveDirection.x) > 0.0f)
		{
			_boxFixture->SetFriction(0.0f);
		}
		else
		{
			_boxFixture->SetFriction(10.0f);
		}

		if((moveDirection.x < 0.0f && _body->GetLinearVelocity().x > -3.0f) || (moveDirection.x > 0.0f && _body->GetLinearVelocity().x < 3.0f))
		{
			_body->ApplyLinearImpulse(b2Vec2(moveDirection.x, 0.0f), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
		}

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