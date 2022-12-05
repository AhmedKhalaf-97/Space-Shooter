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
	virtual void Move() = 0;
	virtual void AssignWeapons() = 0;
	virtual void UpdateWeapons(Time dt, Vector2f newPos) = 0;
	virtual void CheckIfShouldFire(Time dt) = 0;
	virtual vector<Sprite> GetProjectileSprites() = 0;
	void Create(Vector2f initialPosition);
	void SetMovingSpeed(int speed);
	void SetMovingDirection(Vector2f dir);
	Vector2f GetMovingDirection();
	Vector2f GetPosition();
	void SetHealthAmount(int healthAmount);
	void TakeDamage(int damageAmount);
	virtual void UpdateController(Time dt, Vector2f screenResolution);

private:
	Texture myTexture;
	Sprite mySprite;

	Vector2f position;
	Vector2f movingDirection;

	float movingSpeed;
	int healthAmount;

protected:
	Weapon weaponsAssigned[2]; // 2 weapons, one for the bullets and one for the missiles.
};

#endif