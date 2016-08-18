//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_MASKENTITY_H
#define FANCYGOLDENLAMPS_MASKENTITY_H

#include "World.h"

namespace FGL
{
	class PlayerEntity;
	class MaskEntity : public Entity
	{
	public:
		MaskEntity(sf::Vector2f position);
		~MaskEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		void MakeGood();

		void Throw(sf::Vector2f direction);
		void Explode();

	private:
		void CheckCollisions();

		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_bodyFixture;

		bool _atSpawn;
		bool _isGood;
		PlayerEntity *_carryingPlayer;
		bool _wasThrown;

		float _explosionTimer;
	};
}

#endif //FANCYGOLDENLAMPS_MASKENTITY_H
