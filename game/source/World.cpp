//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"

#include "BoardEntity.h"
#include "PlayerEntity.h"

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

//#define FULLSCREEN

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

	World::World() : _physicsWorld(nullptr), _screenShakeTimer(0.0f)
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
		_view->zoom(1200/_window->getSize().y);
		_window->setView(*_view);
	}

	void World::LoadLevel()
	{
		Reset();

		new BoardEntity();
		new PlayerEntity(0, sf::Vector2f(0.0f, 0.0f));
		new PlayerEntity(1, sf::Vector2f(0.0f, 0.0f));
	}

	void World::Reset()
	{
		EntityManager::GetInstance()->RemoveAllEntities();

		if(_physicsWorld)
			delete _physicsWorld;

		b2Vec2 gravity(0.0f, 9.81f);
		_physicsWorld = new b2World(gravity);
	}

	void World::Loop()
	{
		LoadLevel();

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
				_physicsWorld->Step(1.0f / 60.0f, 2, 1);

				EntityManager::GetInstance()->Update(1.0f / 60.0f);
				Update(1.0f / 60.0f);

				time -= sf::seconds(1.0f / 60.0f);
				counter += 1;
			}

			if(counter >= 10)
				time = sf::Time::Zero;

			_window->clear(sf::Color::White);
			EntityManager::GetInstance()->Draw(_window);

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
	}

	void World::Shake()
	{
		_screenShakeTimer = 0.13f;
	}
}
