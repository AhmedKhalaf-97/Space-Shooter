#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Controller
{
public:
	Controller();
	Controller(Vector2f initialPosition);
	Sprite GetSprite();
	virtual void Move() = 0;
	void Create(Vector2f initialPosition);
	void SetMovingSpeed(int speed);
	void SetMovingDirection(Vector2f dir);
	Vector2f GetMovingDirection();
	void SetHealthAmount(int healthAmount);
	void TakeDamage(int damageAmount);
	void AssignWeapon();
	void MoveWeaponAlongWithController();
	void UpdatePosition(Time dt, Vector2f screenResolution);
private:
	Texture myTexture;
	Sprite mySprite;
	Vector2f position;
	Vector2f movingDirection;
	float movingSpeed;
	int healthAmount;
	// Weapon weaponAssigned; 
};

#endif // !CONTROLLER_H
