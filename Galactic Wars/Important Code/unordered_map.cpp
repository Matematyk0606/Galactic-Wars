// Plik nag��wkowy
#include <unordered_map>

// Tworzenie mapy (tablicy asocjacyjnej)
{
	// Klasa1 - klasa, kt�rej obiekty b�d� indeksami tej tablicy
	// Najcz�ciej s� to typy danych: string, int, float, char
	// Je�li chcemy jednak u�y� innej klasy tablica MUSI przyjmowa� jej wska�niki (patrz ni�ej)

	// Klasa2 - klasa, kt�rej obiekty b�d� zwracane

	unordered_map <string, Klasa2> mapName;
	// Lub
	unordered_map <Klasa1*, Klasa2> mapName;
}

// Zwracanie obiekt�w, kt�re przetrzymuje mapa (tablica asocjacyjna)
{
	mapName[string_LUB_obiektKlasy1];
}

// Przesukiwanie tablicy
{
	// Szukanie po przyjmowanym obiekcie
	unordered_map<string, Klasa2>::const_iterator iterator = mapName.find(stringName);

	if (iterator != mapName.end()) // Je�li znalaz� szukany obiekt
	{
		// Odwo�anie do indeksu, kt�rym szukali�my
		iterator->first;

		// Odwo�anie do znalezionej zawarto�ci tablicy
		iterator->second;
	}
	else // Je�li go nie znalaz�
	{

	}


	// Przeskakiwanie ca�ej tablicy
	unordered_map<string, Klasa2>::iterator iterator = mapName.begin();

	while (iterator != mapName.end())
	{
		// Dzia�anie na poszczeg�lnych obiektach...
		{
			// Mo�liwe odwo�ania
			iterator->first;
			iterator->second;
		}

		iterator++;
	}
}