//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_MASKSINK_H
#define FANCYGOLDENLAMPS_MASKSINK_H

#include "World.h"

namespace FGL
{
	class MaskSink : public Entity
	{
	public:
		MaskSink(sf::Vector2f position, sf::Vector2f size);
		~MaskSink();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		b2Body *_body;
		b2Fixture *_bodyFixture;
	};
}

#endif //FANCYGOLDENLAMPS_MASKSINK_H
