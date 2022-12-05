#pragma once

#ifndef MISSILE_H
#define MISSILE_H

#include "Projectile.h"

class Missile : public Projectile
{
public:
	Missile(Vector2f initialPos);
	void ConfigureProjectile() override;
};

#endif