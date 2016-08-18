//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_STARTMENU_H
#define FANCYGOLDENLAMPS_STARTMENU_H

#include "World.h"

namespace FGL
{
	class StartMenu : public Entity
	{
	public:
		StartMenu();
		~StartMenu();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *window);

	private:
		sf::Sprite _backgroundImage;

		bool _canTrigger;
	};
}

#endif //FANCYGOLDENLAMPS_STARTMENU_H
