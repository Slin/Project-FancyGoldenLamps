//
// Created by Nils Daumann on 19.08.16.
//

#ifndef FANCYGOLDENLAMPS_BLACKFADEENTITY_H
#define FANCYGOLDENLAMPS_BLACKFADEENTITY_H

#include "World.h"

namespace FGL
{
	class BlackFadeEntity
	{
	public:
		BlackFadeEntity();
		~BlackFadeEntity();

		void Update(float timeStep);
		void DrawLate(sf::RenderWindow *window);

		void SetTargetAlpha(float target, float speed);
		float GetCurrentAlpha(){return _currentAlpha;}

	private:
		sf::RectangleShape _object;
		float _currentAlpha;
		float _targetAlpha;
		float _startAlpha;
		float _speed;
		float _timer;
	};
}

#endif //FANCYGOLDENLAMPS_BLACKFADEENTITY_H
