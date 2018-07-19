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
	if (!runningAnimations.empty())// Je�li lista obecnie dzia�aj�cych animacji nie jest pusta
	{
		for (int i = 0; i < runningAnimations.size(); i++)
		{
			if (runningAnimations[i]->move()) continue; // Je�li animacja pracuje, odliczaj dalej i zostaw j� w spokoju
			else runningAnimations.erase(runningAnimations.begin() + i); // Je�li wcze�niej dodana animacja przesta�a pracowa� (np. Zosta�a zatrzymana), wywal j� z listy
		}
	}
}

void AnimationMove::play()
{
	if (isRunning == false && isReady()) // Je�li jest wy��czona - w��cz
	{
		isRunning = true;

		elapsedTime = 0; // Zerowanie up�yni�tego  czasu
		clock.restart(); // Zerowanie timera

		runningAnimations.push_back(this); // Dodaje obecn� animacj� do listy dzia�aj�cych animacji
	}
}

void AnimationMove::stop()
{
	isRunning = false;
	elapsedTime = 0; // Zerowanie up�yni�tego czasu
	clock.restart(); // Zerowanie odliczaj�cego timera
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
		time = clock.restart(); // Resetuje i pobiera warto��� timera

		elapsedTime += time.asMilliseconds(); // Sumowanie minionego czasu

		if (elapsedTime >= movingSpeed) // Je�li nadszed� czas na zmian� klatki
		{
			elapsedTime = 0; // Zerowanie up�yni�tego  czasu
			clock.restart(); // Zerowanie timera
			

		}

		return true;
	}
	else return false; // Je�li animacja zosta�a zatrzymana
}
