#include "GameEngine.h"

void GameEngine::CreateBackground()
{
	backgroundTexture.loadFromFile("graphics/background.png");

	textureWidth = backgroundTexture.getSize().x;
	textureHeight = backgroundTexture.getSize().y;

	rows = ceil(screenResolution.y / textureHeight);
	cols = ceil(screenResolution.x / textureWidth);

	minY = -rows * textureHeight;
	maxY = rows * textureHeight;

	int spritesCount = rows * cols * 3;

	for (int i = 0; i < spritesCount; i++)
	{
		backgroundSprites.push_back(Sprite(backgroundTexture));
	}

	int i = 0;
	for (int r = -rows; r <= rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			backgroundSprites[i].setPosition(Vector2f(c * textureWidth, r * textureHeight));
			i++;
		}
	}
}

void GameEngine::UpdateBackground(Time dt, int playerDirection)
{
	if (playerDirection == -1) // Player is moving forward.
	{
		speed = baseSpeed * 2;
	}
	else if (playerDirection == 1) // Player is moving backward.
	{
		speed = baseSpeed * 0.75;
	}
	else
	{
		speed = baseSpeed;
	}

	for (Sprite& backgroundSprite : backgroundSprites)
	{
		if (backgroundSprite.getPosition().y >= maxY)
		{
			backgroundSprite.setPosition(backgroundSprite.getPosition().x, minY);
		}

		backgroundSprite.setPosition(backgroundSprite.getPosition().x,
					 backgroundSprite.getPosition().y + speed * dt.asSeconds());
	}
}