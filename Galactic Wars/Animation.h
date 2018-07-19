#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Caption.h"
//#include "GraphicsController.h"

using namespace std;
using namespace sf;

class Animation
{
	
public:
	Animation();
	Animation(Sprite & animatedSprite, float frameTime = 200, bool loop = false, vector<IntRect> framesRect = vector<IntRect>());
	~Animation();
	
	static void updateAnimations(); // Po kolei aktualizuje każdą działającą animację

	void play();	// dodaje obecny obiekt do vectora 'runningAnimations'
	void stop();
	void pause();
	
	IntRect getRectOfCurrentFrame(); // Zwraca koordynaty obecnej klatki
	Sprite * getImage(); // Zwraca wskaźnik do oryginalnego Sprita
	vector<IntRect> getRectOfAllFrames(); // Zwraca wszystkie koordynaty wszystkich klatek
	bool isLooped(); // Animacja zapętlona?
	float getFrameTime(); // zwraca czas trwanie jednej klatki

	void replaceExistFrame(unsigned int ID, IntRect coordinates); // ID numerowane od 0 !!!; Podmienia istaniejącą klatkę na inną na podstaie przesłanych koordynatów
	void replaceExistFrame(unsigned int ID, unsigned int x, unsigned int y, unsigned int width, unsigned int height); // ID numerowane od 0 !!!; Jak wyżej ^
	
	void changeCurrentFrame(IntRect frameRect); // Zmienia obecną klatkę animacji
	void changeCurrentFrame(int ID = -1); // Jak wyżej ^, ID numerowane od 0 !!! ID = -1 automatycznie ustawi klatkę na wartość zmiennej 'currentFrame'
	
	void setLoop(bool loop); 
	void setFrameTime(float frameTime);
	void setImage(Sprite & animatedSprite);

	void restoreOriginalRect(); // Przywraca oryginalne koordynaty Sprita, oryginalny obrazek

	void addFrame(IntRect coordinates);						// Dodaje klatkę animacji
	void addFrame(unsigned int x, unsigned int y, unsigned int width, unsigned int height);		// Jak wyżej ^
	
	void removeFrame(int ID); // ID numerowane od 0 !!!
	void reset();
	
	bool isRunning;
	
private:
	bool updateFrame(); // Zarządza sprawdzaniem i zmianą klatki animacji, zwraca 'false' jeśli 'isRunning' równe jest 'false'

	Sprite *image; // Wskaźnik (Bezpośrednie odwołanie) do oryginalnego Sprita podanego w konstruktorze lub w funkcji 'setImage()'

	Clock clock; // Timer
	Time time; // Obiekt przechowujący czas

	vector<IntRect> frames; // Vector z koordynatatmi
	static vector<Animation*> runningAnimations; // Pojemnik na aktualnie pracujące animacje; * ponieważ 'this' zwraca '* const'

	IntRect originalRect;

	//Thread updatingThread; // Wątek odpowiedzialny za zmianę klatki; Pomysł porzucony, zbyt duża ilość błędów oraz brak optymalizacji aplikacji
	
	bool loop;
	float frameTime; // Czas trwania jednej klatki w milisekundach

	float elapsedTime; // Iloś minionego czasu jednej klatki
	int currentFrame; // Numer obecnej klatki

};

#endif

