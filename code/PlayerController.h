#pragma once
#ifndef PlAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "Controller.h"

using namespace sf;

class PlayerController : public Controller
{
public:
	PlayerController();
	//PlayerController(Vector2f initialPosition);
	void Move() override;
private:
};

#endif