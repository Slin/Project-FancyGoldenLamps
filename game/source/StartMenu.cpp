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

		_music.openFromFile("assets/sounds/menu.ogg");
		_music.play();
		_music.setPlayingOffset(World::GetInstance()->GetMusicPosition());
		_music.setLoop(true);
	}

	StartMenu::~StartMenu()
	{

	}

	void StartMenu::Update(float timeStep)
	{
		for(int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
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
	}
}
