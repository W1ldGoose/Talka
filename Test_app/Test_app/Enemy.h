#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:

	Enemy(AnimationManager& a, Level& lev, int x, int y) :Entity(a, x, y)
	{
		option("enemy", 0.02, 15, "walk");
	}

	void update(float time)
	{
		x += dx * time;
		timer += time;
		if (timer > 3200)
		{
			dx *= -1;
			timer = 0;
			dir = !dir;
			anim.flip(dir);
		}

		if (health <= 0) {
			anim.set("dead"); dx = 0;
			timer_end += time;
			if (timer_end > 4000) life = false;
		}

		anim.tick(time);
	}
};
