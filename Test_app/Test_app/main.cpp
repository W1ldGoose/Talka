#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Level.h"
#include "View.h"
using namespace sf;

int main()
{
	Level lvl;
	lvl.LoadFromFile("files/New_Level.tmx");
	Object pl = lvl.GetObject("PLAYER");

	RenderWindow window(sf::VideoMode(600, 400), "Gayme");
	view.reset(FloatRect(0, 0, 400, 260));

	Texture textPlayer;

	textPlayer.loadFromFile("files/knight.png");

	AnimationManager animPlayer;

	animPlayer.loadFromXML("files/hero.xml", textPlayer);
	Clock clock;
	 
	Player player(animPlayer,lvl, pl.rect.left, pl.rect.top);
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 600;
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
		if (Keyboard::isKeyPressed(Keyboard::F)) player.key["F"] = true;

		animPlayer.tick(time);
		playerTracking(player.x, player.y);
		viewMap(time);
		window.setView(view);
		window.clear();

		lvl.Draw(window);
		player.draw(window);
		window.display();
	}
	return 0;
}