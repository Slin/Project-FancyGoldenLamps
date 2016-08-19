//
// Created by Nils Daumann on 19.08.16.
//

#include "ControlMenu.h"

namespace FGL
{
	ControlMenu::ControlMenu()
	{
		_backgroundImage.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/controls.png"));
		_backgroundImage.setOrigin(_backgroundImage.getLocalBounds().width*0.5f, _backgroundImage.getLocalBounds().height*0.5f);

		_backgroundLight.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/controls_light.png"));
		_backgroundLight.setOrigin(_backgroundLight.getLocalBounds().width*0.5f, _backgroundLight.getLocalBounds().height*0.5f);
	}

	ControlMenu::~ControlMenu()
	{

	}

	void ControlMenu::Update(float timeStep)
	{
		sf::Time deltaTime = _clock.getElapsedTime();

		if(rand()%100 < 5)
		{
			_backgroundLight.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			_backgroundLight.setColor(sf::Color(255, 255, 255, 0));
		}

		for(int i = 0; i < sf::Keyboard::F1; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i) && i != sf::Keyboard::LSystem)
			{
				if(_canTrigger && deltaTime.asSeconds() > 1.0f)
				{
					World::GetInstance()->ShouldLoadMenu();
				}
				return;
			}
		}

		_canTrigger = true;
	}

	void ControlMenu::Draw(sf::RenderWindow *window)
	{
		window->draw(_backgroundImage);

		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;
		window->draw(_backgroundLight, renderStates);
	}
}
