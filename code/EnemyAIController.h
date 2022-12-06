#pragma once

#ifndef ENEMY_AI_CONTROLLER_H
#define ENEMY_AI_CONTROLLER_H

#include "Controller.h"
#include "PlayerController.h"

#include <cstdlib>


class EnemyAIController : public Controller
{
public:
	EnemyAIController();
	EnemyAIController(Vector2f initialPosition);
	void Create(Vector2f initialPosition);
	void Move() override;
	void UpdateSurrondings(PlayerController* player, vector<EnemyAIController*>* aliveEnemies);
	void CheckIfShouldFire(Time dt) override;
	void AssignWeapons() override;
	void UpdateWeapons(Time dt, Vector2f newPos) override;
	vector<Sprite> GetProjectileSprites() override;
	void UpdateController(Time dt, Vector2f screenResolution);
	bool IsEnabled();
	void SetIsEnabled(bool condition);

private:
	ProjectileType selectedProjectileType = ProjectileType::Bullet_Type;
	Vector2f screenResolution;

	bool enabled = true;

	PlayerController* player;
	vector<EnemyAIController*>* aliveEnemies;
};

#endif