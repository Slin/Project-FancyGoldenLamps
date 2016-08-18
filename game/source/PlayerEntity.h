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
		PlayerEntity(int id);
		~PlayerEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		bool IsGrounded();

		void Throw();

	private:
		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_boxFixture;

		int _playerID;

		int _throwTimer;
	};
}

#endif //FANCYGOLDENLAMPS_PLAYERENTITY_H
