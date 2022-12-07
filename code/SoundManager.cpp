#include "SoundManager.h"

SoundManager::SoundManager()
{
	laserBulletSFXBuffer.loadFromFile("sound/laser_bullet.wav");
	laserBulletSFX.setBuffer(laserBulletSFXBuffer);
}

void SoundManager::PlayLaserBulletSFX()
{
	laserBulletSFX.play();
}