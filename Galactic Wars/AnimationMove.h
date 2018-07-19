#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "GameInfo.h"
#include "Caption.h"
//#include "Collidable.h"
//#include "GraphicsController.h"

using namespace std;
using namespace sf;

class AnimationMove
{
public:
	enum directions 
	{ 
		LEFT, 
		RIGHT, 
		UP,
		DOWN,
		LEFT_UP,
		LEFT_DOWN,
		RIGHT_UP,
		RIGHT_DOWN,
		ANOTHER 
	};

private:
	directions direction;

public:
	AnimationMove(Sprite &image, enum directions direction, float speed, bool changingDirection = false);
	AnimationMove();
	~AnimationMove();

	static void updateAnimations(); // Po kolei aktualizuje ka¿d¹ dzia³aj¹c¹ animacjê

	void play();	// dodaje obecny obiekt do vectora 'runningAnimations'
	void stop();
	void pause();

	Sprite * getImage(); // Zwraca wskaŸnik do oryginalnego Sprita
	bool isLooped(); // Animacja zapêtlona?
	float getSpeed(); // zwraca czas trwanie jednej klatki
	bool isReady();
	bool canChangeDirection();

	void setLoop(bool loop);
	void setSpeed(float movingSpeed);
	void setImage(Sprite & animatedSprite);

	void reset();

	bool isRunning;

private:

	bool move(); // Porusza obiektem; zwraca 'false' jeœli ruch siê zakoñczy³ i pêtla jest wy³¹czona

	Sprite *image; // WskaŸnik (Bezpoœrednie odwo³anie) do oryginalnego Sprita podanego w konstruktorze lub w funkcji 'setImage()'

	Clock clock; // Timer
	Time time; // Obiekt przechowuj¹cy czas

	static vector<AnimationMove*> runningAnimations; // Pojemnik na aktualnie pracuj¹ce animacje; * poniewa¿ 'this' zwraca '* const'

	bool loop;

	float elapsedTime; // Iloœ minionego czasu jednej klatki

	bool changingDirection;

protected:
	float movingSpeed; // Prêdkoœæ poruszania siê
};

