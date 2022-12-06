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
#include "CollisionDetection.h"

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
	void GetAllObjectsAndCheckForCollisions();
	void InstantiateExplosionVFXsObjects();
	void PlayExplosions();
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

	CollisionDetection collisionDetection;

	vector<Controller*> allControllers;
	vector<Projectile*> allProjectiles;

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

	int enemiesCount = 64; // Preferably to be in one of those numbers 4, 9, 16, 25, 36, 49, 64, etc...
	int enemiesAlive;

	int explosionVFXsPoolCount = 100;
	int availableExplosionVFXsIndex = 0;
	Texture explosionTexture;
	vector<Spritesheet*> explosionVFXs;
};

#endif