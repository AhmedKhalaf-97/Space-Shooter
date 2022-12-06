#include "Controller.h"

Controller::Controller()
{
	Create(Vector2f(0,0));
}

Controller::Controller(Vector2f initialPosition)
{
	Create(initialPosition);
}

Sprite Controller::GetSprite()
{
	return mySprite;
}

void Controller::SetHealthAmount(int healthAmount)
{
	this->healthAmount = healthAmount;
}

void Controller::Create(Vector2f initialPosition)
{
	position = initialPosition;

	FloatRect objectRect = mySprite.getLocalBounds();
	mySprite.setOrigin(objectRect.left +
		objectRect.width / 2.0f,
		objectRect.top +
		objectRect.height / 2.0f);
	mySprite.setPosition(initialPosition);
}

void Controller::SetMovingSpeed(int speed)
{
	this->movingSpeed = speed;
}

void Controller::SetMovingDirection(Vector2f dir)
{
	this->movingDirection = dir;
}

void Controller::SetPosition(Vector2f newPosition)
{
	position = newPosition;
	mySprite.setPosition(position);
}

Vector2f Controller::GetMovingDirection()
{
	return movingDirection;
}

Vector2f Controller::GetPosition()
{
	return position;
}

int Controller::GetHealthAmount()
{
	return healthAmount;
}

void Controller::TakeDamage(int damageAmount)
{
	if (healthAmount > 0)
	{
		healthAmount -= damageAmount;

		shouldPlayHitVFX = true;
	}

	if (healthAmount <= 0)
	{
		healthAmount = 0;
		SetIsAlive(false);
		shouldDestroy = true;
	}
}

void Controller::UpdateController(Time dt, Vector2f screenResolution)
{
	int screenEdgeSize = 100;

	position.x += movingDirection.x * movingSpeed * dt.asSeconds();
	position.y += movingDirection.y * movingSpeed * dt.asSeconds();

	if (position.x > screenResolution.x - screenEdgeSize)
	{
		position.x = screenResolution.x - screenEdgeSize;
	}
	if (position.x < screenEdgeSize)
	{
		position.x = screenEdgeSize;
	}
	if (position.y > screenResolution.y - screenEdgeSize)
	{
		position.y = screenResolution.y - screenEdgeSize;
	}
	if (position.y < screenResolution.y * 0.30)
	{
		position.y = screenResolution.y * 0.30;
	}

	mySprite.setPosition(position);
}

FloatRect Controller::GetFloatRect()
{
	return mySprite.getGlobalBounds();
}

bool Controller::IsAlive()
{
	return alive;
}

void Controller::SetIsAlive(bool condition)
{
	alive = condition;
}

void Controller::PlayHitVFX(Time dt)
{
	if (shouldPlayHitVFX)
	{
		mySprite.setColor(Color::Red);

		elapsedTime += dt.asSeconds();
		if (elapsedTime >= nextTimeToFlash)
		{
			nextTimeToFlash = flashRate + elapsedTime;

			mySprite.setColor(Color::White);

			shouldPlayHitVFX = false;
		}
	}
}

bool Controller::ShouldDestroy()
{
	return shouldDestroy;
}

Vector2f Controller::GetExplosionPosition()
{
	shouldDestroy = false; //reset it
	return position;
}
