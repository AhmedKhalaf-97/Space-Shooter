#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SFML\Graphics.hpp>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>

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
	Vector2f screenResolution;

	RenderWindow window;

	View mainView;
	View hudView;

	Text hud;
	Font font;

	Texture backgroundTexture;
	vector<Sprite> backgroundSprites;

	PlayerController player;

	Clock clock;

	bool isGameRunning = true;
};

#endif