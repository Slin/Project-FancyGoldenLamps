//
// Created by Nils Daumann on 19.08.16.
//

#include "EndMenu.h"

namespace FGL
{
	EndMenu::EndMenu(int winner) : _animationTimer(0.0f)
	{
		_backgroundImage.setTexture(*TexturePool::GetInstance()->GetTexture(winner==0?"assets/textures/win_left.png":"assets/textures/win_right.png"));
		_backgroundImage.setOrigin(_backgroundImage.getLocalBounds().width*0.5f, _backgroundImage.getLocalBounds().height*0.5f);

		_backgroundLight.setTexture(*TexturePool::GetInstance()->GetTexture("assets/textures/win_light.png"));
		_backgroundLight.setOrigin(_backgroundLight.getLocalBounds().width*0.5f, _backgroundLight.getLocalBounds().height*0.5f);

		_playerImage.setTexture(*TexturePool::GetInstance()->GetTexture(winner==0?"assets/textures/player.png":"assets/textures/player2.png"));
		_playerImage.setTextureRect(sf::IntRect(0, 0, 92, 124));
		_playerImage.setOrigin(_playerImage.getLocalBounds().width*0.5f, _playerImage.getLocalBounds().height*0.5f);
		_playerImage.setPosition(0.0f, 400);

		_music.openFromFile(World::GetInstance()->GetBundlePath()+"assets/sounds/menu.ogg");
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

		_backgroundLight.setColor(sf::Color(255, 255, 255, 255*(sin(deltaTime.asSeconds()*10.0f)*0.5f+0.5f)));

		_animationTimer += timeStep*10.0f;
		if(_animationTimer >= 8.0f)
			_animationTimer -= 8.0f;
		_playerImage.setTextureRect(sf::IntRect(((int)_animationTimer)*92, 0, 92, 124));

		for(int i = 0; i < sf::Keyboard::F1; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i) && i != sf::Keyboard::LSystem)
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

		sf::RenderStates renderStates = sf::RenderStates::Default;
		renderStates.blendMode = sf::BlendAdd;
		renderWindow->draw(_backgroundLight, renderStates);

		renderWindow->draw(_playerImage);
	}
}
