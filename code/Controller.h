#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"

using namespace sf;

class Controller
{
public:
	Controller();
	Controller(Vector2f initialPosition);
	Sprite GetSprite();
	virtual void Create(Vector2f initialPosition);
	virtual void Move() = 0;
	virtual void AssignWeapons() = 0;
	virtual void UpdateWeapons(Time dt, Vector2f newPos) = 0;
	virtual void CheckIfShouldFire(Time dt) = 0;
	virtual vector<Sprite> GetProjectileSprites() = 0;
	virtual vector<Projectile*> GetProjectiles() = 0;
	virtual string GetType() = 0;
	void SetMovingSpeed(int speed);
	void SetMovingDirection(Vector2f dir);
	void SetPosition(Vector2f newPosition);
	Vector2f GetMovingDirection();
	Vector2f GetPosition();
	int GetHealthAmount();
	void SetHealthAmount(int healthAmount);
	void TakeDamage(int damageAmount);
	virtual void UpdateController(Time dt, Vector2f screenResolution);
	FloatRect GetFloatRect();
	bool IsAlive();
	void SetIsAlive(bool condition);
	void PlayHitVFX(Time dt);
	bool ShouldDestroy();
	Vector2f GetExplosionPosition();

private:
	Vector2f position;
	Vector2f movingDirection;

	bool alive = true;
	bool shouldDestroy = false;

protected:
	Texture myTexture;
	Sprite mySprite;

	Weapon weaponsAssigned[2]; // 2 weapons, one for the bullets and one for the missiles.

	float movingSpeed;
	int healthAmount;

	bool shouldPlayHitVFX = false;
	float flashRate = 0.1;
	float nextTimeToFlash = 0;
	float elapsedTime = 0;
};

#endif