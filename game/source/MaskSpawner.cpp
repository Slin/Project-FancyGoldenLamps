//
// Created by Nils Daumann on 18.08.16.
//

#include "MaskSpawner.h"

namespace FGL
{
	MaskSpawner::MaskSpawner()
	{
		_spawnPositions[0] = sf::Vector2f(0.0f, 0.0f);
		_spawnPositions[1] = sf::Vector2f(0.0f, 550.0f);
		_spawnPositions[2] = sf::Vector2f(500.0f, -450.0f);
		_spawnPositions[3] = sf::Vector2f(-500.0f, -450.0f);

		for(int i = 0; i < 4; i++)
		{
			_masks[i] = new MaskEntity(_spawnPositions[i]);
		}

		_goodMaskIndex = (int)(((float)rand()/(float)INT_MAX)*4.0f);
		_masks[_goodMaskIndex]->MakeGood();
	}

	MaskSpawner::~MaskSpawner()
	{

	}

	void MaskSpawner::RemoveMask(MaskEntity *mask)
	{
		for(int i = 0; i < 4; i++)
		{
			if(_masks[i] == mask)
			{
				_masks[i] = new MaskEntity(_spawnPositions[i]);

				if(i == _goodMaskIndex)
				{
					_goodMaskIndex = (int)(((float)rand()/(float)INT_MAX)*4.0f);
					while(!_masks[_goodMaskIndex]->IsAtSpawn())
					{
						_goodMaskIndex += 1;
						if(_goodMaskIndex > 3)
							_goodMaskIndex = 0;
					}

					_masks[_goodMaskIndex]->MakeGood();
				}
				return;
			}
		}
	}
}
