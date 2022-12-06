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
#include "EnemyAIController.h"
#include "Projectile.h"

using namespace sf;
using namespace std;

class GameEngine
{
public:
	GameEngine();
	void CreateBackground();
	void UpdateBackground(int playerDirection);
	void SpawnEnemies();
	void UpdateEnemiesAIBehaviour();
	void Run();
	void Draw();
private:
	Clock clock;
	Time dt;

	bool isGameRunning = true;

	Vector2f screenResolution;

	RenderWindow window;

	View mainView;
	View hudView;

	Text hud;
	Font font;

	PlayerController player;
	vector<EnemyAIController*> enemies;
	vector<EnemyAIController*> aliveEnemies;

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

	float baseSpeed = 100;
	float speed = baseSpeed;
#pragma endregion

	int enemiesCount = 36; // Preferably to be in one of those numbers 4, 9, 16, 25, 36, 49, 64, etc...
	int enemiesAlive;
};

#endif