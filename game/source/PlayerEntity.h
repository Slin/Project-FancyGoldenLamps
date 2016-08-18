//
// Created by Nils Daumann on 17.08.16.
//

#ifndef FANCYGOLDENLAMPS_PLAYERENTITY_H
#define FANCYGOLDENLAMPS_PLAYERENTITY_H

#include "World.h"

namespace FGL
{
	class PlayerEntity : public Entity
	{
	public:
		PlayerEntity(int id, sf::Vector2f position);
		~PlayerEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		bool IsGrounded();

		void Throw();
		void Kill();

	private:
		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_boxFixture;

		int _playerID;
		sf::Vector2f _spawnPosition;

		int _throwTimer;
		int _jumpTimer;
	};
}

#endif //FANCYGOLDENLAMPS_PLAYERENTITY_H
