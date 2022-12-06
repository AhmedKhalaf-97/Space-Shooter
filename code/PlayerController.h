#pragma once

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Controller.h"

class PlayerController : public Controller
{
public:
	PlayerController();
	PlayerController(Vector2f initialPosition);
	void Create(Vector2f initialPosition);
	void Move() override;
	void CheckIfShouldFire(Time dt) override;
	void CheckIfShouldChangeWeapon();
	void AssignWeapons() override;
	void UpdateWeapons(Time dt, Vector2f newPos) override;
	vector<Sprite> GetProjectileSprites() override;
	vector<Projectile*> GetProjectiles() override;
	void UpdateController(Time dt, Vector2f screenResolution);
private:
	ProjectileType selectedProjectileType = ProjectileType::Bullet_Type;
	Vector2f screenResolution;
};

#endif