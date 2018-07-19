#include "Menu.h"


Menu::Menu()
{
	loadedData = false;
}

Menu::Menu(RenderWindow & window, GraphicsController & graphicsController, AudioController & audioController, Font & font, GameInfo & gameInfo)
{
	this->window = &window;
	this->graphicsController = &graphicsController;
	this->audioController = &audioController;
	this->font = &font;
	this->gameInfo = &gameInfo;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ustawianie wartoœci napisów w menu g³ównym
	mainOptions.push_back(Caption(font, "Start Gry!"));
	mainOptions.push_back(Caption(font, "Ustawienia"));
	mainOptions.push_back(Caption(font, "Info"));
	mainOptions.push_back(Caption(font, "Wyjscie"));

	for (int i = 0; i < mainOptions.size(); i++)
	{
		mainOptions[i].setCharacterSize(30);
		mainOptions[i].setPosition(centerPosition(mainOptions[i]), (295 + i * (mainOptions[i].getGlobalBounds().height + 50))); // Ustawianie pozycji ka¿dego z napisów
	}

	currentOptions = mainOptions;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ustawianie napisów w menu ustawieñ
	settingsHeader = Caption(font, "Dzwiek");
	settingsHeader.setCharacterSize(60);
	settingsHeader.setPosition(centerPosition(settingsHeader), 25);

	settingsOptions.push_back(Caption(font, "Glosnosc muzyki: "));
	settingsOptions.push_back(Caption(font, "Glosnosc dzwiekow: "));
	settingsOptions.push_back(Caption(font, "Powrot"));

	for (int i = 0; i < settingsOptions.size(); i++)
	{
		settingsOptions[i].setCharacterSize(30);
		settingsOptions[i].setPosition(100, (120 + i * (settingsOptions[i].getGlobalBounds().height + 50))); // Ustawianie pozycji ka¿dego z napisów
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ustawianei napisów z menu informacji
	infoHeader = Caption(font, "Informacje");
	infoHeader.setCharacterSize(60);
	infoHeader.setPosition(centerPosition(infoHeader), 25);

	gameInformations.push_back(Caption(font, "Wersja aplikacji: 1.0"));
	gameInformations.push_back(Caption(font, "Autor gry: Ce Pe U"));
	gameInformations.push_back(Caption(font, "Autor czesci grafiki: Ce Pe U"));
	gameInformations.push_back(Caption(font, "Muzyka z menu: SnD Nero v7 All Product Keygen"));
	gameInformations.push_back(Caption(font, "Muzyka z gry: MP2k - UltraEdit11"));

	for (int i = 0; i < gameInformations.size(); i++)
	{
		gameInformations[i].setCharacterSize(30);
		gameInformations[i].setPosition(centerPosition(gameInformations[i]), (120 + i * (gameInformations[i].getGlobalBounds().height + 20))); // Ustawianie pozycji ka¿dego z napisów
	}

	infoOptions.push_back(Caption(font, "Powrot"));
	for (int i = 0; i < infoOptions.size(); i++)
	{
		infoOptions[i].setCharacterSize(30);
		infoOptions[i].setPosition(centerPosition(infoOptions[i]), (500 + i * (infoOptions[i].getGlobalBounds().height + 20))); // Ustawianie pozycji ka¿dego z napisów
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Ustawianie suwaków g³oœnoœci
	sliderBar1.setSize(Vector2f(205, 20));
	sliderBar1.setPosition(GameInfo::widthWindow / 2 + 50, settingsOptions[0].getPosition().y + 9);

	sliderBar2.setSize(Vector2f(205, 20));
	sliderBar2.setPosition(GameInfo::widthWindow / 2 + 50, settingsOptions[1].getPosition().y + 9);

	sliderMovingVol1.setSize(Vector2f(5, 30));
	sliderMovingVol1.setPosition(sliderBar1.getPosition().x + audioController.volumeMusic * 2, centerPosition(sliderMovingVol1, sliderBar1, false));
	sliderMovingVol1.setFillColor(Color::Red);

	sliderMovingVol2.setSize(Vector2f(5, 30));
	sliderMovingVol2.setPosition(sliderBar2.getPosition().x + audioController.volumeSound * 2, centerPosition(sliderMovingVol2, sliderBar2, false));
	sliderMovingVol2.setFillColor(Color::Red);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	selectedOption = 1;

	loadedData = false;
	clickedButton = false;

	loadData();
}

Menu::~Menu()
{
}

void Menu::loadData()
{
	if (window != NULL && graphicsController != NULL &&				 // Jeœli wszystkie niezbêdne
		audioController != NULL && font != NULL && gameInfo != NULL) // Obiekty zosta³y ustawione 
	{
		if (loadedData == false)
		{
			// Ustawianie tekstur
			// Ustawianie tekstury loga
			setImageToSprite(logo, "logo");
			logo.setPosition(centerPosition(logo), 25);

			//Ustawianie tekstury ramki wyboru
			setImageToSprite(border, "border");
			border.setPosition(centerPosition(border), mainOptions[0].getPosition().y-8);

			//ustawianie tekstuy d³ugiej ramki
			setImageToSprite(longBorder, "longBorder");
			longBorder.setPosition(centerPosition(longBorder), 287);

			loadedData = true;
		}
	}
}

bool Menu::changeOption()
{
	int tableSize = currentOptions.size(); // Sprawdza wielkoœæ tablicy z napisami w menu, poniewa¿ dostêpnych jest kilka zestawów napisów

	if ( (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && clickedButton == false ) // W górê
	{
		if (selectedOption > 1) // Jeœli wybrana obecnie opcja nie jest pierwsz¹ dostêpn¹, wtedy mo¿na jeszcze wybraæ opcjê wy¿ej
			selectedOption--;
		else // Jeœli wybrana opcja jest pierwsz¹ dostêpn¹, zmieñ na ostatni¹
			selectedOption = tableSize; // Zmienia numer wybranej opcji na ostatni¹ z dostêpnych

		audioController->playSound("menuClick");

		clickedButton = true; // Blokuje mo¿liwoœæ dalszego klikania
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && clickedButton == false) // W dó³
	{

		if (selectedOption < tableSize) // Jeœli wybrana obecnie opcja jest mniejsza ni¿ ich iloœæ, czyli czy mo¿na wybraæ nastêpn¹
			selectedOption++;
		else // Jeœli wybrana opcja jest ostatnia, zmieñ na pierwsz¹
			selectedOption = 1; // Zmienia obecn¹ opcjê na pierwsz¹ z dostêpnych

		audioController->playSound("menuClick");

		clickedButton = true; // Blokuje mo¿liwoœæ dalszego klikania
	}
	else if ((Keyboard::isKeyPressed(Keyboard::Return) || Keyboard::isKeyPressed(Keyboard::Space)) && clickedButton == false)
	{
		clickedButton = true;
		return true;
	}
	else if( !Keyboard::isKeyPressed(Keyboard::Down) && !Keyboard::isKeyPressed(Keyboard::S) &&  // Jeœli ¿aden przycisk nie jest klikniêty, odblokuj mo¿liwoœæ klikania
			 !Keyboard::isKeyPressed(Keyboard::Up) && !Keyboard::isKeyPressed(Keyboard::W) &&
			 !Keyboard::isKeyPressed(Keyboard::Return) && !Keyboard::isKeyPressed(Keyboard::Space) &&
			 clickedButton == true )
		clickedButton = false; // Odblokowuje mo¿liwoœæ klikania

	return false; // Jeœli nic nie klikniêto
}

void Menu::displayMainMenu()
{
	window->draw(logo);

	for (int i = 0; i < mainOptions.size(); i++)
		window->draw(mainOptions[i]);

	border.setPosition(border.getPosition().x, mainOptions[selectedOption - 1].getPosition().y - 8); // Dzia³a TYLKO dla tej czcionki o rozmiarze 30

	window->draw(border);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (changeOption())
	{
		if (selectedOption == 1) gameInfo->state = GameInfo::GAME;
		else if (selectedOption == 2)
		{
			gameInfo->state = GameInfo::MENU_SETTINGS;
			currentOptions = settingsOptions;
		}
		else if (selectedOption == 3)
		{
			gameInfo->state = GameInfo::MENU_INFO;
			currentOptions = infoOptions;
		}
		else if (selectedOption == 4)
			gameInfo->state = GameInfo::END;

		selectedOption = 1;
	}
}

void Menu::displaySettingsMenu()
{
	// Pog³aszanie i przyciszanie muzyki
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) 
	{
		// Przyciszanie muzyki
		if (selectedOption == 1)
		{
			if (audioController->volumeMusic > 0 &&
				sliderMovingVol1.getPosition().x > sliderBar1.getPosition().x)
			{
				audioController->volumeMusic -= 0.25;
				sliderMovingVol1.move(-0.5, 0);
			}
		}
		// Przyciszanie dŸwiêków
		else if (selectedOption == 2)
		{
			if (audioController->volumeSound > 0 &&
				sliderMovingVol2.getPosition().x > sliderBar2.getPosition().x)
			{
				audioController->volumeSound -= 0.25;
				sliderMovingVol2.move(-0.5, 0);
			}
		}

		audioController->updateVolume();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	{
		// Pog³aszanie muzyki
		if (selectedOption == 1)
		{
			if (audioController->volumeMusic < 100 &&
				sliderMovingVol1.getPosition().x < sliderBar1.getPosition().x + sliderBar1.getGlobalBounds().width)
			{
				audioController->volumeMusic += 0.25;
				sliderMovingVol1.move(+0.5, 0);
			}
		}
		// Pog³aszanie dŸwiêków
		else if (selectedOption == 2)
		{
			if (audioController->volumeSound < 100 &&
				sliderMovingVol2.getPosition().x < sliderBar2.getPosition().x + sliderBar2.getGlobalBounds().width)
			{
				audioController->volumeSound += 0.25;
				sliderMovingVol2.move(+0.5, 0);
			}
		}
		audioController->updateVolume();
	}

	window->draw(settingsHeader);

	for (int i = 0; i < settingsOptions.size(); i++)
		window->draw(settingsOptions[i]);

	longBorder.setPosition(longBorder.getPosition().x, settingsOptions[selectedOption - 1].getPosition().y - 8); // Dzia³a TYLKO dla tej czcionki o rozmiarze 30

	window->draw(sliderBar1);
	window->draw(sliderMovingVol1);

	window->draw(sliderBar2);
	window->draw(sliderMovingVol2);

	window->draw(longBorder);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (changeOption())
	{
		if (selectedOption == 3) 
		{
			gameInfo->state = GameInfo::MENU;
			currentOptions = mainOptions;
		}
		
		selectedOption = 2;
	}
}

void Menu::displayInfoMenu()
{
	window->draw(infoHeader);

	for (int i = 0; i < gameInformations.size(); i++)
		window->draw(gameInformations[i]);

	for (int i = 0; i < infoOptions.size(); i++)
		window->draw(infoOptions[i]);

	border.setPosition(border.getPosition().x, infoOptions[selectedOption - 1].getPosition().y - 8); // Dzia³a TYLKO dla tej czcionki o rozmiarze 30

	window->draw(border);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (changeOption())
	{
		if (selectedOption == 1) 
		{
			gameInfo->state = GameInfo::MENU; 
			currentOptions = mainOptions;
		}

		selectedOption = 3;
	}
}

void Menu::show()
{
	audioController->volumeMusic=50;
	if (loadedData == true)
	{
		while (window->isOpen() && gameInfo->state != GameInfo::GAME && 
			   gameInfo->state != GameInfo::SCORE && gameInfo->state != GameInfo::END)
		{
			Event zdarzenie;
			while (window->pollEvent(zdarzenie))
			{
				if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape)
					window->close();
				if (zdarzenie.type == Event::Closed)
					window->close();
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//updating.updateAllAnimations();

			window->clear();
			graphicsController->slideBackground(*window);
			
			if(gameInfo->state == GameInfo::MENU) displayMainMenu();
			else if (gameInfo->state == GameInfo::MENU_SETTINGS) displaySettingsMenu();
			else if (gameInfo->state == GameInfo::MENU_INFO) displayInfoMenu();

			window->display();
		}
	}
}
