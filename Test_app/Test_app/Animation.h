#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "source/TinyXML/tinyxml.h"
using namespace sf;

//класс анимации, хранит одну анимацию
class Animation {
public:
	std::vector<IntRect> frames, framesFlip; //массив кадров обычный и с повернутыми изображениями
	float frameSpeed, currentFrame;
	bool flip, isPlaying, loop;
	Sprite sprite;

	Animation();
	void tick(float time);
};

Animation::Animation()
{
	currentFrame = 0;
	isPlaying = true;
	flip = false;
	loop = true;
}


void Animation::tick(float time) {//проигрывание анимации
	if (!isPlaying) return;

	currentFrame += frameSpeed * time;

	if (currentFrame > frames.size()) {
		currentFrame -= frames.size();
		if (!loop) {
			isPlaying = false;
			return;
		}
	}

	int i = currentFrame;
	sprite.setTextureRect(frames[i]);
	if (flip)
		sprite.setTextureRect(framesFlip[i]);
}

//вспомогательный класс 
class AnimationManager {
public:
	std::string currentAnim;// имя текущей анимации
	//контейнер с ключом - название анимации, и значением - класс Animation
	std::map<std::string, Animation> animationList;

	AnimationManager() {}
	~AnimationManager() {
		animationList.clear();
	}

	void createAnim(std::string name, Texture& tex, int x, int y, int w, int h, int count, float speed, int step, bool LOOP);

	void drawAnim(RenderWindow& win, int x, int y);//вывод анимации в координату x,y

	void set(std::string name);//переключение на анимацию с именем name

	void loadFromXML(std::string fileName, Texture& t);

	void flip(bool b = 1) { animationList[currentAnim].flip = b; }//поворот анимации

	void tick(float time) { animationList[currentAnim].tick(time);}//проигрывание анимации

	void pause() { animationList[currentAnim].isPlaying = false;}//приостановление проигрывания анимации

	void play() { animationList[currentAnim].isPlaying = true;}//возобновление -//-

	void play(std::string name) { animationList[name].isPlaying = true; }

	bool isPlaying() { return animationList[currentAnim].isPlaying;}

	float getH() { return animationList[currentAnim].frames[0].height; }

	float getW() { return animationList[currentAnim].frames[0].width; }
};

void AnimationManager::createAnim(std::string name, Texture& texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool LOOP = true) {
	Animation a;
	a.frameSpeed = speed;
	a.loop = LOOP;
	a.sprite.setTexture(texture);
	a.sprite.setOrigin(0, h);

	for (int i = 0; i < count; i++)
	{
		a.frames.push_back(IntRect(x + i * step, y, w, h));
		a.framesFlip.push_back(IntRect(x + i * step + w, y, -w, h));
	}
	animationList[name] = a;
	currentAnim = name;
}

void AnimationManager::drawAnim(RenderWindow& win, int x = 0, int y = 0) {
	animationList[currentAnim].sprite.setPosition(x, y);
	win.draw(animationList[currentAnim].sprite);
}

void AnimationManager::set(std::string name)
{
	currentAnim = name;
	animationList[currentAnim].flip = false;// по умолчанию flip=false, т.е. анимация повернута вправо
}

//загрузка из файла XML
void AnimationManager::loadFromXML(std::string fileName, Texture& t)
{
	TiXmlDocument animFile(fileName.c_str());

	animFile.LoadFile();

	TiXmlElement* head;
	head = animFile.FirstChildElement("sprites");

	TiXmlElement* animElement;
	animElement = head->FirstChildElement("animation");
	while (animElement)
	{
		Animation anim;
		currentAnim = animElement->Attribute("title");
		int delay = atoi(animElement->Attribute("delay"));
		anim.frameSpeed = 1.0 / delay; anim.sprite.setTexture(t);

		TiXmlElement* cut;
		cut = animElement->FirstChildElement("cut");
		while (cut)
		{
			int x = atoi(cut->Attribute("x"));
			int y = atoi(cut->Attribute("y"));
			int w = atoi(cut->Attribute("w"));
			int h = atoi(cut->Attribute("h"));

			anim.frames.push_back(IntRect(x, y, w, h));
			anim.framesFlip.push_back(IntRect(x + w, y, -w, h));
			cut = cut->NextSiblingElement("cut");
		}

		anim.sprite.setOrigin(0, anim.frames[0].height);

		animationList[currentAnim] = anim;
		animElement = animElement->NextSiblingElement("animation");
	}
}


