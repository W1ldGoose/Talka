#pragma once
#include "Entity.h"

class ENEMY : public Entity
{
public:

	ENEMY(AnimationManager& a, Level& lev, int x, int y) :Entity(a, x, y)
	{
		option("Enemy", 0.01, 15, "move");
	}

	void update(float time)
	{
		x += dx * time;
		timer += time;
		if (timer > 3200) { dx *= -1; timer = 0; }

		if (health <= 0) {
			anim.set("dead"); dx = 0;
			timer_end += time;
			if (timer_end > 4000) life = false;
		}

		anim.tick(time);
	}
};
