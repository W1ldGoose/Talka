#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Level.h"
using namespace sf;

int main()
{
	Level lvl;
	lvl.LoadFromFile("LEVEL_0.tmx");
	Object pl = lvl.GetObject("PLAYER");

	RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	Texture test;

	test.loadFromFile("files/knight.png");

	AnimationManager anim;

	anim.loadFromXML("source/test_sprite.xml", test);
	Clock clock;
	 
	Player player(anim,lvl, 100, 100);
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
		player.update(time);

		if (Keyboard::isKeyPressed(Keyboard::Left)) player.key["LEFT"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Right)) player.key["RIGHT"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Up)) player.key["UP"] = true;
		if (Keyboard::isKeyPressed(Keyboard::Down)) player.key["DOWN"] = true;

		anim.tick(time);
		window.clear();
		lvl.Draw(window);
		player.draw(window);
		window.display();
	}
	return 0;
}