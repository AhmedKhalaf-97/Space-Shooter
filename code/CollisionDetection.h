#pragma once

#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "Projectile.h"
#include "Controller.h"
#include "PlayerController.h"

class CollisionDetection
{
public:
	void CheckForCollisions(vector<Projectile*>& projectiles, vector<Controller*>& controllers);
};

#endif