//
// Created by Nils Daumann on 18.08.16.
//

#include "StartMenu.h"

namespace FGL
{
	StartMenu::StartMenu() : _canTrigger(false)
	{
		_backgroundImage.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/menu.png"));
		_backgroundImage.setOrigin(_backgroundImage.getLocalBounds().width*0.5f, _backgroundImage.getLocalBounds().height*0.5f);

		_lightDoor.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/menu_door.png"));
		_lightDoor.setOrigin(_lightDoor.getLocalBounds().width*0.5f, _lightDoor.getLocalBounds().height*0.5f);

		_lightSign.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/menu_sign.png"));
		_lightSign.setOrigin(_lightSign.getLocalBounds().width*0.5f, _lightSign.getLocalBounds().height*0.5f);

		_lightEnter.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/menu_enter.png"));
		_lightEnter.setOrigin(_lightEnter.getLocalBounds().width*0.5f, _lightEnter.getLocalBounds().height*0.5f);

		_music.openFromFile(World::GetInstance()->GetBundlePath()+"assets/sounds/menu.ogg");
		_music.play();
		_music.setPlayingOffset(World::GetInstance()->GetMusicPosition());
		_music.setLoop(true);
	}

	StartMenu::~StartMenu()
	{

	}

	void StartMenu::Update(float timeStep)
	{
		timer += timeStep;
		if(rand()%100 < 1)
		{
			_lightDoor.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			_lightDoor.setColor(sf::Color(255, 255, 255, 0));
		}

		if(rand()%100 < 5)
		{
			_lightSign.setColor(sf::Color(255, 255, 255, 255));
		}
		else
		{
			_lightSign.setColor(sf::Color(255, 255, 255, 0));
		}

		_lightEnter.setColor(sf::Color(255, 255, 255, 255*(sin(timer*10.0f)*0.5f+0.5f)));

		for(int i = 0; i < sf::Keyboard::F1; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i) && i != sf::Keyboard::LSystem)
			{
				if(_canTrigger)
				{
					World::GetInstance()->SetMusicPosition(_music.getPlayingOffset());
					World::GetInstance()->ShouldLoadLevel();
				}
				return;
			}
		}

		_canTrigger = true;
	}

	void StartMenu::Draw(sf::RenderWindow *window)
	{
		window->draw(_backgroundImage);

		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;
		window->draw(_lightDoor, renderStates);
		window->draw(_lightSign, renderStates);
		window->draw(_lightEnter, renderStates);
	}
}
