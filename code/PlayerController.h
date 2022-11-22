#pragma once
#ifndef PlAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <SFML\Graphics.hpp>
#include "Controller.h"

using namespace sf;

class PlayerController : public Controller
{
public:
	PlayerController(Vector2f initialPosition);
	void Move() override;
private:
};

#endif