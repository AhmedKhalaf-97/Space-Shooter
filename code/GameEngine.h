#pragma once

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>

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
	void LoadUI();
	void CenterTheOriginForTexts();
	void UpdateHud();
	void DrawUI();
	void CheckIfLevelIsCompleted();
	void Run();
	void Draw();
private:
	Clock clock;
	Time dt;

	bool isGameStarted = false;
	bool isGameOver = false;
	bool isLevelCompleted = false;

	Vector2f screenResolution;

	RenderWindow window;

	View mainView;
	View UI_View;

	int score;
	int initialPlayerHealthAmount;

	Font font;

	vector<Text*> allTexts;

	Text titleText;
	Text startGameText;
	Text instructionsText; 

	Text hudText;

	Text gameOverText;

	Text levelCompletedText;

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

	int enemiesCount = 100; // Preferably to be in one of those numbers 4, 9, 16, 25, 36, 49, 64, etc...
	int enemiesAlive;

	int explosionVFXsPoolCount = 100;
	int availableExplosionVFXsIndex = 0;
	Texture explosionTexture;
	vector<Spritesheet*> explosionVFXs;

	SoundBuffer explosionSFXBuffer;
	Sound explosionSFX;
};

#endif