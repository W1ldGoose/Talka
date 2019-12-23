#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

View view;

View playerTracking(float x, float y) {
	float tmpX = x, tmpY = y;
	//����� �� ������ ���� �����
	if (x < 100) tmpX = 100;
	if (x > 600) tmpX = 600;
	if (y < 150) tmpY = 150;
	if (y > 500) tmpY = 500;
	view.setCenter(tmpX + 50, tmpY);
	return view;
}

void viewMap(float time) { //������� ��� ����������� ������ �� �����

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(0.1 * time, 0);//�������� ����� ������
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, 0.1 * time);//�������� ����� ���� 
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-0.1 * time, 0);//�������� ����� �����
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -0.1 * time);//�������� ����� ������
	}
}
