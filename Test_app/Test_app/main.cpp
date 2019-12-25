#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Level.h"
#include "View.h"
#include <list>
#include "Enemy.h"

using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(960, 480), "Gayme");
	//view.reset(FloatRect(0, 0, 720, 360));

	Level lvl;
	lvl.LoadFromFile("files/New_Level.tmx");
	
	std::list<Entity*>  entities;
	std::list<Entity*>::iterator  it = entities.begin();

	Texture textPlayer, textEnemy;

	textPlayer.loadFromFile("files/knight.png");
	textEnemy.loadFromFile("files/Skeleton.png");

	AnimationManager animPlayer, animEnemy;

	animPlayer.loadFromXML("files/hero.xml", textPlayer);
	animPlayer.animationList["jump"].loop = 0;
	animEnemy.loadFromXML("files/enemy.xml", textEnemy);
	animEnemy.animationList["dead"].loop = 0;

	Object pl = lvl.GetObject("PLAYER");
	Player player(animPlayer, lvl, pl.rect.left, pl.rect.top);
	player.y = player.y - player.h;
	player.w = player.w * 2;

	std::vector<Object> enem = lvl.GetObjects("enemy");
	for (int i = 0; i < enem.size(); i++) {
		entities.push_back(new enemy(animEnemy, lvl, enem[i].rect.left, enem[i].rect.top));
	}

	 
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

	Clock clock;
	view.reset(FloatRect(0, 0, 720, 360));
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 600;
		if (time > 60) time = 60;

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
		
		for (it = entities.begin(); it != entities.end();)
		{
			Entity* b = *it;
			b->update(time);
			if (b->life == false) { it = entities.erase(it); delete b; }
			else it++;
		}

		for (it = entities.begin(); it != entities.end(); it++)
		{
			//1. враги
			if ((*it)->Name == "enemy")
			{
				Entity* currentEnemy = *it;

				if (currentEnemy->health <= 0) continue;

				if (std::abs(player.x - currentEnemy->x) < 50 && std::abs(player.y - currentEnemy->y) < 30)
					if (player.fight) { currentEnemy->dx = 0; currentEnemy->health -= 5; }
					else if (!player.hit) {
						player.health -= 5; player.hit = true;//прописать анимацию при получении урона
						if (player.dir) player.x += 10; else player.x -= 10;
					}

			}

		}
		player.update(time);
		viewMap(time);
		changeView();
		window.setView(view);
		window.clear();

		for (int i = 0; i < back.size(); i++) {
			window.draw(back[i]);
		}
		lvl.Draw(window);
		for (it = entities.begin(); it != entities.end(); it++)
			(*it)->draw(window);
		player.draw(window);
		window.display();
	}
	return 0;
}