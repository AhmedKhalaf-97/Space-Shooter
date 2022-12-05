#include "Weapon.h"

Weapon::Weapon()
{
}

Weapon::Weapon(ProjectileType projectile)
{
	 projectileType = projectile;

	 if (projectileType == ProjectileType::Bullet_Type)
	 {
		 ammoCount = 10;
		 remainingAmmoCount = ammoCount;
		 fireRate = 0.1;

		 for (int i = 0; i < ammoCount; i++)
		 {
			 Bullet* newBullet = new Bullet(position);
			 newBullet->ConfigureProjectile();
			 projectiles.push_back(newBullet);
		 }
	 }

	 if (projectileType == ProjectileType::Missile_Type)
	 {
		 ammoCount = 10;
		 remainingAmmoCount = ammoCount;
		 fireRate = 1;

		 for (int i = 0; i < ammoCount; i++)
		 {
			 Missile* newMissile = new Missile(position);
			 newMissile->ConfigureProjectile();
			 projectiles.push_back(newMissile);
		 }
	 }
}

void Weapon::Fire(Time dt)
{
	Vector2f positionWithOffset = Vector2f(position.x - 35, position.y - 60);

	elapsedTime += dt.asSeconds();
	if (elapsedTime >= nextTimeToFire)
	{
		nextTimeToFire = fireRate + elapsedTime;

		projectiles[remainingAmmoCount-1]->ActivateProjectile();
		projectiles[remainingAmmoCount-1]->SetPosition(positionWithOffset);

		remainingAmmoCount--;

		if (remainingAmmoCount <= 0)
		{
			remainingAmmoCount = ammoCount;
		}
	}
}

void Weapon::Update(Time dt, Vector2f newPosition, Vector2f screenResolution)
{
	position = newPosition;

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->UpdatePositionWhenActive(dt, screenResolution);
	}
}

// Return active projectile sprites to be drawn.
vector<Sprite> Weapon::GetActiveProjectileSprites()
{
	vector<Sprite> activeProjectileSprites;

	for (int i = 0; i < projectiles.size(); i++)
	{
		if (projectiles[i]->IsItActive())
		{
			activeProjectileSprites.push_back(projectiles[i]->GetSprite());
		}
	}

	return activeProjectileSprites;
}
