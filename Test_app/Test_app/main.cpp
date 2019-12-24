#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Level.h"
#include "View.h"
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(960, 480), "Gayme");
	//view.reset(FloatRect(0, 0, 720, 360));

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
		tmpSprite.setPosition(0, 0);
		back.push_back(tmpSprite);
	}

	Texture menu_back, menu_enter, menu_exit;
	menu_back.loadFromFile("files/menu.png");
	menu_enter.loadFromFile("files/press-enter.png");
	menu_exit.loadFromFile("files/exit.png");
	Sprite menu1(menu_back), menu2(menu_enter), menu3(menu_exit);
	menu2.setScale(4.f, 4.f);
	menu3.setScale(4.f, 4.f);
	menu1.setScale(1.f, 0.92664);
	bool Menu = 1;
	int MenuNum = 0;
	menu1.setPosition(0, 0);
	menu2.setPosition(100, 100);
	menu3.setPosition(100, 250);


	/////меню
	while (Menu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		MenuNum = 0;
		window.clear(Color(0, 0, 0));

		if (Keyboard::isKeyPressed(Keyboard::Enter)) { MenuNum = 2; }
		if (IntRect(100, 100, menu2.getTextureRect().width * 4, menu2.getTextureRect().height * 4).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); MenuNum = 2; }
		if (IntRect(100, 250, menu3.getTextureRect().width * 4, menu3.getTextureRect().height * 4).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Yellow); MenuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Enter))
		{
			if (MenuNum == 2) Menu = false;
			if (MenuNum == 3) { window.close(); Menu = false; }

		}

		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}

	view.reset(FloatRect(0, 0, 720, 360));
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