#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Level.h"
#include "View.h"
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(960, 480), "Gayme");
	view.reset(FloatRect(0, 0, 720, 360));


	Level lvl;
	lvl.LoadFromFile("files/New_Level.tmx");

	
	Texture textPlayer;
	textPlayer.loadFromFile("files/knight.png");
	AnimationManager animPlayer;
	animPlayer.loadFromXML("files/hero.xml", textPlayer);
	Object pl = lvl.GetObject("PLAYER");
	Player player(animPlayer, lvl, pl.rect.left, pl.rect.top);

	Clock clock;
	 
	std::vector <sf::Sprite> back;
	Sprite tmpSprite;
	for (int i = 0; i < lvl.backTextures.size(); i++) {
		tmpSprite.setTexture(lvl.backTextures[i]);
		tmpSprite.setTextureRect(IntRect(0, 0, lvl.backTextures[i].getSize().x, lvl.backTextures[i].getSize().y));
		//tmpSprite.setPosition(pl.rect.top, pl.rect.left);
		back.push_back(tmpSprite);
	}

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

		//камера следит за игроком, когда он двигается
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			player.key["LEFT"] = true;
			playerTracking(player.x, player.y, back);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			player.key["RIGHT"] = true;
			playerTracking(player.x, player.y, back);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			player.key["UP"] = true;
			playerTracking(player.x, player.y, back);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			player.key["DOWN"] = true;
			playerTracking(player.x, player.y, back);
		}
		if (Keyboard::isKeyPressed(Keyboard::F)) player.key["F"] = true;

		player.update(time);
		viewMap(time);
		changeView();
		window.setView(view);
		window.clear();

		for (int i = 0; i < back.size(); i++) {
			window.draw(back[i]);
		}
		lvl.Draw(window);
		player.draw(window);
		window.display();
	}
	return 0;
}