#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>
#include "Spritesheet.h"

#include "PlayerController.h"

using namespace sf;
using namespace std;


using namespace sf;

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

	Texture backgroundTexture;
	vector<Sprite> backgroundSprites;
	RenderTexture finalBackgroundRenderTexture;

	PlayerController player;

#pragma region Dynamic background stuff
	int textureWidth;
	int textureHeight;

	int rows;
	int cols;

	float minY;
	float maxY;

	float baseSpeed = 500;
	float speed = baseSpeed;
#pragma endregion


};

#endif