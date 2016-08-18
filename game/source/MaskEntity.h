//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_MASKENTITY_H
#define FANCYGOLDENLAMPS_MASKENTITY_H

#include "World.h"

namespace FGL
{
	class MaskEntity : public Entity
	{
	public:
		MaskEntity(sf::Vector2f position);
		~MaskEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		void Throw(int id, sf::Vector2f direction);
		void Explode();

	private:
		void CheckCollisions();

		sf::Sprite *_object;
		b2Body *_body;
		b2Fixture *_bodyFixture;

		float _explosionTimer;
	};
}

#endif //FANCYGOLDENLAMPS_MASKENTITY_H
