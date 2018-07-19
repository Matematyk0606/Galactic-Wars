#include "Game.h"


// Ta linijka znajduje się tutaj, a nie w pliku Game.h,
// ponieważ Controller.h includuje Game.h, a Game.h includuje Controller.h
// co powoduje błąd
#include "Controller.h" 

Game::Game()
{ 
}

Game::Game(RenderWindow & window, GraphicsController & graphicsController, AudioController & audioController, Font & font, GameInfo & gameInfo)
{
	this->window = &window;
	this->graphicsController = &graphicsController;
	this->audioController = &audioController;
	this->font = &font;
	this->gameInfo = &gameInfo;

	paused = false;
	clicked = false;
	loadedData = false;

	// Ustawianie dostępnych schematów broni
	availableWeapons.push_back(Weapon(1, 1, 1.25, 5, "playerBullet1"));
	availableWeapons.push_back(Weapon(2, 2, 1.5, 7, "playerBullet2"));
	availableWeapons.push_back(Weapon(3, 3, 2, 5, "playerBullet3"));
	availableWeapons.push_back(Weapon(4, 7, 2.5, 10, true, 10, "playerBullet4"));
	availableWeapons.push_back(Weapon(5, 10, 3, 10, true, 15, "playerBullet5"));

	loadData();
}

void Game::loadData()
{
	if (window != NULL && graphicsController != NULL &&				 // Jeśli wszystkie niezbędne
		audioController != NULL && font != NULL && gameInfo != NULL) // Obiekty zostały ustawione 
	{
		if (loadedData == false)
		{
			// Ustawianie tekstury Weapon (obecne pociski Player) 
			player.setWeapon(availableWeapons[0]); // Ładowanie 1. schematu broni

			loadedData = true;
		}
	}
}

