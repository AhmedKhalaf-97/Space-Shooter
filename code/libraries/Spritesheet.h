#pragma once

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML\Graphics.hpp>

using namespace sf;

class Spritesheet
{
public:
	Spritesheet();
	Spritesheet(Texture spritesheetTexture, int rows, int columns);
	void Create(Texture spritesheetTexture, int rows, int columns);
	void SetPosition(Vector2f position);
	void SetScale(Vector2f scale);
	void SetRotation(float angle);
	/// <summary>
	/// Lower animation rate value means faster animation speed.
	/// </summary>
	/// <param name="rate"></param>
	void SetAnimationRate(float rate);
	bool CheckIfLooping();
	void SetIsLooping(bool condition);
	bool CheckIfStillPlaying();
	Sprite GetSprite();
	void PlayAnimation(Time timeElapsed);
private:
	Texture m_texture;
	Sprite m_sprite;
	IntRect frameRectangle;
	Vector2f m_position;
	Vector2f m_scale;
	float m_angle;

	float animatingRate = 0.5;
	float nextTimeToAnimate = 0;
	double elapsedTime = 0;

	Vector2u frameSize;
	int rows;
	int cols;
	int c = 0;
	int r = 0;

	bool isLooping = false;
	bool stopPlaying = false;
};

#endif // !SPRITESHEET_H
