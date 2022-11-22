#include "Controller.h"

Controller::Controller(Vector2f initialPosition)
{
	position = initialPosition;
	healthAmount = 100;
	movingSpeed = 1000.0f;

	rectangleShape.setSize(Vector2f(70,100));
	FloatRect objectRect = rectangleShape.getLocalBounds();
	rectangleShape.setOrigin(objectRect.left +
		objectRect.width / 2.0f,
		objectRect.top +
		objectRect.height / 2.0f);
	rectangleShape.setPosition(initialPosition);
}

RectangleShape Controller::GetShape()
{
	return rectangleShape;
}

void Controller::SetHealthAmount(int healthAmount)
{
	this->healthAmount = healthAmount;
}

void Controller::SetMovingSpeed(int speed)
{
	this->movingSpeed = speed;
}

void Controller::SetMovingDirection(Vector2f dir)
{
	this->movingDirection = dir;
}

void Controller::TakeDamage(int damageAmount)
{
	if (healthAmount > 0)
	{
		healthAmount -= damageAmount;

		if (healthAmount <= 0)
		{
			healthAmount = 0;
		}
	}
	else
	{
		healthAmount = 0;
	}
}

void Controller::AssignWeapon()
{
}

void Controller::MoveWeaponAlongWithController()
{
}

void Controller::UpdatePosition(Time dt, Vector2f screenResolution)
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
	if (position.y < screenEdgeSize)
	{
		position.y = screenEdgeSize;
	}

	rectangleShape.setPosition(position);
}
