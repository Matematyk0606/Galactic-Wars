#include "PowerUp.h"

// Lista inicjalizacyjna konstruktora w celu wywo³ania konstruktora 
// klasy 'AnimationMove' przed utworzeniem obiektu tej klasy 
PowerUp::PowerUp(possibleEffects effect) : AnimationMove::AnimationMove(*this, AnimationMove::DOWN, 1)
{
	//fallingSpeed = &movingSpeed;
	//*fallingSpeed = 2;

	if (AnimationMove::isReady())
	{
		this->effect = effect;

		string nameTexture;

		switch (effect)
		{
		case LIFE: nameTexture = "extraLife"; break;
		case POSITIVE_SPEED: nameTexture = "speed+"; break;
		case NEGATIVE_SPEED: nameTexture = "speed-"; break;
		case MONEY100: nameTexture = "money100"; break;

		default: nameTexture = "speed+"; break;
		}

		setImageToSprite(*this, nameTexture);
	}
	else
	{
		cout << "Animacja ruchu nie jest gotowa!" << endl;
	}
}

PowerUp::PowerUp(const PowerUp & powerUp)
{
}

PowerUp::~PowerUp()
{
}

PowerUp::possibleEffects PowerUp::getEffect()
{
	return effect;
}

float PowerUp::getFallingSpeed()
{
	return movingSpeed;
}

void PowerUp::setEffect(possibleEffects effect)
{
	this->effect = effect;
}

void PowerUp::setFallingSpeed(float speed)
{
	movingSpeed = speed;
}
