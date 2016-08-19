//
// Created by Nils Daumann on 19.08.16.
//

#include "BlackFadeEntity.h"

namespace FGL
{
	BlackFadeEntity::BlackFadeEntity() : _currentAlpha(1.0f), _startAlpha(1.0f), _targetAlpha(0.0f), _speed(3.0f)
	{
		_object.setSize(sf::Vector2f(10000, 10000));
		_object.setOrigin(_object.getSize().x*0.5f, _object.getSize().y*0.5f);
		_object.setFillColor(sf::Color::Black);
	}

	BlackFadeEntity::~BlackFadeEntity()
	{

	}

	void BlackFadeEntity::Update(float timeStep)
	{
		_timer += timeStep*_speed;

		if(_timer > 1.0f)
			_timer = 1.0f;

		_currentAlpha = _startAlpha*(1.0f-_timer)+_targetAlpha*_timer;
		_object.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, _currentAlpha*255));
	}

	void BlackFadeEntity::DrawLate(sf::RenderWindow *window)
	{
		window->draw(_object);
	}

	void BlackFadeEntity::SetTargetAlpha(float target, float speed)
	{
		_startAlpha = _currentAlpha;
		_timer = 0.0f;
		_targetAlpha = target;
//		_speed = speed;
	}
}
