#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class HealthBar {
	Texture txtrH;
	Sprite sprtH;
	int max;
	RectangleShape bar;
public:
	void update(int playerH);
	void draw(RenderWindow& window);
	HealthBar();
};

HealthBar::HealthBar() {
	txtrH.loadFromFile("files/health.png");
	sprtH.setTexture(txtrH);
	sprtH.setScale(2, 2);
	bar.setFillColor(Color(0, 0, 0));
	bar.setScale(2, 2);
	max = 20;
}

void HealthBar::update(int playerH) {
	if (playerH >= 0 && playerH < max) {
		bar.setSize(Vector2f(-((max - playerH) * 56 / max), 4));
	}
}

void HealthBar::draw(RenderWindow& window) {
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();

	sprtH.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);
	bar.setPosition(center.x - size.x / 2 + 160, center.y - size.y / 2 + 30);

	window.draw(sprtH);
	window.draw(bar);

}