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

	static void updateAnimations(); // Po kolei aktualizuje ka�d� dzia�aj�c� animacj�

	void play();	// dodaje obecny obiekt do vectora 'runningAnimations'
	void stop();
	void pause();

	Sprite * getImage(); // Zwraca wska�nik do oryginalnego Sprita
	bool isLooped(); // Animacja zap�tlona?
	float getSpeed(); // zwraca czas trwanie jednej klatki
	bool isReady();
	bool canChangeDirection();

	void setLoop(bool loop);
	void setSpeed(float movingSpeed);
	void setImage(Sprite & animatedSprite);

	void reset();

	bool isRunning;

private:

	bool move(); // Porusza obiektem; zwraca 'false' je�li ruch si� zako�czy� i p�tla jest wy��czona

	Sprite *image; // Wska�nik (Bezpo�rednie odwo�anie) do oryginalnego Sprita podanego w konstruktorze lub w funkcji 'setImage()'

	Clock clock; // Timer
	Time time; // Obiekt przechowuj�cy czas

	static vector<AnimationMove*> runningAnimations; // Pojemnik na aktualnie pracuj�ce animacje; * poniewa� 'this' zwraca '* const'

	bool loop;

	float elapsedTime; // Ilo� minionego czasu jednej klatki

	bool changingDirection;

protected:
	float movingSpeed; // Pr�dko�� poruszania si�
};

