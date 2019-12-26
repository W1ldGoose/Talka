#pragma once
#include "Entity.h"
#include <map>
#include <SFML/Graphics.hpp>


class Player : public Entity {
public:
	int coins;
	bool fight;
	Font font;
	Text text;
	enum { stand, run, sit, jump, fight1, fight2, fight3, dead, climb, block } state;

	std::map<std::string, bool> key;

	void CheckKey();

	void Animation(float time);

	void collision(int num);

	void update(float time);
	void DEAD(RenderWindow& window);
	Player(AnimationManager& a, Level& lev, int x, int y);
};

Player::Player(AnimationManager& a, Level& lev, int x, int y) : Entity(a, x, y) {
	option("PLAYER", 0, 20, "stand");
	state = stand;
	coins = 0;
	obj = lev.GetAllObjects();
	font.loadFromFile("files/pixel_font.ttf");
	text.setFont(font);
	text.setStyle(Text::Bold | Text::Underlined);
	text.setString("POTRACHENO");
	text.setOutlineThickness(3);
	text.setCharacterSize(80);
	text.setFillColor(Color::Red);
}

//дописать разные состояния и учесть вариант, когда клавиши не нажаты
void Player::CheckKey() {
	if (key["LEFT"]) {
		dir = 1;
		if (state == stand) {
			state = run;
			dx = -0.15;
		}
	}
	if (key["RIGHT"]) {
		dir = 0;
		if (state == stand) {
			state = run;
			dx = 0.15;
		}
	}
	if (key["UP"]) {
		if (state == stand || state == run) {
			dy = -0.3;
			state = jump;
			anim.play("jump");
			anim.animationList["jump"].currentFrame = 0;
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


	if (health <= 0) {
		anim.set("dead"); dx = 0; dy = 0;

	}
	if (hit) {
		timer += time;
		if (timer > 800) { hit = false; timer = 0; }
		anim.set("block");
	}
	if (fight) {
		timer += time;
		if (timer > 800) { 
			timer = 0; 
			fight = false;
		}
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
			if (obj[i].name == "thorn" && !hit) {
				if (!dir)
					dx += 0.03;
				else dx -= 0.03;
				hit = true;
				y = obj[i].rect.top - h;
				dy = -0.2;
				health -= 1;
			}

			
		}
	
}

void Player::update(float time) {
	
	CheckKey();
	Animation(time);
	dy += 0.0004 * time;

	if (health <= 0) {
		 life = false;
	}
	x += dx * time;
	collision(0);
	y += dy * time;
	collision(1);
}

void Player::DEAD(RenderWindow& window) {
	Vector2f center= window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	text.setPosition(center.x - size.x / 4-30, center.y - size.y / 4);
	window.draw(text);
}