#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View playerTracking(float x, float y) {
	float tmpX = x, tmpY = y;
	//чтобы не видеть края карты
	if (x < 100) tmpX = 100;
	if (x > 600) tmpX = 600;
	if (y < 150) tmpY = 150;
	if (y > 500) tmpY = 500;
	view.setCenter(tmpX + 50, tmpY);
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
