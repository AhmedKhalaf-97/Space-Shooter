#include "CollisionDetection.h"

void CollisionDetection::CheckForCollisions(vector<Projectile*>& projectiles, vector<Controller*>& controllers)
{
	for (Projectile* projectile : projectiles)
	{
		for (Controller* controller : controllers)
		{
			if (projectile->GetFloatRect().intersects(controller->GetFloatRect()))
			{
				cout << "Hit" << endl;
				controller->TakeDamage(1);
			}
		}
	}
}
