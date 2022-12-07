#pragma once

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
public:
	SoundManager();
	void PlayLaserBulletSFX();
private:
	SoundBuffer laserBulletSFXBuffer;
	Sound laserBulletSFX;
};

#endif