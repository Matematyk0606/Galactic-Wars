#include "GraphicsController.h"

// Statyczne obiekty klasy 'GraphicsController', które TRZEBA zadeklarowaæ
Texture GraphicsController::texturePack = Texture();
unordered_map<string, IntRect> GraphicsController::texturesRect = unordered_map<string, IntRect>();

unordered_map<string, IntRect>*texturesRect = &GraphicsController::texturesRect;

IntRect getRect(string nameTexture)
{
	// Przeszukiwanie tablicy asocjacyjnej w celu odnalezienia po¿¹danych koordynatów
	unordered_map<string, IntRect>::const_iterator foundValues = texturesRect->find(nameTexture);

	if (foundValues != texturesRect->end()) // Jeœli znalaz³ porz¹dane koordynaty
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
	//newSprite.setTexture(*spriteWithTexture.getTexture(), true); // Zmiana ca³ej tekstury
	newSprite.setTexture(*spriteWithTexture.getTexture(), true);
	newSprite.setTextureRect(spriteWithTexture.getTextureRect());;
}

void setImageToSprite(Sprite & sprite, string nameTexture)
{
	sprite.setTexture(GraphicsController::texturePack);

	if ((nameTexture != "") && (!texturesRect->empty())) // Jeœli szukana textura jest ustawiona i vector nie jest pusty
	{
		IntRect tmp = getRect(nameTexture);
		if (tmp != IntRect())
		{
			// Ustawianie tekstury z atlasu tekstur
			sprite.setTextureRect(tmp); // Ustawia odpowiedni¹ teksturê z atlasu tekstur
		}
	}
}



