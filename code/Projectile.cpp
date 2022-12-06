#include "Projectile.h"

#include<iostream>
using namespace std;

Projectile::Projectile(Vector2f initialPos)
{
	sprite.setPosition(initialPos);

	position = initialPos;
	direction = Vector2f(0, 0);

	speed = 500;
	damageAmount = 100;
}

void Projectile::SetTexture(std::string fileName)
{
	texture.loadFromFile(fileName);
	sprite.setTexture(texture);
}

void Projectile::SetPosition(Vector2f position)
{
	this->position = position;
}

void Projectile::SetRotation(float angle)
{
	sprite.setRotation(angle);
}

void Projectile::SetScale(Vector2f scale)
{
	sprite.setScale(scale);
}

void Projectile::SetDirection(Vector2f direction)
{
	this->direction = direction;
}

void Projectile::SetSpeed(int speed)
{
	this->speed = speed;
}

void Projectile::SetDamageAmount(int damageAmount)
{
	this->damageAmount = damageAmount;
}

int Projectile::GetDamageAmount()
{
	return damageAmount;
}

void Projectile::ActivateProjectile()
{
	isActive = true;
}

void Projectile::DeactivateProjectile()
{
	isActive = false;
}

bool Projectile::IsItActive()
{
	return isActive;
}

Sprite Projectile::GetSprite()
{
	return sprite;
}

void Projectile::UpdatePositionWhenActive(Time dt, Vector2f screenResolution)
{
	if (isActive)
	{
		position.x += direction.x * speed * dt.asSeconds();
		position.y += direction.y * speed * dt.asSeconds();

		sprite.setPosition(position);

		if (position.x > screenResolution.x
			|| position.x < 0
			|| position.y > screenResolution.y
			|| position.y < 0)
		{
			isActive = false;
		}
	}
}

FloatRect Projectile::GetFloatRect()
{
	return sprite.getGlobalBounds();
}
