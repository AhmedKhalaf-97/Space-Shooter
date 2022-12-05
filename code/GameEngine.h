#pragma once

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>

#include "Spritesheet.h"

#include "PlayerController.h"
#include "Projectile.h"

using namespace sf;
using namespace std;

class GameEngine
{
public:
	GameEngine();
	void CreateBackground();
	void UpdateBackground(Time dt, int playerDirection);
	void Run();
private:
	Clock clock;

	bool isGameRunning = true;

	Vector2f screenResolution;

	RenderWindow window;

	View mainView;
	View hudView;

	Text hud;
	Font font;

	PlayerController player;

#pragma region Dynamic background stuff
	Texture backgroundTexture;
	vector<Sprite> backgroundSprites;
	RenderTexture finalBackgroundRenderTexture;

	int textureWidth;
	int textureHeight;

	int rows;
	int cols;

	float minY;
	float maxY;

	float baseSpeed = 500;
	float speed = baseSpeed;
#pragma endregion

	//ProjectileObjectsPool projectileObjectsPool;
vector<Projectile*> projectiles;
};

#endif