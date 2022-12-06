#include "Missile.h"

Missile::Missile(Vector2f initialPos) : Projectile(initialPos)
{
}

void Missile::ConfigureProjectile()
{
	texture.loadFromFile("graphics/missile.png");
	sprite.setTexture(texture);

	CenterTheOrigin();

	SetSpeed(2000);
	SetDirection(Vector2f(0, -1));
	SetRotation(-90);
	SetScale(Vector2f(0.5, 0.5));

	SetDamageAmount(200);
}