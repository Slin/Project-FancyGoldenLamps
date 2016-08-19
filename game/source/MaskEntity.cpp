//
// Created by Nils Daumann on 18.08.16.
//

#include "MaskEntity.h"
#include "PlayerEntity.h"
#include "MaskSpawner.h"
#include "ExplosionEntity.h"
#include <iostream>

namespace FGL
{
	MaskEntity::MaskEntity(sf::Vector2f position) : _explosionTimer(3.0f), _atSpawn(true), _carryingPlayer(nullptr), _wasThrown(false), _isGood(false), _needsCollection(false), _glowAnimationTimer(0.0f), _body(
			nullptr)
	{
		_object = World::CreateSprite("assets/textures/mask.png");
		_object->setTextureRect(sf::IntRect(0, 0, 38, 54));
		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->setPosition(position);

		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;

		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(_object->getPosition().x*WORLD_TO_BOX2D, _object->getPosition().y*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(30.0f*0.5f*WORLD_TO_BOX2D, 38.0f*0.5f*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 0.4f;
		fixtureDef.friction = 3.0f;
		fixtureDef.restitution = 0.5f;
		fixtureDef.filter.categoryBits = 0x0002;
		fixtureDef.filter.maskBits = 0x0001|0x0002|0x0004|0x0008;
		_bodyFixture = _body->CreateFixture(&fixtureDef);
	}

	MaskEntity::~MaskEntity()
	{
		World::GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
		_body = nullptr;
		if(_carryingPlayer)
		{
			_carryingPlayer->_currentMask = nullptr;
		}
	}

	void MaskEntity::CheckCollisions()
	{
		b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
		while(contact)
		{
			if(contact->IsTouching() && (contact->GetFixtureA() == _bodyFixture || contact->GetFixtureB() == _bodyFixture))
			{
				b2Fixture *otherFixture = ((contact->GetFixtureA() == _bodyFixture)?contact->GetFixtureB():contact->GetFixtureA());
				if(otherFixture->GetUserData() && (otherFixture->GetFilterData().categoryBits & (0x0004|0x0008)))
				{
					if((_atSpawn && !((PlayerEntity*)otherFixture->GetUserData())->_currentMask) || _isGood)
					{
						_wasThrown = false;
						_atSpawn = false;
						_carryingPlayer = (PlayerEntity*)otherFixture->GetUserData();
						_carryingPlayer->_currentMask = this;

						b2Filter filter = _bodyFixture->GetFilterData();
						filter.maskBits = 0x0001|0x0002|((_carryingPlayer->_playerID==0)?0x0008:0x0004);

						if(_isGood)
						{
							filter.maskBits |= 0x0010;
							_glowAnimationTimer = 6.0f;
						}

						_bodyFixture->SetFilterData(filter);
					}
					else
					{
						_atSpawn = false;
						PlayerEntity *player = (PlayerEntity*)otherFixture->GetUserData();
						player->Kill();
						_explosionTimer = 0.0f;
					}
				}
				else
				{
					if(otherFixture->GetFilterData().categoryBits == 0x0002)
					{
						_atSpawn = false;
					}
				}
			}

			contact = contact->GetNext();
		}
	}

	void MaskEntity::Update(float timeStep)
	{
		CheckCollisions();

		if(_carryingPlayer && !_wasThrown)
		{
			b2Vec2 position = _carryingPlayer->_body->GetPosition();
			_body->SetTransform(b2Vec2(position.x, position.y-35.0f*WORLD_TO_BOX2D), 0.0f);
		}

		if(_wasThrown && _carryingPlayer)
		{
			sf::Vector2f difference = _object->getPosition()-_carryingPlayer->_object->getPosition();
			if(difference.x*difference.x+difference.y*difference.y > 10000)
			{
				_wasThrown = false;
				_carryingPlayer = nullptr;

				b2Filter filter = _bodyFixture->GetFilterData();
				filter.maskBits = 0x0001|0x0002|0x0008|0x0004;
				_bodyFixture->SetFilterData(filter);
			}
		}

		if(!_atSpawn && !_isGood)
		{
			_explosionTimer -= timeStep;
		}

		if(!_atSpawn)
		{
			_glowAnimationTimer += timeStep*10.0f;
			if(!_isGood)
			{
				if(_glowAnimationTimer > 5.5f)
					_glowAnimationTimer = 5.5f;
			}
			else
			{
				if(_glowAnimationTimer > 10.5f)
					_glowAnimationTimer = 10.5f;
			}

			_object->setTextureRect(sf::IntRect(38*(int)_glowAnimationTimer, 0, 38, 54));
		}

		if(_object && _body)
		{
			_object->setPosition(_body->GetPosition().x/WORLD_TO_BOX2D, _body->GetPosition().y/WORLD_TO_BOX2D);
			_object->setRotation(_body->GetAngle()*180.0f/3.14f);
		}

		if(_explosionTimer < 0.0f)
		{
			Explode();
		}

		if(_needsCollection)
		{
			if(_carryingPlayer)
			{
				_carryingPlayer->_currentMask = nullptr;
			}
			World::GetInstance()->GetMaskSpawner()->RemoveMask(this);
			delete this;
		}
	}

	void MaskEntity::Draw(sf::RenderWindow *window)
	{
		if(_object)
		{
			window->draw(*_object);
		}
	}

	void MaskEntity::MakeGood()
	{
		_isGood = true;
		_bodyFixture->SetUserData(this);

		b2Filter filter = _bodyFixture->GetFilterData();
		filter.maskBits = 0x0001|0x0002|0x0004|0x0008|0x0010;
		_bodyFixture->SetFilterData(filter);
	}

	void MaskEntity::Throw(sf::Vector2f direction)
	{
		_wasThrown = true;
		_body->ApplyLinearImpulse(b2Vec2(direction.x, direction.y), _body->GetPosition(), true);
	}

	void MaskEntity::Explode()
	{
		new ExplosionEntity(_object->getPosition());

		if(_carryingPlayer)
		{
			_carryingPlayer->_currentMask = nullptr;
			_carryingPlayer->Kill();
		}
		World::GetInstance()->GetMaskSpawner()->RemoveMask(this);
		World::GetInstance()->Shake();
		delete this;
	}

	void MaskEntity::Collect()
	{
		_needsCollection = true;
	}
}
