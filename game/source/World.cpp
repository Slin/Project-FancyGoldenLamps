//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"

#include "BoardEntity.h"
#include "PlayerEntity.h"
#include "MaskSpawner.h"
#include "MaskSink.h"
#include "IngameUI.h"
#include "StartMenu.h"
#include "EndMenu.h"
#include "BlackFadeEntity.h"
#include "ControlMenu.h"

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#define FULLSCREEN

namespace FGL
{
	World *World::_instance = nullptr;

	World *World::GetInstance()
	{
		if(!_instance)
		{
			_instance = new World();
		}

		return _instance;
	}

	World::World() : _physicsWorld(nullptr), _screenShakeTimer(0.0f), _maskSpawner(nullptr), _shouldLoadLevel(false), _shouldLoadMenu(false), _shouldLoadEnd(-1)
	{
#if __APPLE__ && !(TARGET_OS_IPHONE) && NDEBUG
		CFBundleRef bundle = CFBundleGetMainBundle();
		CFURLRef url = CFBundleCopyBundleURL(bundle);

		CFStringRef urlString = CFURLCopyPath(url);

		const char *file = CFStringGetCStringPtr(urlString, kCFStringEncodingUTF8);
		_bundlePath = file;
		_bundlePath += "Contents/Resources/";
#else
		_bundlePath = "";
#endif

#if defined(FULLSCREEN)
		_window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Fancy Golden Lamps", sf::Style::Fullscreen);
#else
		_window = new sf::RenderWindow(sf::VideoMode(1920, 1200), "Fancy Golden Lamps");
#endif
		_window->setFramerateLimit(60);

		_view = new sf::View(sf::FloatRect(-0.5*_window->getSize().x, -0.5*_window->getSize().y, _window->getSize().x, _window->getSize().y));
		_view->zoom(1200.0f/_window->getSize().y);
		_window->setView(*_view);
		_window->clear(sf::Color::Black);
	}

	void World::ShouldLoadLevel()
	{
		_blackFade->SetTargetAlpha(1.0f, 1.0f);
		_shouldLoadLevel = true;
	}

	void World::ShouldLoadMenu()
	{
		_blackFade->SetTargetAlpha(1.0f, 1.0f);
		_shouldLoadMenu = true;
	}

	void World::ShouldLoadEnd(int winner)
	{
		_blackFade->SetTargetAlpha(1.0f, 1.0f);
		_shouldLoadEnd = winner;
	}

	void World::LoadMenu()
	{
		Reset();
		new StartMenu();
		_blackFade->SetTargetAlpha(0.0f, 1.0f);
	}

	void World::LoadEnd(int winner)
	{
		Reset();
		new EndMenu(winner);
		_blackFade->SetTargetAlpha(0.0f, 1.0f);
	}

	void World::LoadLevel()
	{
		Reset();

		new BoardEntity();

		_ingameUI = new IngameUI();

		new MaskSink(0, sf::Vector2f(-525, 525), sf::Vector2f(150, 150));
		new MaskSink(1, sf::Vector2f(525, 525), sf::Vector2f(150, 150));

		new PlayerEntity(0, sf::Vector2f(-562.0f, 537.0f));
		new PlayerEntity(1, sf::Vector2f(562.0f, 537.0f));

		_maskSpawner = new MaskSpawner();

		_blackFade->SetTargetAlpha(0.0f, 1.0f);
	}

	void World::LoadControls()
	{
		Reset();
		new ControlMenu();
		_blackFade->SetTargetAlpha(0.0f, 1.0f);
	}

	void World::Reset()
	{
		if(_maskSpawner)
		{
			delete _maskSpawner;
			_maskSpawner = nullptr;
		}

		EntityManager::GetInstance()->RemoveAllEntities();

		if(_physicsWorld)
			delete _physicsWorld;

		b2Vec2 gravity(0.0f, 9.81f*1.5f);
		_physicsWorld = new b2World(gravity);
	}

	void World::Loop()
	{
		_blackFade = new BlackFadeEntity();
		LoadControls();

		sf::Clock clock;
		sf::Time deltaTime;
		sf::Time time = sf::Time::Zero;

		while(_window->isOpen())
		{
			sf::Event event;
			while(_window->pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
				{
					_window->close();
				}
			}

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_window->close();
				break;
			}

			deltaTime = clock.getElapsedTime();
			time += deltaTime;
			clock.restart();
			int counter = 0;
			while(time.asSeconds() > 1.0f / 60.0f && counter < 10)
			{
				_physicsWorld->Step(1.0f / 60.0f, 10, 5);

				EntityManager::GetInstance()->Update(1.0f / 60.0f);
				Update(1.0f / 60.0f);

				time -= sf::seconds(1.0f / 60.0f);
				counter += 1;
			}

			if(counter >= 10)
				time = sf::Time::Zero;

			//_window->clear(sf::Color(100, 100, 100, 255));
			EntityManager::GetInstance()->Draw(_window);

			_blackFade->DrawLate(_window);

			_window->display();
		}
	}

	void World::Update(float timeStep)
	{
		if(_screenShakeTimer > 0)
		{
			_view->setRotation(((float)rand()*6.0f/(float)INT_MAX)-3.0f);
		}
		else
		{
			_view->setRotation(0.0f);
		}
		_window->setView(*_view);
		_screenShakeTimer -= timeStep;

		if(_blackFade->GetCurrentAlpha() >= 0.99f)
		{
			if(_shouldLoadLevel)
			{
				LoadLevel();
				_shouldLoadLevel = false;
			}

			if(_shouldLoadMenu)
			{
				LoadMenu();
				_shouldLoadMenu = false;
			}

			if(_shouldLoadEnd >= 0)
			{
				LoadEnd(_shouldLoadEnd);
				_shouldLoadEnd = -1;
			}
		}

		_blackFade->Update(timeStep);
	}

	void World::Shake()
	{
		_screenShakeTimer = 0.15f;
	}
}
