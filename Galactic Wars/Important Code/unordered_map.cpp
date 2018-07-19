// Plik nag³ówkowy
#include <unordered_map>

// Tworzenie mapy (tablicy asocjacyjnej)
{
	// Klasa1 - klasa, której obiekty bêd¹ indeksami tej tablicy
	// Najczêœciej s¹ to typy danych: string, int, float, char
	// Jeœli chcemy jednak u¿yæ innej klasy tablica MUSI przyjmowaæ jej wskaŸniki (patrz ni¿ej)

	// Klasa2 - klasa, której obiekty bêd¹ zwracane

	unordered_map <string, Klasa2> mapName;
	// Lub
	unordered_map <Klasa1*, Klasa2> mapName;
}

// Zwracanie obiektów, które przetrzymuje mapa (tablica asocjacyjna)
{
	mapName[string_LUB_obiektKlasy1];
}

// Przesukiwanie tablicy
{
	// Szukanie po przyjmowanym obiekcie
	unordered_map<string, Klasa2>::const_iterator iterator = mapName.find(stringName);

	if (iterator != mapName.end()) // Jeœli znalaz³ szukany obiekt
	{
		// Odwo³anie do indeksu, którym szukaliœmy
		iterator->first;

		// Odwo³anie do znalezionej zawartoœci tablicy
		iterator->second;
	}
	else // Jeœli go nie znalaz³
	{

	}


	// Przeskakiwanie ca³ej tablicy
	unordered_map<string, Klasa2>::iterator iterator = mapName.begin();

	while (iterator != mapName.end())
	{
		// Dzia³anie na poszczególnych obiektach...
		{
			// Mo¿liwe odwo³ania
			iterator->first;
			iterator->second;
		}

		iterator++;
	}
}