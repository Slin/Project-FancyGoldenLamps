//
// Created by Nils Daumann on 18.08.16.
//

#include "IngameUI.h"

namespace FGL
{
	IngameUI::IngameUI() : _pointsLeft(0), _pointsRight(0)
	{
		_font.loadFromFile("assets/fonts/dangerflight.ttf");

		_scoreLeft.setFont(_font);
		_scoreLeft.setCharacterSize(80);
		_scoreLeft.setFillColor(sf::Color::Black);
		_scoreLeft.setString("0");
		_scoreLeft.setPosition(-350-_scoreLeft.getLocalBounds().width*0.5, 450.0f);

		_scoreRight.setFont(_font);
		_scoreRight.setCharacterSize(80);
		_scoreRight.setFillColor(sf::Color::Black);
		_scoreRight.setString("0");
		_scoreRight.setPosition(350-_scoreRight.getLocalBounds().width*0.5, 450.0f);
	}

	IngameUI::~IngameUI()
	{

	}

	void IngameUI::Update(float timeStep)
	{

	}

	void IngameUI::Draw(sf::RenderWindow *window)
	{
		window->draw(_scoreLeft);
		window->draw(_scoreRight);
	}

	void IngameUI::AddPoint(int player)
	{
		switch(player)
		{
			case 0:
			{
				_pointsLeft += 1;
				_scoreLeft.setString(std::to_string(_pointsLeft));
				_scoreLeft.setPosition(-350 - _scoreLeft.getLocalBounds().width * 0.5, 450.0f);
				break;
			}

			case 1:
			{
				_pointsRight += 1;
				_scoreRight.setString(std::to_string(_pointsRight));
				_scoreRight.setPosition(350 - _scoreRight.getLocalBounds().width * 0.5, 450.0f);
				break;
			}
		}
	}
}
