//
// Created by Nils Daumann on 17.08.16.
//

#ifndef FANCYGOLDENLAMPS_WORLD_H
#define FANCYGOLDENLAMPS_WORLD_H


#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "EntityManager.h"
#include "Entity.h"
#include "TexturePool.h"


namespace FGL
{
	class BoardEntity;
	class World
	{
	public:
		void Loop();
		void Update(float timeStep);

		float GetScaleFactor()
		{
			return _scaleFactor;
		}

		sf::RenderWindow *GetWindow()
		{
			return _window;
		}

		const std::string &GetBundlePath() const;

		static World *GetInstance();

		void LoadLevel();

		void Reset();

	private:
		World();
		static World *_instance;

		sf::RenderWindow *_window;
		float _scaleFactor;
		std::string _bundlePath;

		BoardEntity *_boardEntity;
	};
}


#endif //FANCYGOLDENLAMPS_WORLD_H
