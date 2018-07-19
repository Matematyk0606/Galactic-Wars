#include "AnimationMove.h"

vector<AnimationMove*> AnimationMove::runningAnimations;


AnimationMove::AnimationMove(Sprite & image, directions direction, float speed, bool changingDirection)
{
	this->image = &image;
	this->direction = direction;
	movingSpeed = speed;
	this->changingDirection = changingDirection;

	isRunning = false;

	loop = false;
}

AnimationMove::AnimationMove()
{
	image = NULL;
	direction = DOWN;
	movingSpeed = 1;
	changingDirection = false;

	isRunning = false;

	loop = false;
}


AnimationMove::~AnimationMove()
{
}

void AnimationMove::updateAnimations()
{
	if (!runningAnimations.empty())// Jeœli lista obecnie dzia³aj¹cych animacji nie jest pusta
	{
		for (int i = 0; i < runningAnimations.size(); i++)
		{
			if (runningAnimations[i]->move()) continue; // Jeœli animacja pracuje, odliczaj dalej i zostaw j¹ w spokoju
			else runningAnimations.erase(runningAnimations.begin() + i); // Jeœli wczeœniej dodana animacja przesta³a pracowaæ (np. Zosta³a zatrzymana), wywal j¹ z listy
		}
	}
}

void AnimationMove::play()
{
	if (isRunning == false && isReady()) // Jeœli jest wy³¹czona - w³¹cz
	{
		isRunning = true;

		elapsedTime = 0; // Zerowanie upˆyniêtego  czasu
		clock.restart(); // Zerowanie timera

		runningAnimations.push_back(this); // Dodaje obecn¹ animacjê do listy dzia³aj¹cych animacji
	}
}

void AnimationMove::stop()
{
	isRunning = false;
	elapsedTime = 0; // Zerowanie up³yniêtego czasu
	clock.restart(); // Zerowanie odliczaj¹cego timera
}

void AnimationMove::pause()
{
	isRunning = false;
}

Sprite * AnimationMove::getImage()
{
	return image;
}

bool AnimationMove::isLooped()
{
	return loop;
}

float AnimationMove::getSpeed()
{
	return movingSpeed;
}

bool AnimationMove::isReady()
{
	if (image != NULL && direction != NULL && movingSpeed > 0) return true;
	else return false;
}

void AnimationMove::setLoop(bool loop)
{
	this->loop = loop;
}

void AnimationMove::setSpeed(float movingSpeed)
{
	this->movingSpeed = movingSpeed;
}

void AnimationMove::setImage(Sprite & animatedSprite)
{
	image = &animatedSprite;
}

void AnimationMove::reset()
{
	isRunning = false;
	loop = false;

	movingSpeed = 125; // W milisekundach

	elapsedTime = 0;
	clock.restart();

	image = NULL;
}

bool AnimationMove::move()
{
	if (isRunning == true)
	{
		time = clock.restart(); // Resetuje i pobiera warto˜œæ timera

		elapsedTime += time.asMilliseconds(); // Sumowanie minionego czasu

		if (elapsedTime >= movingSpeed) // Je˜li nadszedˆ czas na zmianê klatki
		{
			elapsedTime = 0; // Zerowanie upˆyniêtego  czasu
			clock.restart(); // Zerowanie timera
			

		}

		return true;
	}
	else return false; // Jeœli animacja zosta³a zatrzymana
}
