//
// Created by gclmini-06 on 07.11.2015.
//

#include "SoundPool.h"
#include <random>
namespace FGL
{

	SoundPool *SoundPool::_instance = 0;

	SoundPool::SoundPool()
	{
		LoadSound("assets/sounds/splat_1.ogg");
		LoadSound("assets/sounds/splat_2.ogg");
		LoadSound("assets/sounds/splat_4.ogg");

		LoadSound("assets/sounds/stab_1.ogg");
		LoadSound("assets/sounds/stab_2.ogg");
		LoadSound("assets/sounds/stab_3.ogg");
	}


	void SoundPool::LoadSound(std::string sound)
	{
		sf::SoundBuffer* buf = new sf::SoundBuffer();
		buf->loadFromFile(World::GetInstance()->GetBundlePath()+sound);
		soundMap.insert(std::pair<std::string,sf::SoundBuffer*>(sound,buf));
	}
	sf::SoundBuffer *SoundPool::GetSound(std::string sound)
	{
		if(soundMap.find(sound)==soundMap.end()){
			LoadSound(sound);
		}
		return soundMap.at(sound);
	}

	SoundPool *SoundPool::GetInstance()
	{
		if(!_instance)
			_instance = new SoundPool();

		return _instance;
	}

	sf::SoundBuffer *SoundPool::PlaySplat()
	{
		sf::SoundBuffer *buf;
		int rnd = rand() % 3;
		switch(rnd){
			case 0:
				buf=GetSound("assets/sounds/splat_1.ogg");
				break;
			case 1:
				buf=GetSound("assets/sounds/splat_2.ogg");
				break;
			case 2:
				buf=GetSound("assets/sounds/splat_4.ogg");
				break;
		}
		return buf;

	}
	sf::SoundBuffer *SoundPool::PlayStab()
	{
		sf::SoundBuffer *buf;
		int rnd = rand() % 3;
		switch(rnd){
			case 0:
				buf=GetSound("assets/sounds/stab_1.ogg");
				break;
			case 1:
				buf=GetSound("assets/sounds/stab_2.ogg");
				break;
			case 2:
				buf=GetSound("assets/sounds/stab_3.ogg");
				break;
		}
		return buf;
	}

	void SoundPool::PlayStabFail()
	{

	}
	SoundPool::~SoundPool()
	{
		soundMap.clear();
	}

}