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

	// Zwraca wielkoœæ tablicy z obiektami muzycznymi - Music, czyli iloœæ miejsc na muzykê
	int getCountOfMusicObjects(); 

	// Statusy dostêpnoœci obiektów w u¿yciu; 
	// Mówi¹ czy mo¿na za³adowaæ muzykê do jednego z obiektów klasy Music
	enum AvailabilityOfMusicObjects 
	{ 
		NOT_IN_USE = 1, // Obiekt nie posiada muzyki i mo¿na do niego j¹ za³¹dowaæ
		IN_USE = 0 // Obiekt w u¿yciu, posiada za³adowan¹ muzykê, nie wolno ³adowaæ nowej
	};

	// Tablica asocjacyjna przechowuj¹ca informacje o dostêpnoœci 
	// obiektów muzycznych do za³adowania nowego pliku z muzyk¹
	unordered_map <Music*, AvailabilityOfMusicObjects> availableMusicObjects;
	// Obiekty przechowuj¹ce muzykê; [n] - oznacza maks. liczbê dostêpnych obiektów
	Music musicObjects[5]; 
	
	unordered_map <string, Music&> music; // Lista plików muzycznych, gotowych do odtworzenia
	unordered_map <string, Sound> sounds; // Lista plików dŸwiêkowcyh, gotowych do odtworzenia
	unordered_map <string, SoundBuffer> soundBuffers; // Lista obiektów przechowuj¹cych dŸwiêki

};

#endif // AUDIOCONTROLLER_H_INCLUDED
