#include "AudioController.h"

AudioController::AudioController()
{
	volumeMusic = 50;
	volumeSound = 50;

	// Tworzenie i ustawianie statusu dost�pno�ci obiekt�w z muzyk� na dost�pne
	for (int i = 0; i < getCountOfMusicObjects(); i++)
	{ 
		availableMusicObjects.insert(
		{
			&musicObjects[i], AudioController::NOT_IN_USE
		});
	}

	// Muzyka
	addMusic("snd//menuMusic.ogg", true, volumeMusic, "menuMusic");
	addMusic("snd//gameMusic.ogg", true, volumeMusic, "gameMusic");

	// Dzwi�ki
	addSound("snd//menuClick.ogg", volumeSound, "menuClick");
	addSound("snd//laserShot.ogg", volumeSound, "laserShot");
}

void AudioController::addMusic(string path, bool loop, float volume, string name)
{
	if (path != "" && (volume >= 0 && volume <= 100) && name != "")
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// Sprawdzanie dost�pno�ci do za�adowania muzyki dost�pnych obiekt�w klasy Music
		///////////////////////////////////////////////////////////////////////////////////////

		bool foundAvailableObject = false; // Znaleziono wolny obiekt?

		auto iterator = availableMusicObjects.begin();

		// Przeszukiwanie ca�ej tablicy asocjacyjnej w celu znalezienia dost�pnego obiektu
		while (iterator != availableMusicObjects.end())
		{
			// Je�li obiekt nie jest w u�yciu (czyli jest dost�pny)
			if (iterator->second == NOT_IN_USE)
			{
				// Otwieranie fizycznego pliku z muzyk�
				if (iterator->first->openFromFile(path))
				{
					iterator->first->setLoop(loop);
					iterator->first->setVolume(volume);

					// Zmiana statusu obiektu na niedost�pny
					iterator->second = IN_USE;

					// Dodanie oryginalnego obiektu do tablicy z muzyk�
					music.insert({ name, *iterator->first });
					foundAvailableObject = true;
					break;
				}
			}
			iterator++;
		}


		if (foundAvailableObject == false)
			cout << "Nie mozna dodac muzyki. Brak dostepnych miejsc!" << endl 
				 << "Usun obecnie uzywane lub powieksz limit dostepnych obiektow muzycznych!" << endl << endl;
	}
	else cout << "Nie mozna dodac muzyki '" << path << "'" << endl << endl;
}

void AudioController::removeMusic(string name)
{
	if (name != "" && isMusicExisting(name))
	{
		// Przesukiwanie ca�ej tablicy z obietkami muzycznymi
		unordered_map<string, Music&>::const_iterator musicIterator = music.find(name);

		if (musicIterator != music.end()) // Je�li znalaz� muzyk� do usuni�cia
		{
			// Zmiana statusu obiektu z muzyk� na "dost�pny do u�cyia"
			availableMusicObjects[&musicIterator->second] = NOT_IN_USE;

			// Usuwanie muzyki z listy dost�pnych obiekt�w do odtworzenia
			music.erase(name);
		}
	}
}

/*void AudioController::editMusic(Music &m, bool loop, float volume) // Do poprawy
{
	if (loop != NULL) m.setLoop(loop);
	if (volume != NULL) m.setVolume(volume);
}*/

void AudioController::playMusic(string name)
{
	if (isMusicExisting(name))
	{
		// Przeszukiwanie listy muzyk
		unordered_map<string, Music&>::const_iterator iterator = music.find(name);

		if (iterator != music.end()) // Je�li znalaz� muzyk� do odtworzenia
			iterator->second.play();
	}
}

void AudioController::addSound(string path, float volume, string name)
{
	if (path != "" && (volume >= 0 && volume <= 100) && name != "")
	{
		soundBuffers.insert({name, SoundBuffer()});

		if (soundBuffers[name].loadFromFile(path))
		{
			Sound sound;
			sound.setBuffer(soundBuffers[name]);
			sound.setVolume(volume);

			sounds.insert({ name, sound });
		}
	}
	else cout << "Nie mozna dodac dzwieku '" << path << "'" << endl << endl;
}

void AudioController::removeSound(string name)
{
	if (name != "" && isSoundExisting(name)) sounds.erase(name);
}

/*void AudioController::editSound(Sound &s, float volume) // Do poprawy
{
	if(volume != NULL) s.setVolume(volume);
}*/

void AudioController::playSound(string name)
{
	if (isSoundExisting(name)) sounds[name].play();
}

void AudioController::updateVolume()
{
	//Muzyka

		// Przesukiwanie tablicy asocjacyjnej z muzyk�
		auto musicIterator = music.begin();
		while (musicIterator != music.end())
		{
			musicIterator->second.setVolume(volumeMusic);
			musicIterator++;
		}

	//Dzwi�ki

		// Przesukiwanie tablicy asocjacyjnej z d�wi�kami
		auto soundIterator = sounds.begin();
		while (soundIterator != sounds.end())
		{
			soundIterator->second.setVolume(volumeSound);
			soundIterator++;
		}
}

bool AudioController::isMusicExisting(string name)
{
	// Przesukiwanie tablicy asocjacyjnej z muzyk�
	unordered_map<string, Music&>::const_iterator iterator = music.find(name);

	// Je�li podana muzyk� istnieje
	if (iterator != music.end()) return true;
	else return false;
}

bool AudioController::isSoundExisting(string name)
{
	// Przesukiwanie tablicy asocjacyjnej z d�wi�kami
	unordered_map<string, Sound>::const_iterator iterator = sounds.find(name);

	// Je�li podany d�wi�k istnieje
	if (iterator != sounds.end()) return true;
	else return false;
}

int AudioController::getCountOfMusicObjects()
{
	return sizeof(musicObjects) / sizeof(musicObjects[0]);
}
