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
		_object->setTextureRect(sf::IntRect(0, 0, 500, 550));
		_object->setOrigin(_object->getLocalBounds().width*0.5f, _object->getLocalBounds().height*0.5f);
		_object->setPosition(position);

		_sound.setBuffer(*SoundPool::GetInstance()->GetSound("assets/sounds/explosion.ogg"));
		_sound.play();
	}

	ExplosionEntity::~ExplosionEntity()
	{
		delete _object;
	}

	void ExplosionEntity::Update(float timeStep)
	{
		_animationTimer += timeStep*10.0f;
		_object->setTextureRect(sf::IntRect(((int)_animationTimer)*500, 0, 500, 550));

		if(_animationTimer >= 6.0f && _sound.getStatus() != sf::Sound::Playing)
			delete this;
	}

	void ExplosionEntity::Draw(sf::RenderWindow *window)
	{
		window->draw(*_object);
	}
}
