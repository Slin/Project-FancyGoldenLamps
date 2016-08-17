//
// Created by Nils Daumann on 17.08.16.
//

#include "World.h"

#include "BoardEntity.h"

#if __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

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

	World::World()
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

		_window = new sf::RenderWindow(sf::VideoMode(1920, 1080)/*::getDesktopMode()*/, "Fancy Golden Lamps");//, sf::Style::Fullscreen);
		_scaleFactor = _window->getSize().y / 1080.0f;
	}

	void World::LoadLevel()
	{
		Reset();

		_boardEntity = new BoardEntity();
	}

	void World::Reset()
	{
		EntityManager::GetInstance()->RemoveAllEntities();
	}

	void World::Loop()
	{
		LoadLevel();

		sf::Clock clock;
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

			sf::Time deltaTime = clock.getElapsedTime();
			clock.restart();
			EntityManager::GetInstance()->Update(deltaTime.asSeconds());

			Update(deltaTime.asSeconds());
			_window->clear(sf::Color::Black);
			EntityManager::GetInstance()->Draw(_window);

			_window->display();
		}
	}

	void World::Update(float timeStep)
	{

	}

	const std::string &World::GetBundlePath() const
	{
		return _bundlePath;
	}
}
