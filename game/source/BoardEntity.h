//
// Created by Nils Daumann on 17.08.16.
//

#ifndef FANCYGOLDENLAMPS_BOARDENTITY_H
#define FANCYGOLDENLAMPS_BOARDENTITY_H

#include "World.h"

namespace FGL
{
	class BoardEntity : public Entity
	{
	public:
		BoardEntity();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite *_object;

	};
}

#endif //FANCYGOLDENLAMPS_BOARDENTITY_H
