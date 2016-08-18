//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_INGAMEUI_H
#define FANCYGOLDENLAMPS_INGAMEUI_H

#include "World.h"

namespace FGL
{
	class IngameUI : public Entity
	{
	public:
		IngameUI();
		~IngameUI();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

		void AddPoint(int player);

	private:
		sf::Font _font;
		sf::Text _scoreLeft;
		sf::Text _scoreRight;

		int _pointsLeft;
		int _pointsRight;
	};
}

#endif //FANCYGOLDENLAMPS_INGAMEUI_H
