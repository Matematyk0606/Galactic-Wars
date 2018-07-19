#ifndef AUDIOCONTROLLER_H_INCLUDED
#define AUDIOCONTROLLER_H_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace sf;
using namespace std;

class AudioController
{
    public:
    AudioController();
    void addMusic(string path, bool loop, float volume, string name);
    void removeMusic(string name);
	void editMusic(Music & m, bool loop, float volume);
	void playMusic(string name);

	void addSound(string path, float volume, string name);
    void removeSound(string name);
	void editSound(Sound &s, float volume);
	void playSound(string name);

	void updateVolume();

	float volumeMusic;
	float volumeSound;

private:
	bool isMusicExisting(string name);
	bool isSoundExisting(string name);

	// Zwraca wielko�� tablicy z obiektami muzycznymi - Music, czyli ilo�� miejsc na muzyk�
	int getCountOfMusicObjects(); 

	// Statusy dost�pno�ci obiekt�w w u�yciu; 
	// M�wi� czy mo�na za�adowa� muzyk� do jednego z obiekt�w klasy Music
	enum AvailabilityOfMusicObjects 
	{ 
		NOT_IN_USE = 1, // Obiekt nie posiada muzyki i mo�na do niego j� za��dowa�
		IN_USE = 0 // Obiekt w u�yciu, posiada za�adowan� muzyk�, nie wolno �adowa� nowej
	};

	// Tablica asocjacyjna przechowuj�ca informacje o dost�pno�ci 
	// obiekt�w muzycznych do za�adowania nowego pliku z muzyk�
	unordered_map <Music*, AvailabilityOfMusicObjects> availableMusicObjects;
	// Obiekty przechowuj�ce muzyk�; [n] - oznacza maks. liczb� dost�pnych obiekt�w
	Music musicObjects[5]; 
	
	unordered_map <string, Music&> music; // Lista plik�w muzycznych, gotowych do odtworzenia
	unordered_map <string, Sound> sounds; // Lista plik�w d�wi�kowcyh, gotowych do odtworzenia
	unordered_map <string, SoundBuffer> soundBuffers; // Lista obiekt�w przechowuj�cych d�wi�ki

};

#endif // AUDIOCONTROLLER_H_INCLUDED
