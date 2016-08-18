//
// Created by Nils Daumann on 18.08.16.
//

#ifndef FANCYGOLDENLAMPS_MASKSPAWNER_H
#define FANCYGOLDENLAMPS_MASKSPAWNER_H

#include <SFML/System/Vector2.hpp>
#include "MaskEntity.h"

namespace FGL
{
	class MaskSpawner
	{
	public:
		MaskSpawner();
		~MaskSpawner();

		void RemoveMask(MaskEntity *mask);

	private:
		sf::Vector2f _spawnPositions[4];
		MaskEntity *_masks[4];
		int _goodMaskIndex;
	};
}

#endif //FANCYGOLDENLAMPS_MASKSPAWNER_H
