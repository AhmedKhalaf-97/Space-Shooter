#include "Bullet.h"

Bullet::Bullet(Vector2f initialPos): Projectile(initialPos)
{
}

void Bullet::ConfigureProjectile()
{
	texture.loadFromFile("graphics/bullet.png");
	sprite.setTexture(texture);

	SetSpeed(2000);
	SetDirection(Vector2f(0, -1));
	SetRotation(-90);
	SetScale(Vector2f(0.5, 0.5));

	SetDamageAmount(5);
}