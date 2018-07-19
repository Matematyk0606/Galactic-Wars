#include "AudioController.h"

AudioController::AudioController()
{
	volumeMusic = 50;
	volumeSound = 50;

	// Tworzenie i ustawianie statusu dostêpnoœci obiektów z muzyk¹ na dostêpne
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

	// Dzwiêki
	addSound("snd//menuClick.ogg", volumeSound, "menuClick");
	addSound("snd//laserShot.ogg", volumeSound, "laserShot");
}

void AudioController::addMusic(string path, bool loop, float volume, string name)
{
	if (path != "" && (volume >= 0 && volume <= 100) && name != "")
	{
		///////////////////////////////////////////////////////////////////////////////////////
		// Sprawdzanie dostêpnoœci do za³adowania muzyki dostêpnych obiektów klasy Music
		///////////////////////////////////////////////////////////////////////////////////////

		bool foundAvailableObject = false; // Znaleziono wolny obiekt?

		auto iterator = availableMusicObjects.begin();

		// Przeszukiwanie ca³ej tablicy asocjacyjnej w celu znalezienia dostêpnego obiektu
		while (iterator != availableMusicObjects.end())
		{
			// Jeœli obiekt nie jest w u¿yciu (czyli jest dostêpny)
			if (iterator->second == NOT_IN_USE)
			{
				// Otwieranie fizycznego pliku z muzyk¹
				if (iterator->first->openFromFile(path))
				{
					iterator->first->setLoop(loop);
					iterator->first->setVolume(volume);

					// Zmiana statusu obiektu na niedostêpny
					iterator->second = IN_USE;

					// Dodanie oryginalnego obiektu do tablicy z muzyk¹
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
		// Przesukiwanie ca³ej tablicy z obietkami muzycznymi
		unordered_map<string, Music&>::const_iterator musicIterator = music.find(name);

		if (musicIterator != music.end()) // Jeœli znalaz³ muzykê do usuniêcia
		{
			// Zmiana statusu obiektu z muzyk¹ na "dostêpny do u¿cyia"
			availableMusicObjects[&musicIterator->second] = NOT_IN_USE;

			// Usuwanie muzyki z listy dostêpnych obiektów do odtworzenia
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

		if (iterator != music.end()) // Jeœli znalaz³ muzykê do odtworzenia
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

		// Przesukiwanie tablicy asocjacyjnej z muzyk¹
		auto musicIterator = music.begin();
		while (musicIterator != music.end())
		{
			musicIterator->second.setVolume(volumeMusic);
			musicIterator++;
		}

	//Dzwiêki

		// Przesukiwanie tablicy asocjacyjnej z dŸwiêkami
		auto soundIterator = sounds.begin();
		while (soundIterator != sounds.end())
		{
			soundIterator->second.setVolume(volumeSound);
			soundIterator++;
		}
}

bool AudioController::isMusicExisting(string name)
{
	// Przesukiwanie tablicy asocjacyjnej z muzyk¹
	unordered_map<string, Music&>::const_iterator iterator = music.find(name);

	// Jeœli podana muzyk¹ istnieje
	if (iterator != music.end()) return true;
	else return false;
}

bool AudioController::isSoundExisting(string name)
{
	// Przesukiwanie tablicy asocjacyjnej z dŸwiêkami
	unordered_map<string, Sound>::const_iterator iterator = sounds.find(name);

	// Jeœli podany dŸwiêk istnieje
	if (iterator != sounds.end()) return true;
	else return false;
}

int AudioController::getCountOfMusicObjects()
{
	return sizeof(musicObjects) / sizeof(musicObjects[0]);
}
