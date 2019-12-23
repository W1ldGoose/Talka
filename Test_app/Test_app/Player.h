#pragma once
#include "Entity.h"
#include <map>

class Player : public Entity {
public:

	bool onFloor = true, fight;
	enum { stand, run, sit, jump, fight1, fight2, fight3, dead, climb, block } state;

	std::map<std::string, bool> key;

	void CheckKey();

	void Animation(float time);

	void collision(int num);

	void update(float time);
	Player(AnimationManager& a, Level& lev, int x, int y);
};

Player::Player(AnimationManager& a, Level& lev, int x, int y) : Entity(a, x, y) {
	option("PLAYER", 0, 100, "stand");
	state = stand;
	obj = lev.GetAllObjects();
}

//дописать разные состояния и учесть вариант, когда клавиши не нажаты
void Player::CheckKey() {
	if (key["LEFT"]) {
		dir = 1;
		if (state == stand) {
			state = run;
			dx = -0.1;
		}
	}
	if (key["RIGHT"]) {
		dir = 0;
		if (state == stand) {
			state = run;
			dx = 0.1;
		}
	}
	if (key["UP"]) {
		if (state == stand || state == run) {
			dy = -0.3;
			state = jump;
			anim.play("jump");
		}

	}
	if (key["DOWN"]) {
		if (state == stand || state == run) {
			dx = 0;
			state = sit;
		}
	}
	if (!(key["LEFT"] || key["RIGHT"])) {
		dx = 0;
		if (state == run) state = stand;
	}
	if (!key["DOWN"]) {
		if (state == sit) state = stand;
	}
	if (key["RIGHT"] && key["LEFT"]) {
		if (state == run) {
			state = stand;
			dx = 0;
		}

	}
	if (key["F"]) {
		if (state != run)
			fight = true;
	}
	if (!key["F"])
	{
		fight = false;
	}
	key["RIGHT"] = false;
	key["LEFT"] = false;
	key["F"] = false;
	key["UP"] = false;
	key["DOWN"] = false;
}
void Player::Animation(float time)
{
	if (state == stand) anim.set("stand");
	if (state == run) anim.set("run");
	if (state == jump) anim.set("jump");
	if (state == sit) anim.set("sit");

	if (hit) {
		timer += time;
		if (timer > 800) { hit = false; timer = 0; }
		anim.set("block");
	}

	if (fight) {
		anim.set("fight1");
	}

	if (dir) anim.flip();
	anim.tick(time);
}
void Player::collision(int num) {
	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (dy > 0 && num == 1) { y = obj[i].rect.top - h;  dy = 0;   state = stand; }
				if (dy < 0 && num == 1) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (dx > 0 && num == 0) { x = obj[i].rect.left - w; }
				if (dx < 0 && num == 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
}

void Player::update(float time) {
	CheckKey();
	Animation(time);
	dy += 0.0005 * time;

	x += dx * time;
	collision(0);
	y += dy * time;
	collision(1);
}
