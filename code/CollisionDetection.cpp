#include "CollisionDetection.h"

void CollisionDetection::CheckForCollisions(vector<Projectile*>& projectiles, vector<Controller*>& controllers)
{
	for (Projectile* projectile : projectiles)
	{
		for (Controller* controller : controllers)
		{
			if (projectile->IsItActive() && projectile->GetFloatRect().intersects(controller->GetFloatRect()))
			{
				controller->TakeDamage(projectile->GetDamageAmount());
				projectile->DeactivateProjectile();
			}
		}
	}
}
