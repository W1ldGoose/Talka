#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Level.h"

using namespace sf;

//абстрактный класс Entityn bbb   
class Entity
{
public:
	float x, y, dx, dy, w, h;
	AnimationManager anim;
	bool hit;//?
	bool life, dir;
	float timer, timer_end;
	std::vector<Object> obj;
	std::string Name;
	int health;

	virtual void update(float time) = 0; //чисто виртуальная функция

	FloatRect getRect();
	Entity(AnimationManager& a, int X, int Y);
	void draw(RenderWindow& window);

	void option(std::string NAME, float SPEED, int HEALTH, std::string FIRST_ANIM);
	float getCoordinateX() { return x; };
	float getCoordinateY() { return y; };
};

FloatRect Entity::getRect()
{
	return FloatRect(x, y, w, h);
}
Entity::Entity(AnimationManager& a, int X, int Y)
{
	anim = a;
	x = X;
	y = Y;
	dir = false;
	hit = false;

	life = true;
	timer = 0;
	timer_end = 0;
	dx = dy = 0;
}

//отрисовка для всех производных классов будет одинаковой
void Entity::draw(RenderWindow& window)
{
	anim.drawAnim(window, x, y+h);
}

//firstAnim = "stand" - ?
void Entity::option(std::string NAME, float spd = 0, int hlth = 10, std::string firstAnim = "")
{
	Name = NAME;
	if (firstAnim != "") anim.set(firstAnim);
	w = anim.getW();
	h = anim.getH();
	dx = spd;
	health = hlth;
}
