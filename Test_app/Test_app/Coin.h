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
	dy = -0.01;
	x = X;
	y = Y;
}


void Coin::update(float time)
{
	y += dy * time;
	timer += time;
	if (timer > 500)
	{
		dy *= -1;
		timer = 0;
	}

	if (health <= 0) {
		 life = false;
	}

	anim.tick(time);
}

