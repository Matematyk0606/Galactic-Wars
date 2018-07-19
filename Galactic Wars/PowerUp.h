#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicsController.h"
#include "AnimationMove.h"

using namespace std;
using namespace sf;

class PowerUp : public Sprite, AnimationMove
{
private:
	enum possibleEffects { LIFE, POSITIVE_SPEED, NEGATIVE_SPEED, MONEY100 };
	possibleEffects effect;

public:
	PowerUp(enum possibleEffects effect);
	PowerUp(const PowerUp &powerUp); // Konstruktor kopiuj¹cy, umo¿liwia pisowniê: PowerUp(PowerUp);
	~PowerUp();

	enum possibleEffects getEffect();
	float getFallingSpeed();

	void setEffect(enum possibleEffects effect);
	void setFallingSpeed(float speed);
};