GraphicsController::GraphicsController()
{
	errorLoad = "\n\nProgram nie mo¿e kontynuowaæ dalszego dzia³ania.\nProszê zainstalowaæ go ponownie lub pobraæ poprawny plik 'texturePack' ze strony http://updatesgames.cba.pl/download/Galactic-Wars/texturePack.php lub skontaktowaæ siê z autorem \n(email : matematyk.tmobile@gmail.com)";

	/////////////////////////////////////////////////////////////////////////////
	//£adowanie atlasu tekstur
	/////////////////////////////////////////////////////////////////////////////
	if (loadTexturePack(texturePack, "img/texturePack.png"))
	{
		//Komunikat z b³êdem
	}
	
	if(texturePackTXT.openFile("img/texturePack.txt"))
	{
		loadCoordinates();

		// T³o
		setImageToSprite(background, "background");
		background2.setTexture(texturePack);
		setSpriteFromSprite(background2, background);
		background2.setPosition(0, -GameInfo::heightWindow);
	}
	else
	{
		string textAlert = "Wyst¹pi³ b³¹d podczas próby pobrania zawartoœci pliku 'texturePack'." + errorLoad;
		MessageBoxA(NULL, textAlert.c_str(), "Nie mo¿na skorzystaæ z pliku!", MB_ICONSTOP);
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

	if (!contentFile.empty()) // Jeœli vector nie jest pusty
	{
		texturesRect.clear();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Zgrywanie ka¿dej linijki pliku tekstowego to tablicy asocjacyjnej
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < contentFile.size(); i++) // Odpowiada za sprawdzenie ka¿dej linijki pliku
		{
			string line = contentFile[i]; // 1 linia z pliku
			if (line == "") continue; // Pomijaj puste linie

			size_t foundPosition = line.find(" = "); // Szuka znaku '=' w celu rozpoczêcia pobierania koordynatów tekstur
			bool error = false;

			if (foundPosition != string::npos) // Jeœli znalaz³
			{
				string nameTexture; // Nazwa tekstury wprowadzana do tablicy asocjacyjnej
				nameTexture.assign(line, 0, foundPosition); // Pobieranie nazwy tekstury z pliku

				IntRect coordinates; // Ostateczne koordynaty
				string string_coordinates[4]; // Tymczasowa tablica na koordynaty (Z liczbami w postai tekstu)
				int int_coordinates[4]; // Tymczasowa tablica na koordynaty (Z liczbami)

				// Pobieranie ka¿dego z 4 koordynatów
				for (int j = foundPosition + 3, coordinateNumber = 0; j < line.length(); j++) // '+ 3' poniewa¿ te 3 znaki to ' = ' (Patrz wy¿ej); 'coordinateNumber = 0' odpowiada aktualnemu numerowi koordynata
				{
					if (isNumeric(line[j])) // Jeœli obecny znak jest cyfr¹ dodaj go do koordynatów
						string_coordinates[coordinateNumber] += line[j];
					else
					{
						if (coordinateNumber < 4) coordinateNumber++;
						else goto checkError; // Jeœli napotka³ wiêcej ni¿ 3 spacje, przerwij z b³êdem
					}
				}

				// Konwersja wczytanych liczb z postaci tekstu na liczby
				for (int i = 0; i < 4; i++) int_coordinates[i] = stringToInt(string_coordinates[i]);

				// Przenieœ liczby do obiektu z ostatecznymi koordynatami jeœli pobrana wysokoœc i szerokoœæ s¹ wiêksze od 0
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
// NIE DODANO SPRAWDZENIA PRZYPADKU, W KTÓRYM BRAK KTÓREJŒ WARTOŒCI W PLIKU!!!
///////////////////////////////////////////////////////////////////////////////////////

vector<string> contentFile = GraphicsController::texturePackTXT.getContent();

if (!contentFile.empty()) // Jeœli vector nie jest pusty
{
string errorLoad = "\n\nProgram nie mo¿e kontynuowaæ dalszego dzia³ania.\nProszê zainstalowaæ go ponownie lub pobraæ poprawny plik 'texturePack' ze strony http://updatesgames.cba.pl/download/Galactic-Wars/texturePack.php lub skontaktowaæ siê z autorem \n(email : matematyk.tmobile@gmail.com)";


string string_coordinates[4]; // Tekstowe wartoœci
vector<int> values; // Liczbowe wartoœci
IntRect coordinates;
bool found = false; // Czy znaleziono poszukiwane koordynanty Sprita

// Pierwszy mo¿liwy komunikat o b³êdzie
string error1 = "Nie odnaleziono po³o¿enia tekstury o nazwie: '" + searchTexture + "' w pliku 'texturePack'. " + errorLoad;
// Drugi mo¿liwy komunikat o b³êdzie 		
string error2 = "Znaleziono poszukiwan¹ teksturê ('" + searchTexture + "'), ale jej wartoœci s¹ b³êdnie zapisane w pliku 'texturePack'. " + errorLoad;
string textAlert = error1; // Tekst, który ostatecznie bêdzie wyœwietlany, bêdzie mia³ wartoœæ 'textAlert1' albo 'textAlert2'

for (int i = 0; i < contentFile.size(); i++) // Sprawdzanie po kolei ka¿dego elementu vectora
{
	string line = contentFile[i]; // 1 linia z pliku
	size_t foundPosition = line.find(searchTexture); // Wyszukiwanie

	if (foundPosition != string::npos) // Jeœli znalaz³
	{
		cout << line << endl; // Wyœwietla koordynaty tekstury w atlasie tekstur
		if (line[searchTexture.size()] == ' ' && line[searchTexture.size() + 1] == '=' && line[searchTexture.size() + 2] == ' ') // Celowo na pocz¹tku bez -1 w tablicy, sprawdzanie nastêpnego znaku; PóŸniej sprawdzanie jeszcze kolejnego, na koñcu sprawdzanie 3. z kolei
		{
			int character = searchTexture.size() + 3; // Pierwszy znak pierwszej wartoœci
			for (int j = 0; j < 4; j++) // 4 razy, dla ka¿dej wartoœci
			{
				for (int k = character; k < line.size(); k++) // Przeskakiwanie przez ka¿dy element wiersza zaczynaj¹c od 'character'
				{
					if (line[k] != ' ') // Jeœli nie napotka³ spacji
					{
						if (line[k] == '0' || line[k] == '1' || line[k] == '2' || line[k] == '3' ||
							line[k] == '4' || line[k] == '5' || line[k] == '6' || line[k] == '7' ||
							line[k] == '8' || line[k] == '9') // Jeœli napotka³ na cyfrê
							string_coordinates[j] += line[k]; // Liczba którejœ z wartoœci
						else // Jeœli napotka³ b³êdny znak (np. literê) - B£¥D
						{
							found = false;
							textAlert = error2;
							goto check; // Skok bezwatunkowy; PrzejdŸ bezpoœrednio do wyœwietlenia b³êdu
						}

					}
					else // Jeœli napotka³ spacjê, przeskakuje do kolejnej wartoœci w wierszu
					{
						if (line[k + 1] == ' ' || string_coordinates[j].size() == 0) // 1. Jeœli wystêpuj¹ 2 spacje pod rz¹d - B£¥D; 2. Jeœli po 'nazwa = ' bezpoœrednio wystêpuje spacja = B£¥D
						{
							found = false;
							textAlert = error2;
							goto check; // Skok bezwatunkowy; PrzejdŸ bezpoœrednio do wyœwietlenia b³êdu
						}
						else // Jeœli spacja wystêpuje, ale nie jest to ostatnia wartoœæ
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
			found = false; // Prawdopodobny b³¹d w pliku 'texturePack' (NIE by³o zapisu 'nazwa = '), nie przerywaj pêtli, mo¿liwe, ¿e szukane wartoœci wystêpuj¹ ni¿ej w pliku
			textAlert = error1; // error1 poniewa¿ jeœli obecnie sprawdzana linijka, jest poprawna, to oznacza to, ¿e nie znaleziono szukanej wartoœci
			continue; // Kontynuuj wyszukiwanie
		}


		for (int j = 0; j < 4; j++) // Sprawdza czy zosta³y pobrane wszystkie 4 wartoœci; Kod ten jednak nie dzia³a wedle za³o¿eñ
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
			break; // Tutaj nie potrzeba skoku bezwarunkowego, jesteœmy bezpoœrednio w ostatniej pêtli for
		}
	}
}

check: // Skok bezwarunkowy, niezbyt ³adny zabieg :(
if (found == false) // Jeœli nie znalaz³
{
	//string textAlert = "Nie odnaleziono po³o¿enia tekstury o nazwie: '" + searchTexture + "' w pliku 'texturePack'. Program nie mo¿e kontynuowaæ dalszego dzia³ania. Proszê zainstalowaæ go ponowanie lub skontaktowaæ siê z autorem (email: matematyk.tmobile@gmail.com)";
	MessageBox(NULL, textAlert.c_str(), "Nie odnaleziono po³o¿enia tekstury!", MB_ICONSTOP); // Wyœwietlanie okienka z powiadomieniem deweloperskim
	exit(0);
}
else if (found == true) // Jeœli znalaz³
return coordinates;
	}
}

*/
