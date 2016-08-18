//
// Created by Nils Daumann on 18.08.16.
//

#include "ExplosionEntity.h"

namespace FGL
{
	ExplosionEntity::ExplosionEntity(sf::Vector2f position) : _animationTimer(0.0f)
	{
		_object = new sf::Sprite();
		_object->setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/explosion.png"));
		_object->setTextureRect(sf::IntRect(0, 0, 118, 118));
		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->setPosition(position);
		_object->setScale(5.0f, 5.0f);
	}

	ExplosionEntity::~ExplosionEntity()
	{
		delete _object;
	}

	void ExplosionEntity::Update(float timeStep)
	{
		_animationTimer += timeStep*1.0f;
		_object->setTextureRect(sf::IntRect(((int)_animationTimer)*118, 0, 118, 118));

		if(_animationTimer >= 6.0f)
			delete this;
	}

	void ExplosionEntity::Draw(sf::RenderWindow *window)
	{
		window->draw(*_object);
	}
}
