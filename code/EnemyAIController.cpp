#include "EnemyAIController.h"

EnemyAIController::EnemyAIController()
{
	AssignWeapons();

	srand(time(NULL));
}

EnemyAIController::EnemyAIController(Vector2f initialPosition)
{
	AssignWeapons();

	srand(time(NULL));
}

void EnemyAIController::Create(Vector2f initialPosition)
{
	healthAmount = 100;
	movingSpeed = 1000.0f;

	myTexture.loadFromFile("graphics/enemy_destroyer.png");
	mySprite.setTexture(myTexture);
	mySprite.setScale(0.3, 0.3);
	mySprite.setRotation(180);

	Controller::Create(initialPosition);
}

void EnemyAIController::Move()
{
	//should implement more complex movements.

	Vector2f dir(0, 0);

	dir.y = 1.0;

	SetMovingDirection(dir);
}

void EnemyAIController::UpdateSurrondings(PlayerController* player, vector<EnemyAIController*>* aliveEnemies)
{
	this->player = player;
	this->aliveEnemies = aliveEnemies;
}

void EnemyAIController::CheckIfShouldFire(Time dt)
{
	bool shouldFire = false;

	Vector2f myPosition = GetPosition();

	int shootingProbability = rand() % 100 + 1; //generate random number between 1 and 100

	for (int i = 0; i < aliveEnemies->size(); i++)
	{
		Vector2f anotherAliveEnemyPos = aliveEnemies->at(i)->GetPosition();

		if (myPosition.x == anotherAliveEnemyPos.x)
		{
			if (myPosition.y > anotherAliveEnemyPos.y - 5)
			{
				shouldFire = true;
			}
			else
			{
				shouldFire = false;
			}
		}
	}

	if (shouldFire)
	{
		if (shootingProbability >= 60)
		{
			weaponsAssigned[selectedProjectileType].Fire(dt);
		}
	}
}

void EnemyAIController::AssignWeapons()
{
	weaponsAssigned[0] = Weapon(ProjectileType::Bullet_Type);
	weaponsAssigned[0].SetShootingDirection(Vector2f(0, 1));
	weaponsAssigned[0].OverrideProjectilesTexture("graphics/enemy_bullet.png");
	weaponsAssigned[0].SetFireRate(0.5);
}

void EnemyAIController::UpdateWeapons(Time dt, Vector2f newPos)
{
	weaponsAssigned[0].Update(dt, newPos, screenResolution);
}

vector<Sprite> EnemyAIController::GetProjectileSprites()
{
	return weaponsAssigned[0].GetActiveProjectileSprites();
}

void EnemyAIController::UpdateController(Time dt, Vector2f screenResolution)
{
	if (enabled)
	{
		if (this->screenResolution.x == 0 || this->screenResolution.y == 0)
		{
			this->screenResolution = screenResolution;
		}

		Vector2f position = GetPosition();

		position.x += GetMovingDirection().x * movingSpeed * dt.asSeconds();
		position.y += GetMovingDirection().y * movingSpeed * dt.asSeconds();

		SetPosition(position);

		Vector2f offset(10, 200);
		UpdateWeapons(dt, (this->GetPosition() + offset));
	}
}

bool EnemyAIController::IsEnabled()
{
	return enabled;
}

void EnemyAIController::SetIsEnabled(bool condition)
{
	enabled = condition;
}
