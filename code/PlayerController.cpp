#include "PlayerController.h"

PlayerController::PlayerController(Vector2f initialPosition): Controller(initialPosition)
{
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