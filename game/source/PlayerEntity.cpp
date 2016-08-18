//
// Created by Nils Daumann on 17.08.16.
//

#include "PlayerEntity.h"
#include "MaskEntity.h"

#include <iostream>

namespace FGL
{
	PlayerEntity::PlayerEntity() : _throwTimer(100)
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
		fixtureDef.friction = 10.0f;
		fixtureDef.filter.categoryBits = 0x0002;
		fixtureDef.filter.maskBits = 0x0001;
		_boxFixture = _body->CreateFixture(&fixtureDef);
		_body->SetFixedRotation(true);
		_body->SetBullet(true);
	}

	PlayerEntity::~PlayerEntity()
	{
		delete _object;
		World::GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
	}

	bool PlayerEntity::IsGrounded()
	{
		bool grounded = false;
		bool blocked = false;
		b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
		while(contact)
		{
			if(contact->IsTouching() && (contact->GetFixtureA() == _boxFixture || contact->GetFixtureB() == _boxFixture))
			{
				contact->SetFriction(_boxFixture->GetFriction());
				b2WorldManifold manifold;
				contact->GetWorldManifold(&manifold);

				grounded = (grounded || ((contact->GetFixtureA() == _boxFixture)?(manifold.normal.y > 0.4f):(manifold.normal.y < -0.4f)));
				blocked = (blocked || ((contact->GetFixtureA() == _boxFixture)?(manifold.normal.y < -0.2f):(manifold.normal.y > 0.2f)));
			}

			contact = contact->GetNext();
		}
		return (grounded && !blocked);
	}

	void PlayerEntity::Update(float timeStep)
	{
		sf::Vector2f moveDirection;
		moveDirection.x = sf::Keyboard::isKeyPressed(sf::Keyboard::D)-sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		moveDirection.y = sf::Keyboard::isKeyPressed(sf::Keyboard::W);//-sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		//moveDirection *= 1.0f;

		if(fabsf(moveDirection.x) > 0.0f)
		{
			_boxFixture->SetFriction(0.0f);

			sf::Vector2f scale = _object->getScale();
			if(scale.x*moveDirection.x > 0.0f)
			{
				_object->setScale(-scale.x, scale.y);
			}
		}
		else
		{
			_boxFixture->SetFriction(5.0f);
		}

		bool isGrounded = IsGrounded();
		if(moveDirection.y > 0.0f && isGrounded)
		{
			_body->ApplyLinearImpulse(b2Vec2(0.0f, -3.0f), b2Vec2(_body->GetPosition().x, _body->GetPosition().y), true);
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

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		{
			if(_throwTimer > 1)
			{
				Throw();
			}
			_throwTimer = 0;
		}
		else
		{
			_throwTimer += 1;
		}
	}

	void PlayerEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
			window->draw(*_object);
	}


	void PlayerEntity::Throw()
	{
		MaskEntity *mask = new MaskEntity(_object->getPosition());
		b2Vec2 direction = _body->GetLinearVelocity();
		sf::Vector2f sfDirection(direction.x, direction.y);
		mask->Throw(sfDirection*0.2f);
	}
}