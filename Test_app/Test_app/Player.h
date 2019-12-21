#pragma once
#include "Entity.h"
#include <map>

class Player : public Entity {
public:

	bool onFloor = true, fight;
	enum { stand, run, sit, jump } state;

	std::map<std::string, bool> key;

	void CheckKey();

	void Animation(float time);

	void update(float time);
	Player(AnimationManager& a, int x, int y);
};

Player::Player(AnimationManager& a, int x, int y) : Entity(a, x, y) {
	option("PLAYER", 0, 100, "stand");
	state = stand;
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
			dy = -0.3; state = jump;
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

	key["RIGHT"] = false;
	key["LEFT"] = false;
	//key["F"] = false;
	key["UP"] = false;
	key["DOWN"] = false;
}
void Player::Animation(float time)
{
	if (state == stand) anim.set("stand");
	if (state == run) anim.set("run");
	if (state == jump) anim.set("jump");
	if (state == sit) anim.set("sit");

	if (dir) anim.flip();
	anim.tick(time);
}

void Player::update(float time) {
	CheckKey();
	Animation(time);
	dy += 0.0005 * time;


}
