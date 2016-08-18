//
// Created by Nils Daumann on 18.08.16.
//

#include "MaskSink.h"
#include "MaskEntity.h"
#include "MaskSpawner.h"

namespace FGL
{
	MaskSink::MaskSink(sf::Vector2f position, sf::Vector2f size)
	{
		b2BodyDef bodyDef;
		b2PolygonShape dynamicBox;
		b2FixtureDef fixtureDef;
		bodyDef.position.Set(position.x*WORLD_TO_BOX2D, position.y*WORLD_TO_BOX2D);
		_body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);
		dynamicBox.SetAsBox(size.x*0.5f*WORLD_TO_BOX2D, size.y*0.5f*WORLD_TO_BOX2D);
		fixtureDef.shape = &dynamicBox;
		fixtureDef.filter.categoryBits = 0x0001;
		fixtureDef.filter.maskBits = 0x0002;
		_bodyFixture = _body->CreateFixture(&fixtureDef);
	}

	MaskSink::~MaskSink()
	{
		World::GetInstance()->GetInstance()->GetPhysicsWorld()->DestroyBody(_body);
	}

	void MaskSink::Update(float timeStep)
	{
		b2Contact *contact = World::GetInstance()->GetPhysicsWorld()->GetContactList();
		while(contact)
		{
			if(contact->IsTouching() && (contact->GetFixtureA() == _bodyFixture || contact->GetFixtureB() == _bodyFixture))
			{
				b2Fixture *otherFixture = ((contact->GetFixtureA() == _bodyFixture)?contact->GetFixtureB():contact->GetFixtureA());

				if(otherFixture->GetUserData() && otherFixture->GetFilterData().categoryBits == 0x0002)
				{
					MaskEntity *mask = (MaskEntity*)otherFixture->GetUserData();
					mask->Collect();
				}
			}

			contact = contact->GetNext();
		}
	}

	void MaskSink::Draw(sf::RenderWindow *window)
	{

	}
}
