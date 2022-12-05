#pragma once

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Projectile
{
public:
	Projectile(Vector2f initialPos);
	virtual void ConfigureProjectile() = 0;
	void SetPosition(Vector2f position);
	void SetRotation(float angle);
	void SetScale(Vector2f scale);
	void SetDirection(Vector2f direction);
	void SetSpeed(int speed);
	void SetDamageAmount(int damageAmount);
	void ActivateProjectile();
	void DeactivateProjectile();
	bool IsItActive();
	Sprite GetSprite();
	void UpdatePositionWhenActive(Time dt, Vector2f screenResolution);

protected:
	Texture texture;
	Sprite sprite;

private:
	bool isActive = false;

	Vector2f position;
	Vector2f direction;

	float speed;
	int damageAmount;
};

#endif