#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML\Graphics.hpp>

using namespace sf;

class Controller
{
public:
	Controller(Vector2f initialPosition);
	RectangleShape GetShape();
	virtual void Move() = 0;
	void SetMovingSpeed(int speed);
	void SetMovingDirection(Vector2f dir);
	void SetHealthAmount(int healthAmount);
	void TakeDamage(int damageAmount);
	void AssignWeapon();
	void MoveWeaponAlongWithController();
	void UpdatePosition(Time dt, Vector2f screenResolution);
private:
	RectangleShape rectangleShape;
	Vector2f position;
	Vector2f movingDirection;
	float movingSpeed;
	int healthAmount;
	// Weapon weaponAssigned; 
};

#endif // !CONTROLLER_H
