//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_EXPLOSIONENTITY_H
#define FANCYGOLDENLAMPS_EXPLOSIONENTITY_H

#include "World.h"

namespace FGL
{
	class ExplosionEntity : public Entity
	{
	public:
		ExplosionEntity(sf::Vector2f position);
		~ExplosionEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite *_object;
		float _animationTimer;
	};
}

#endif //FANCYGOLDENLAMPS_EXPLOSIONENTITY_H