void Game::run()
{
	// Start muzyki
	audioController->playMusic("gameMusic");
	//audioController.gameMusic.play();

	////////////////////////////////////////////////////////////////////////////////////////


	//Tworzenie napisów
	c_score = Caption(*font, "Punkty: ", 20, 20, 10);


	////////////////////////////////////////////////////////////////////////////////////////

	// Wskaźnij na vector z lecącymi pociskami, w celu skrócenia pisowni
	vector<Bullet> * playerFlyingBullets = &player.weapon.flyingBullets;
		
	//Game *g = getGameObjectReference();

	//Thread collisionThread(&Game::checkCollisions, this);	
	
	/*linb::any a = Sprite();
	Sprite b;
	linb::any_cast<Sprite>(a).getColor();

	CollidingGroup<linb::any, linb::any> c; */

	//collidPlayer.addToMainObjects(player);

	//collidPlayer.addToGroup(enemy1);

	//pBullets_Enemys.setVectorObj1(playerFlyingBullets);

	//pBullets_Enemys.addCollidingObj2(enemy1);

	/*UdpSocket socket;
	IpAddress ipLocal = IpAddress::getPublicAddress();
	IpAddress ipRemote = IpAddress::getPublicAddress();

	cout << IpAddress::getPublicAddress() << endl;

	unsigned short port1 = 5001;
	unsigned short port2 = 5002;

	bool sender;
	cin >> sender;

	if (sender == true)
		socket.bind(port2);
	else 
		socket.bind(port1);*/

	if (loadedData == true)
	{
		while (window->isOpen() && gameInfo->state == GameInfo::GAME)
		{
			sf::Event zdarzenie;
			while (window->pollEvent(zdarzenie))
			{
				if (zdarzenie.type == Event::KeyPressed && zdarzenie.key.code == Keyboard::Escape)
					window->close();
				if (zdarzenie.type == Event::Closed)
					window->close();
				if (zdarzenie.type == Event::LostFocus)
					paused = true;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			pause(); // Sprawdza czy kliknieto P, jeśli tak, pauzuje grę

			if (paused == false)
			{
				player.movePlayer(*window);
			}


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
			
			/*if (sender == true)
			{
				Packet packet;
				Int16 x = 5;
				packet << x;
				if (socket.send(packet,  ipRemote, port2) != sf::Socket::Done)
				{
					cout << "Wysylanie nieudane" << endl;
				}
			}
			else
			{ 
				Packet packet;
				if (socket.receive(packet, ipRemote, port2) == sf::Socket::Done)
				{
					cout << "Cos odebrano" << endl;
					if (packet.getData() != NULL)
					{
						Int16 x;
						packet >> x;
						cout << x << endl;
					}
					else
					{
						cout << "Puste dane" << endl;
					}
				}
				else if(socket.receive(packet, ipRemote, port2) == sf::Socket::NotReady)
				{
					cout << "Nic nie doszlo" << endl;
				}
			}*/

			
			//Odtwarzanie wszystkich uruchomionych animacji
			Animation::updateAnimations();


			// Strzelanie i dźwięk strzału
			Bullet *tmpBullet = player.fireBullet();
			if (tmpBullet != NULL)
			{
				playerBullets_VS_enemies.addToFirstGroup(*tmpBullet);
				audioController->playSound("laserShot");
				cout << player.weapon.flyingBullets.size() << endl;
			}


			// Poruszanie wszystkich wystrzelonych pocisków
			player.weapon.moveAllFlyingBullets();

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// KOLIZJE
			
			// Sprawdzanie wystąpienia kolizji między pociskiem gracza a przeciwnikiem
			/*int *collidedObjects = pBullets_Enemys.checkCollisions(); // Tablica zawierająca numery obiektów, które mogły się zderzyć
			if (collidedObjects != NULL) // Jeśli doszło do jakiejś kolizji
			{
				playerFlyingBullets-a>erase(playerFlyingBullets->begin() + collidedObjects[0]);
				updateScore(1);
			}*/

			/*vector<pair<Player*, Enemy*>> asdf = collidPlayer.checkCollisions();
			if (!asdf.empty()) 
			{ 
				cout << "DZIALA!!!" << endl; 
				asdf[0].first->setPosition(200, 200);
			}*/

			//collisionThread.launch();

			checkCollisions();

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Wyświetlanie grafiki i napisów
			window->clear();
			graphicsController->slideBackground(*window);

			for (int i = 0; i < playerFlyingBullets->size(); i++)
				window->draw(playerFlyingBullets->at(i));

			window->draw(enemy1);

			window->draw(player);
			window->draw(c_score);

			window->display();
		}
	}
}

void Game::pause()
{
	if (Keyboard::isKeyPressed(Keyboard::P) && clicked == false)
	{
		if (paused == false) paused = true;
		else paused = false;

		clicked = true;
	}
	if (!Keyboard::isKeyPressed(Keyboard::P))
		clicked = false;
}

void Game::updateScore(int pointsToAdd)
{
	int score = gameInfo->score += pointsToAdd;
	c_score.setString("Punkty: " + intToString(score));
}

void Game::checkCollisions()
{
	//while (true)
	//{
		// Pobieranie listy wszystkich żyjących przeciwników
		playerBullets_VS_enemies.setSecondGroup(Enemy::getEnemiesList());

		// Sprawdzanie wystąpienia kolizji między 'Głównymi obiektami' a 'Grupą kolizującą'
		vector< pair<Bullet*, Enemy*> > collidedObjectsList = playerBullets_VS_enemies.checkCollisions();

		// Jeśli wystąpiła jakaś kolizja
		if (!collidedObjectsList.empty())
		{
			for (int i = 0; i < collidedObjectsList.size(); i++)
			{
				cout << "kolizja z " << collidedObjectsList[i].first->getID() << endl;
				cout << "W1: " << playerBullets_VS_enemies.getFirstGroup().size() << endl;
				playerBullets_VS_enemies.removeFromFirstGroup(collidedObjectsList[i].first);
				cout << "W2: " << playerBullets_VS_enemies.getFirstGroup().size() << endl;


				vector<Bullet> *tmp = &player.weapon.flyingBullets;
				cout << "B1: " << tmp->size() << endl;
				

				/*vector<Bullet>::iterator iterator;
				iterator = std::find(tmp->begin(), tmp->end(), *collidedObjectsList[i].first);

				if (!tmp->empty())
				{
					tmp->erase(iterator);
					cout << "DELETED" << endl;
				}*/

				/*for (int j = 0; j < tmp->size(); j++)
				{
					if (*collidedObjectsList[i].first == tmp->at(j))
					{
						tmp->erase(tmp->begin() + j);
						cout << "DELETED" << endl;
						break;
					}
				}*/

				/*if (tmp->size() > 1)
				{
					if (tmp->at(0) == tmp->at(1)) cout << "A";
					else cout << "B";
				}*/

				tmp->erase(std::remove(tmp->begin(), tmp->end(), *collidedObjectsList[i].first), tmp->end());
				cout << "B2: " << tmp->size() << endl;

				//cout << "Dziala!!!";
			}
		}
	//}
}

