#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View playerTracking(float x, float y, std::vector<Sprite>& back) {
	float tmpX = x, tmpY = y;
	std::vector<Sprite>::reverse_iterator it;
	//чтобы не видеть края карты
	if (x < 320) tmpX = 320;
	if (x > 550) tmpX = 550;
	if (y < 200) tmpY = 200;
	if (y > 280) tmpY = 280;
	int tmp = 1;
	for (it = back.rbegin(); it != back.rend() - 1; it++) {
		//if (x > 320 && x < 550)//???
			it->setPosition(-x/(tmp * 6), 0);
		tmp++;
	}
	view.setCenter(tmpX+50, tmpY);
	return view;
}

void viewMap(float time) { //функция для перемещения камеры по карте

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1 * time, 0);//скроллим карту вправо
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1 * time);//скроллим карту вниз 
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1 * time, 0);//скроллим карту влево
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1 * time);//скроллим карту вправо
	}
}

void changeView() {
	if (Keyboard::isKeyPressed(Keyboard::PageUp))
		view.zoom(1.0009);
	if (Keyboard::isKeyPressed(Keyboard::PageDown))
		view.zoom(0.9990f);
}
