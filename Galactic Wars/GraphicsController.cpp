#include "GraphicsController.h"

// Statyczne obiekty klasy 'GraphicsController', kt�re TRZEBA zadeklarowa�
Texture GraphicsController::texturePack = Texture();
unordered_map<string, IntRect> GraphicsController::texturesRect = unordered_map<string, IntRect>();

unordered_map<string, IntRect>*texturesRect = &GraphicsController::texturesRect;

IntRect getRect(string nameTexture)
{
	// Przeszukiwanie tablicy asocjacyjnej w celu odnalezienia po��danych koordynat�w
	unordered_map<string, IntRect>::const_iterator foundValues = texturesRect->find(nameTexture);

	if (foundValues != texturesRect->end()) // Je�li znalaz� porz�dane koordynaty
	{
		return foundValues->second;
	}
	else
	{
		cout << "Nie odnaleziono koordynatow tekstury o nazwie '" << nameTexture << "'" << endl;
		return IntRect();
	}
}

void  setSpriteFromSprite(Sprite &newSprite, Sprite &spriteWithTexture)
{
	//newSprite.setTexture(*spriteWithTexture.getTexture(), true); // Zmiana ca�ej tekstury
	newSprite.setTexture(*spriteWithTexture.getTexture(), true);
	newSprite.setTextureRect(spriteWithTexture.getTextureRect());;
}

void setImageToSprite(Sprite & sprite, string nameTexture)
{
	sprite.setTexture(GraphicsController::texturePack);

	if ((nameTexture != "") && (!texturesRect->empty())) // Je�li szukana textura jest ustawiona i vector nie jest pusty
	{
		IntRect tmp = getRect(nameTexture);
		if (tmp != IntRect())
		{
			// Ustawianie tekstury z atlasu tekstur
			sprite.setTextureRect(tmp); // Ustawia odpowiedni� tekstur� z atlasu tekstur
		}
	}
}



GraphicsController::GraphicsController()
{
	errorLoad = "\n\nProgram nie mo�e kontynuowa� dalszego dzia�ania.\nProsz� zainstalowa� go ponownie lub pobra� poprawny plik 'texturePack' ze strony http://updatesgames.cba.pl/download/Galactic-Wars/texturePack.php lub skontaktowa� si� z autorem \n(email : matematyk.tmobile@gmail.com)";

	/////////////////////////////////////////////////////////////////////////////
	//�adowanie atlasu tekstur
	/////////////////////////////////////////////////////////////////////////////
	if (loadTexturePack(texturePack, "img/texturePack.png"))
	{
		//Komunikat z b��dem
	}
	
	if(texturePackTXT.openFile("img/texturePack.txt"))
	{
		loadCoordinates();

		// T�o
		setImageToSprite(background, "background");
		background2.setTexture(texturePack);
		setSpriteFromSprite(background2, background);
		background2.setPosition(0, -GameInfo::heightWindow);
	}
	else
	{
		string textAlert = "Wyst�pi� b��d podczas pr�by pobrania zawarto�ci pliku 'texturePack'." + errorLoad;
		MessageBoxA(NULL, textAlert.c_str(), "Nie mo�na skorzysta� z pliku!", MB_ICONSTOP);
		exit(0);
	}

}

void GraphicsController::slideBackground(RenderWindow &window)
{
	if (background.getPosition().y <= GameInfo::heightWindow)
		background.move(0, 0.25);
	if (background2.getPosition().y <= GameInfo::heightWindow)
		background2.move(0, 0.25);

	if (background.getPosition().y == 0)
		background2.setPosition(background2.getPosition().x, -GameInfo::heightWindow);
	if (background2.getPosition().y == 0)
		background.setPosition(background.getPosition().x, -600);

	window.draw(background);
	window.draw(background2);
}

bool GraphicsController::loadTexturePack(Texture & texture, string path)
{
	if (texture.loadFromFile(path)) return true;
	else return false;
}

