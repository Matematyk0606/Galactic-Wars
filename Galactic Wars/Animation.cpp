#include "Animation.h"



vector<Animation*> Animation::runningAnimations;

Animation::Animation()
{
}

Animation::Animation(Sprite &animatedSprite, float frameTime, bool loop, vector<IntRect> framesRect)
					//: updatingThread(&Animation::update, this) // Lista inicjalizacyjna konstruktora (Wywoanie konstruktora wĄtku)
{
	isRunning = false; // Początkowo animacja jest wyłączona
	currentFrame = 0; // Numer startowej kaltki
	
	originalRect = animatedSprite.getTextureRect();
	image = &animatedSprite; // korzystanie z oryginalego Sprita w celu aktualizacji go na ekranie
	frames = framesRect; // Ustawianie vectora z koordynatami klatek animacji
	this->frameTime = frameTime; 
	this->loop = loop;
}

Animation::~Animation()
{
	//updatingThread.wait(); // Wywoanie destruktora wątku odpowiedzialnego za animację
}

void Animation::play()
{
	if(isRunning == false) // Jeśli jest wyłączona - włącz
	{
		isRunning = true;

		elapsedTime = 0; // Zerowanie upyniętego  czasu
		clock.restart(); // Zerowanie timera

		runningAnimations.push_back(this); // Dodaje obecną animację do listy działających animacji
		//updatingThread.launch(); // Uruchamia prywatny wątek odpowiedzialny za zmianę animacji
	}
}

void Animation::stop()
{
	isRunning = false;
	currentFrame = 0;
	elapsedTime = 0; // Zerowanie upłyniętego czasu
	clock.restart(); // Zerowanie odliczającego timera
	changeCurrentFrame(originalRect); // Ustaw oryginalne koordynaty, oryginalny obrazek
}

void Animation::pause()
{
	isRunning = false;
}

IntRect Animation::getRectOfCurrentFrame()
{
	return frames[currentFrame]; // Zwraca koordynaty obecnej klatki
}

Sprite * Animation::getImage()
{
	if (!frames.empty()) 
		changeCurrentFrame(currentFrame);

	return image;
}

vector<IntRect> Animation::getRectOfAllFrames()
{
	return frames;
}

bool Animation::isLooped()
{
	return loop;
}

float Animation::getFrameTime()
{
	return frameTime;
}

void Animation::replaceExistFrame(unsigned int ID, IntRect coordinates) // ID numerowane od 0 !!!
{
	if(ID >= 0 && ID <= frames.size() - 1) // Jeśli podany numer klatki istnieje
		frames[ID] = coordinates;
}

void Animation::replaceExistFrame(unsigned int ID, unsigned int x, unsigned int y, unsigned int width, unsigned int height) // ID numerowane od 0 !!!
{
	if(ID >= 0 && ID <= frames.size() - 1) // Jeśli podany numer klatki istnieje
		frames[ID] = IntRect(x, y, width, height);
}

void Animation::setLoop(bool loop)
{
	this->loop = loop;
}

void Animation::setFrameTime(float frameTime)
{
	this->frameTime = frameTime;
}

void Animation::setImage(Sprite & animatedSprite)
{
	image = &animatedSprite; // korzystanie z oryginalego Sprita w celu aktualizacji go na ekranie
}

void Animation::restoreOriginalRect()
{
	if(image != NULL)
		image->setTextureRect(originalRect);
}

void Animation::addFrame(IntRect coordinates)
{
	frames.push_back(coordinates);
}

void Animation::addFrame(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	frames.push_back(IntRect(x, y , width, height));
}

void Animation::changeCurrentFrame(IntRect frameRect)
{
	if(image != NULL)
		image->setTextureRect(frameRect);
}

