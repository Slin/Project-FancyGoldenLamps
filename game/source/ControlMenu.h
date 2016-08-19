//
// Created by Nils Daumann on 19.08.16.
//

#ifndef FANCYGOLDENLAMPS_CONTROLMENU_H
#define FANCYGOLDENLAMPS_CONTROLMENU_H

#include "World.h"

namespace FGL
{
	class ControlMenu : public Entity
	{
	public:
		ControlMenu();
		~ControlMenu();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite _backgroundImage;
		sf::Sprite _backgroundLight;
		bool _canTrigger;
		sf::Clock _clock;
	};
}

#endif //FANCYGOLDENLAMPS_CONTROLMENU_H
