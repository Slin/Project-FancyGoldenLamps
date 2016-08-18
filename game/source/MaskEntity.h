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

		void Throw(sf::Vector2f direction);

	private:
		sf::Sprite *_object;
		b2Body *_body;
	};
}

#endif //FANCYGOLDENLAMPS_MASKENTITY_H
