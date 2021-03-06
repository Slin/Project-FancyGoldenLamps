//
// Created by Nils Daumann on 17.08.16.
//

#ifndef FANCYGOLDENLAMPS_WORLD_H
#define FANCYGOLDENLAMPS_WORLD_H


#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <Box2D/Box2D.h>

#include "EntityManager.h"
#include "Entity.h"
#include "TexturePool.h"
#include "SoundPool.h"

#define WORLD_TO_BOX2D 0.005f

namespace FGL
{
	class BoardEntity;
	class MaskSpawner;
	class IngameUI;
	class BlackFadeEntity;
	class World
	{
	public:
		void Loop();
		void Update(float timeStep);

		sf::RenderWindow *GetWindow() const
		{
			return _window;
		}

		const std::string &GetBundlePath() const
		{
			return _bundlePath;
		}

		b2World *GetPhysicsWorld() const
		{
			return _physicsWorld;
		}

		MaskSpawner *GetMaskSpawner() const
		{
			return _maskSpawner;
		}

		IngameUI *GetIngameUI() const
		{
			return _ingameUI;
		}

		static World *GetInstance();

		void ShouldLoadLevel();
		void ShouldLoadMenu();
		void ShouldLoadEnd(int winner);

		void SetMusicPosition(sf::Time position)
		{
			_musicPosition = position;
		}

		const sf::Time GetMusicPosition() const
		{
			return _musicPosition;
		}

		static sf::Sprite *CreateSprite(const std::string &file)
		{
			sf::Sprite *object = new sf::Sprite();
			object->setTexture(*TexturePool::GetInstance()->GetTexture(file));

			object->setOrigin(object->getLocalBounds().width*0.5f, object->getLocalBounds().height*0.5f);

			return object;
		}

		static b2Body *CreateStaticBoxCollider(sf::Vector2f position, sf::Vector2u size, float rotation = 0.0f)
		{
			b2BodyDef groundBodyDef;
			groundBodyDef.position.Set(position.x*WORLD_TO_BOX2D, position.y*WORLD_TO_BOX2D);
			groundBodyDef.angle = rotation/180.0f*3.14f;
			b2Body *body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&groundBodyDef);

			b2PolygonShape box;
			box.SetAsBox(size.x*WORLD_TO_BOX2D*0.5f, size.y*WORLD_TO_BOX2D*0.5f);
			body->CreateFixture(&box, 0.0f);

			return body;
		}

		void Shake();

	private:
		World();

		void Reset();
		void LoadLevel();
		void LoadMenu();
		void LoadControls();
		void LoadEnd(int winner);

		static World *_instance;

		sf::RenderWindow *_window;
		sf::View *_view;
		float _scaleFactor;
		std::string _bundlePath;

		b2World *_physicsWorld;
		MaskSpawner *_maskSpawner;
		IngameUI *_ingameUI;
		sf::Time _musicPosition;

		BlackFadeEntity *_blackFade;

		bool _shouldLoadLevel;
		bool _shouldLoadMenu;
		int _shouldLoadEnd;

		float _screenShakeTimer;
	};
}


#endif //FANCYGOLDENLAMPS_WORLD_H
