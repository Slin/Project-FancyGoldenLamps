//
// Created by Nils Daumann on 19.08.16.
//

#ifndef FANCYGOLDENLAMPS_ENDMENU_H
#define FANCYGOLDENLAMPS_ENDMENU_H

#include "World.h"

namespace FGL
{
	class EndMenu : public Entity
	{
	public:
		EndMenu(int winner);
		~EndMenu();

		void Update(float timeStep);
		void Draw(sf::RenderWindow *renderWindow);

	private:
		sf::Sprite _backgroundImage;
		sf::Sprite _backgroundLight;
		sf::Sprite _playerImage;
		sf::Music _music;
		sf::Clock _clock;

		bool _canTrigger;
		float _animationTimer;
	};
}

#endif //FANCYGOLDENLAMPS_ENDMENU_H
