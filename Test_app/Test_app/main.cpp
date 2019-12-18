#include <SFML/Graphics.hpp>
#include "Animation.h"
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	Texture test;

	test.loadFromFile("files/knight.png");

	/* увеличение мастштаба спрайта в 2 раза
	Sprite sprite;
	sprite.setTexture(test);
	sprite.setTextureRect(IntRect(14, 6, 20, 30));
	sprite.setScale(2.f, 2.f);
	*/

	AnimationManager anim;

	anim.loadFromXML("source/test_sprite.xml", test);
	Clock clock;

	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;
		if (time > 40) time = 40;

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		anim.tick(time);
		window.clear();
		anim.drawAnim(window, 100, 100);
		window.display();

	}
	return 0;
}