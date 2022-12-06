#pragma once

#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Projectile.h"
#include "Bullet.h"
#include "Missile.h"

using namespace sf;
using namespace std;

enum ProjectileType { Bullet_Type, Missile_Type };

class Weapon
{
public:
	Weapon();
	Weapon(ProjectileType projectile);
	void SetShootingDirection(Vector2f direction);
	void OverrideProjectilesTexture(string fileName);
	void SetFireRate(float rate);
	void Fire(Time dt);
	void Update(Time dt, Vector2f newPosition, Vector2f screenResolution);
	vector<Sprite> GetActiveProjectileSprites();
	vector<Projectile*> GetActiveProjectiles();
private:
	vector<Projectile*> projectiles;
	ProjectileType projectileType;
	Vector2f position;

	int ammoCount;
	int remainingAmmoCount;

	float fireRate;
	float nextTimeToFire = 0;
	float elapsedTime = 0;

	bool shouldFire = false;
};

#endif