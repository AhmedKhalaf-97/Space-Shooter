#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "Projectile.h"

class Bullet : public Projectile
{
public:
	Bullet(Vector2f initialPos);
	void ConfigureProjectile() override;
};

#endif