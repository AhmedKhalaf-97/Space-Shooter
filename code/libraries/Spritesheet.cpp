#include "Spritesheet.h"

Spritesheet::Spritesheet()
{
}

Spritesheet::Spritesheet(Texture spritesheetTexture, int rows, int columns)
{
	Create(spritesheetTexture, rows, columns);
}

void Spritesheet::Create(Texture spritesheetTexture, int rows, int columns)
{
	m_texture = spritesheetTexture;
	this->rows = rows;
	cols = columns;

	frameSize.x = m_texture.getSize().x / cols;
	frameSize.y = m_texture.getSize().y / rows;

	m_sprite.setTexture(m_texture);
	frameRectangle = IntRect(0, 0, frameSize.x, frameSize.y);
	m_sprite.setTextureRect(frameRectangle);
}

void Spritesheet::SetPosition(Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

void Spritesheet::SetScale(Vector2f scale)
{
	m_scale = scale;
	m_sprite.setScale(m_scale);
}

void Spritesheet::SetRotation(float angle)
{
	m_angle = angle;
	m_sprite.setRotation(angle);
}

void Spritesheet::SetAnimationRate(float rate)
{
	animatingRate = rate;
}

bool Spritesheet::CheckIfLooping()
{
	return isLooping;
}

void Spritesheet::SetIsLooping(bool condition)
{
	isLooping = condition;
}

bool Spritesheet::CheckIfStillPlaying()
{
	return !stopPlaying;
}

Sprite Spritesheet::GetSprite()
{
	return m_sprite;
}

void Spritesheet::PlayAnimation(Time dt)
{
	if (!stopPlaying)
	{

		elapsedTime += dt.asSeconds();
		if (elapsedTime >= nextTimeToAnimate)
		{
			nextTimeToAnimate = animatingRate + elapsedTime;

			frameRectangle.left = c * frameSize.x;
			frameRectangle.top = r * frameSize.y;
			m_sprite.setTextureRect(frameRectangle);

			if (c < cols - 1)
			{
				c++;
			}
			else
			{
				c = 0;

				if (r < rows - 1)
				{
					r++;
				}
				else
				{
					r = 0;
				}

				if (!isLooping && c == 0 && r == 0)
				{
					stopPlaying = true;
				}
			}

		}
	}

}