void Animation::changeCurrentFrame(int ID) // ID numerowane od 0 !!!
{
	int sizeOfVector = frames.size() - 1; // Zmienna ta tworzona jest ponieważ if(ID <= frames.size() - 1) nie działa wedle założeń
	if (ID <= sizeOfVector && image != NULL)
	{
		if (ID == -1) // Ustawia wartość ze zmiennej 'currentFrame'
			image->setTextureRect(frames[currentFrame]);
		else if(ID < -1) // Odwołanie się do nieistniejącej klatki o numerze ujemnym
		{ 
			setColorConsoleFont(12); // Zmiana koloru czcionki na czerwony

			string textAlert = convertToPolishChars("Funkcja Animation::updateFrame(int ID); przyjmuje int większy od 0\nNie można ustawić klatki o numerze mniejszym niż -1\nKlatka o numerze -1 automatycznie ustawiana jest na wartość zmiennej\n'currentFrame'");
			cout << textAlert << endl;	// Komunikat deweloperski do programisty

			setColorConsoleFont(8); // Ponowna zmiana koloru czcionki na biały

			textAlert = "Funkcja Animation::updateFrame(int ID); przyjmuje int większy od 0. Nie można ustawić klatki o numerze mniejszym niż -1. Klatka o numerze -1 automatycznie ustawiana jest na wartość zmiennej 'currentFrame'";
			MessageBoxA(NULL, textAlert.c_str(), "Informacja deweloperska", MB_ICONWARNING); // Wyświetlanie okienka z powiadomieniem deweloperskim
		}
		else if (ID >= 0)
			image->setTextureRect(frames[ID]);
	}
}

void Animation::removeFrame(int ID) // ID numerowane od 0 !!!
{
	if (ID >= 0 && ID <= frames.size() - 1)
		frames.erase(frames.begin() + ID);
}

void Animation::reset()
{
	isRunning = false;
	loop = false;

	frameTime = 125; // W milisekundach
	currentFrame = 0;

	elapsedTime = 0;
	clock.restart();

	changeCurrentFrame(originalRect); // Ustaw oryginalne koordynaty, oryginalny obrazek
	image = NULL;
	originalRect = IntRect();

	frames.clear();
}

bool Animation::updateFrame()
{
	if(isRunning == true)
	{
		time = clock.restart(); // Resetuje i pobiera wartość timera

		elapsedTime += time.asMilliseconds(); // Sumowanie minionego czasu

		if(elapsedTime >= frameTime) // Jeli nadszed czas na zmianę klatki
		{
			elapsedTime = 0; // Zerowanie upyniętego  czasu
			clock.restart(); // Zerowanie timera

			currentFrame++; // Zmiana numeru klatki
			if (currentFrame <= frames.size() - 1) // Jeli numer klatki nie wykracza poza dostępny zakres
				changeCurrentFrame(currentFrame); // Podmiana koordynaów Sprita

			else if(currentFrame >= frames.size() - 1)
			{
				currentFrame = 0;

				if(loop == true) // Jeśli animacja jest zapętlona, rozpocznij ją od nowa
					changeCurrentFrame(0); // Ustawienie pierwszej klatki
				else // Jeśli bez zapętlenia
				{
					stop(); // Zatrzymaj animację
					changeCurrentFrame(originalRect); // Ustaw oryginalne koordynaty, oryginalny obrazek
				}
			}
		}
		
		return true;
		//updateFrame(); // Pozostałość po pracy z dodatkowymi wątkami
	}
	else return false; // Jeśli animacja została zatrzymana
}

void Animation::updateAnimations()
{
	if (!runningAnimations.empty())// Jeśli lista obecnie działających animacji nie jest pusta
	{
		for (int i = 0; i < runningAnimations.size(); i++)
		{
			if (runningAnimations[i]->updateFrame()) continue; // Jeśli animacja pracuje, odliczaj dalej i zostaw ją w spokoju
			else runningAnimations.erase(runningAnimations.begin() + i); // Jeśli wcześniej dodana animacja przestała pracować (np. Została zatrzymana), wywal ją z listy
		}
	}
}


