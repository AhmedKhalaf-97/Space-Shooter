#include "PlayerController.h"

PlayerController::PlayerController(): Controller()
{
	AssignWeapons();
}

PlayerController::PlayerController(Vector2f initialPosition): Controller(initialPosition)
{
	AssignWeapons();
}

void PlayerController::Create(Vector2f initialPosition)
{
	healthAmount = 1000;
	movingSpeed = 1000.0f;

	myTexture.loadFromFile("graphics/destroyer.png");
	mySprite.setTexture(myTexture);
	mySprite.setScale(0.35, 0.35);
	mySprite.setRotation(-90);

	Controller::Create(initialPosition);
}

void PlayerController::Move()
{
	Vector2f dir(0, 0);

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		dir.y = -1.0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		dir.y = 1.0;
	}
	 

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		dir.x = 1.0;
	} 
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		dir.x = -1.0;
	}

	SetMovingDirection(dir);
}

void PlayerController::CheckIfShouldFire(Time dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		weaponsAssigned[selectedProjectileType].Fire(dt);
	}
}

void PlayerController::CheckIfShouldChangeWeapon()
{
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		selectedProjectileType = ProjectileType::Bullet_Type;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		selectedProjectileType = ProjectileType::Missile_Type;
	}
}

void PlayerController::AssignWeapons()
{
	weaponsAssigned[0] = Weapon(ProjectileType::Bullet_Type);
	weaponsAssigned[1] = Weapon(ProjectileType::Missile_Type);
}

void PlayerController::UpdateWeapons(Time dt, Vector2f newPos)
{
	weaponsAssigned[0].Update(dt, newPos, screenResolution);
	weaponsAssigned[1].Update(dt, newPos, screenResolution);
}

vector<Sprite> PlayerController::GetProjectileSprites()
{
	vector<Sprite> allProjectileSprites = weaponsAssigned[0].GetActiveProjectileSprites();
	vector<Sprite> projectileSprites_Weapon2 = weaponsAssigned[1].GetActiveProjectileSprites();

	allProjectileSprites.insert(allProjectileSprites.end(),
		projectileSprites_Weapon2.begin(),
		projectileSprites_Weapon2.end());

	return allProjectileSprites;
}

vector<Projectile*> PlayerController::GetProjectiles()
{
	vector<Projectile*> allProjectiles = weaponsAssigned[0].GetActiveProjectiles();
	vector<Projectile*> projectiles_Weapon2 = weaponsAssigned[1].GetActiveProjectiles();


	allProjectiles.insert(allProjectiles.end(),
		projectiles_Weapon2.begin(),
		projectiles_Weapon2.end());

	return allProjectiles;
}

void PlayerController::UpdateController(Time dt, Vector2f screenResolution)
{
	if (this->screenResolution.x == 0 || this->screenResolution.y == 0)
	{
		this->screenResolution = screenResolution;
	}

	Controller::UpdateController(dt, screenResolution);

	UpdateWeapons(dt, this->GetPosition());
}
