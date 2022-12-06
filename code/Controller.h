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
	void SetMovingSpeed(int speed);
	void SetMovingDirection(Vector2f dir);
	void SetPosition(Vector2f newPosition);
	Vector2f GetMovingDirection();
	Vector2f GetPosition();
	void SetHealthAmount(int healthAmount);
	void TakeDamage(int damageAmount);
	virtual void UpdateController(Time dt, Vector2f screenResolution);

private:
	Vector2f position;
	Vector2f movingDirection;

protected:
	Texture myTexture;
	Sprite mySprite;

	Weapon weaponsAssigned[2]; // 2 weapons, one for the bullets and one for the missiles.

	float movingSpeed;
	int healthAmount;
};

#endif