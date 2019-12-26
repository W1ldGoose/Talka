#pragma once
#include "Animation.h"
#include "Entity.h"

using namespace sf;

class Coin:public Entity{
public:
	Coin(AnimationManager& anim, Level& lev, int X, int Y);

	void update(float time);

};

Coin::Coin(AnimationManager& anim, Level& lev, int X, int Y):Entity(anim,x,y) {
	option("coin", 0, 10, "idle");
	x = lev.GetObject("coin").rect.left;
	y = lev.GetObject("coin").rect.top;
}


void Coin::update(float time)
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
		 life = false;
	}

	anim.tick(time);
}