void GraphicsController::loadCoordinates()
{
	vector<string> contentFile = texturePackTXT.getContent();

	if (!contentFile.empty()) // Je�li vector nie jest pusty
	{
		texturesRect.clear();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Zgrywanie ka�dej linijki pliku tekstowego to tablicy asocjacyjnej
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < contentFile.size(); i++) // Odpowiada za sprawdzenie ka�dej linijki pliku
		{
			string line = contentFile[i]; // 1 linia z pliku
			if (line == "") continue; // Pomijaj puste linie

			size_t foundPosition = line.find(" = "); // Szuka znaku '=' w celu rozpocz�cia pobierania koordynat�w tekstur
			bool error = false;

			if (foundPosition != string::npos) // Je�li znalaz�
			{
				string nameTexture; // Nazwa tekstury wprowadzana do tablicy asocjacyjnej
				nameTexture.assign(line, 0, foundPosition); // Pobieranie nazwy tekstury z pliku

				IntRect coordinates; // Ostateczne koordynaty
				string string_coordinates[4]; // Tymczasowa tablica na koordynaty (Z liczbami w postai tekstu)
				int int_coordinates[4]; // Tymczasowa tablica na koordynaty (Z liczbami)

				// Pobieranie ka�dego z 4 koordynat�w
				for (int j = foundPosition + 3, coordinateNumber = 0; j < line.length(); j++) // '+ 3' poniewa� te 3 znaki to ' = ' (Patrz wy�ej); 'coordinateNumber = 0' odpowiada aktualnemu numerowi koordynata
				{
					if (isNumeric(line[j])) // Je�li obecny znak jest cyfr� dodaj go do koordynat�w
						string_coordinates[coordinateNumber] += line[j];
					else
					{
						if (coordinateNumber < 4) coordinateNumber++;
						else goto checkError; // Je�li napotka� wi�cej ni� 3 spacje, przerwij z b��dem
					}
				}

				// Konwersja wczytanych liczb z postaci tekstu na liczby
				for (int i = 0; i < 4; i++) int_coordinates[i] = stringToInt(string_coordinates[i]);

				// Przenie� liczby do obiektu z ostatecznymi koordynatami je�li pobrana wysoko�c i szeroko�� s� wi�ksze od 0
				if (int_coordinates[2] > 0 && int_coordinates[3] > 0)
				{
					coordinates = IntRect(int_coordinates[0], int_coordinates[1], int_coordinates[2], int_coordinates[3]);
					texturesRect.insert({ nameTexture, coordinates });

					cout << line << endl;
				}
				else error = true;
			}
			else error = true;

		checkError:
			if (error == true) cout << "Linia nr " << i + 1 << " w pliku 'img/texturePack' jest bledna!" << endl;
		}

	}
}


