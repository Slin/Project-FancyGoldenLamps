//
// Created by Nils Daumann on 19.08.16.
//

#include "EndMenu.h"

namespace FGL
{
	EndMenu::EndMenu()
	{
		_backgroundImage.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/end_screen.png"));
		_backgroundImage.setOrigin(_backgroundImage.getLocalBounds().width*0.5f, _backgroundImage.getLocalBounds().height*0.5f);

		_music.openFromFile("assets/sounds/menu.ogg");
		_music.play();
		_music.setPlayingOffset(World::GetInstance()->GetMusicPosition());
		_music.setLoop(true);
	}

	EndMenu::~EndMenu()
	{

	}

	void EndMenu::Update(float timeStep)
	{
		sf::Time deltaTime = _clock.getElapsedTime();
		for(int i = 0; i < sf::Keyboard::KeyCount; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
			{
				if(_canTrigger && deltaTime.asSeconds() > 3.0f)
				{
					World::GetInstance()->SetMusicPosition(_music.getPlayingOffset());
					World::GetInstance()->ShouldLoadMenu();
				}
				return;
			}
		}

		_canTrigger = true;
	}

	void EndMenu::Draw(sf::RenderWindow *renderWindow)
	{
		renderWindow->draw(_backgroundImage);
	}
}