/* Stara wersja funkcji 'loadCoordinates()':

void GraphicsController::loadCoordinates()
{
///////////////////////////////////////////////////////////////////////////////////////
// NIE DODANO SPRAWDZENIA PRZYPADKU, W KT�RYM BRAK KT�REJ� WARTO�CI W PLIKU!!!
///////////////////////////////////////////////////////////////////////////////////////

vector<string> contentFile = GraphicsController::texturePackTXT.getContent();

if (!contentFile.empty()) // Je�li vector nie jest pusty
{
string errorLoad = "\n\nProgram nie mo�e kontynuowa� dalszego dzia�ania.\nProsz� zainstalowa� go ponownie lub pobra� poprawny plik 'texturePack' ze strony http://updatesgames.cba.pl/download/Galactic-Wars/texturePack.php lub skontaktowa� si� z autorem \n(email : matematyk.tmobile@gmail.com)";


string string_coordinates[4]; // Tekstowe warto�ci
vector<int> values; // Liczbowe warto�ci
IntRect coordinates;
bool found = false; // Czy znaleziono poszukiwane koordynanty Sprita

// Pierwszy mo�liwy komunikat o b��dzie
string error1 = "Nie odnaleziono po�o�enia tekstury o nazwie: '" + searchTexture + "' w pliku 'texturePack'. " + errorLoad;
// Drugi mo�liwy komunikat o b��dzie 		
string error2 = "Znaleziono poszukiwan� tekstur� ('" + searchTexture + "'), ale jej warto�ci s� b��dnie zapisane w pliku 'texturePack'. " + errorLoad;
string textAlert = error1; // Tekst, kt�ry ostatecznie b�dzie wy�wietlany, b�dzie mia� warto�� 'textAlert1' albo 'textAlert2'

for (int i = 0; i < contentFile.size(); i++) // Sprawdzanie po kolei ka�dego elementu vectora
{
	string line = contentFile[i]; // 1 linia z pliku
	size_t foundPosition = line.find(searchTexture); // Wyszukiwanie

	if (foundPosition != string::npos) // Je�li znalaz�
	{
		cout << line << endl; // Wy�wietla koordynaty tekstury w atlasie tekstur
		if (line[searchTexture.size()] == ' ' && line[searchTexture.size() + 1] == '=' && line[searchTexture.size() + 2] == ' ') // Celowo na pocz�tku bez -1 w tablicy, sprawdzanie nast�pnego znaku; P�niej sprawdzanie jeszcze kolejnego, na ko�cu sprawdzanie 3. z kolei
		{
			int character = searchTexture.size() + 3; // Pierwszy znak pierwszej warto�ci
			for (int j = 0; j < 4; j++) // 4 razy, dla ka�dej warto�ci
			{
				for (int k = character; k < line.size(); k++) // Przeskakiwanie przez ka�dy element wiersza zaczynaj�c od 'character'
				{
					if (line[k] != ' ') // Je�li nie napotka� spacji
					{
						if (line[k] == '0' || line[k] == '1' || line[k] == '2' || line[k] == '3' ||
							line[k] == '4' || line[k] == '5' || line[k] == '6' || line[k] == '7' ||
							line[k] == '8' || line[k] == '9') // Je�li napotka� na cyfr�
							string_coordinates[j] += line[k]; // Liczba kt�rej� z warto�ci
						else // Je�li napotka� b��dny znak (np. liter�) - B��D
						{
							found = false;
							textAlert = error2;
							goto check; // Skok bezwatunkowy; Przejd� bezpo�rednio do wy�wietlenia b��du
						}

					}
					else // Je�li napotka� spacj�, przeskakuje do kolejnej warto�ci w wierszu
					{
						if (line[k + 1] == ' ' || string_coordinates[j].size() == 0) // 1. Je�li wyst�puj� 2 spacje pod rz�d - B��D; 2. Je�li po 'nazwa = ' bezpo�rednio wyst�puje spacja = B��D
						{
							found = false;
							textAlert = error2;
							goto check; // Skok bezwatunkowy; Przejd� bezpo�rednio do wy�wietlenia b��du
						}
						else // Je�li spacja wyst�puje, ale nie jest to ostatnia warto��
						{
							character = k + 1;
							break;
						}
					}
				}
			}
		}
		else
		{
			found = false; // Prawdopodobny b��d w pliku 'texturePack' (NIE by�o zapisu 'nazwa = '), nie przerywaj p�tli, mo�liwe, �e szukane warto�ci wyst�puj� ni�ej w pliku
			textAlert = error1; // error1 poniewa� je�li obecnie sprawdzana linijka, jest poprawna, to oznacza to, �e nie znaleziono szukanej warto�ci
			continue; // Kontynuuj wyszukiwanie
		}


		for (int j = 0; j < 4; j++) // Sprawdza czy zosta�y pobrane wszystkie 4 warto�ci; Kod ten jednak nie dzia�a wedle za�o�e�
		{
			if (string_coordinates[j].size() > 0)
				values.push_back(stringToInt(string_coordinates[j]));
			else break;
		}

		if (values.size() == 4)
		{
			coordinates = IntRect(values[0], values[1], values[2], values[3]);
			found = true;
			break;
		}
		else
		{
			found = false;
			textAlert = error2;
			break; // Tutaj nie potrzeba skoku bezwarunkowego, jeste�my bezpo�rednio w ostatniej p�tli for
		}
	}
}

check: // Skok bezwarunkowy, niezbyt �adny zabieg :(
if (found == false) // Je�li nie znalaz�
{
	//string textAlert = "Nie odnaleziono po�o�enia tekstury o nazwie: '" + searchTexture + "' w pliku 'texturePack'. Program nie mo�e kontynuowa� dalszego dzia�ania. Prosz� zainstalowa� go ponowanie lub skontaktowa� si� z autorem (email: matematyk.tmobile@gmail.com)";
	MessageBox(NULL, textAlert.c_str(), "Nie odnaleziono po�o�enia tekstury!", MB_ICONSTOP); // Wy�wietlanie okienka z powiadomieniem deweloperskim
	exit(0);
}
else if (found == true) // Je�li znalaz�
return coordinates;
	}
}

*/
