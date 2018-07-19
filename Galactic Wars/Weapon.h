#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GraphicsController.h"
#include <vector>
#include <iostream>
#include "Bullet.h"

using namespace sf;
using namespace std;

class Weapon
{
public:

	friend class Player;

	Weapon(); // Tworzy bro� o ID 1
	Weapon(unsigned int ID, unsigned int firepower, float speedBullet, unsigned int numberBullets, string nameTexture); // Tworzy bro� z podanych ustawie�
	Weapon(unsigned int ID, unsigned int firepower, float speedBullet, unsigned int numberBullets, bool automatic, unsigned int bulletsPerSecond, string nameTexture); // Tworzy bro� z podanych ustawie�
	~Weapon();

	void moveAllFlyingBullets();

	int getMagazineCapacity(); // Pobiera obecn� pojemno�� magazynka
	unsigned int getFirepower();
	unsigned int getID();
	bool isAutomatic();
	unsigned int getBulletsPerSecond();
	unsigned int getFiredBullets();
	Sprite getBulletSprite();

	void setFirepower(unsigned int newFirepower);
	void setID(unsigned int newID);
	void setAutomat(bool isAutomatic);
	void setBulletsPerSecond(unsigned int newValue);
	void setFiredBullets(unsigned int newValue);
	void setMagazineCapacity(int numberBullets); // Ustawia pojemno�� magazynka - ilo�� pocisk�w mo�liwych do wystrzelenia
	void setBulletSprite(Sprite sprite);

	Bullet *fireBullet(float xPos, float yPos);
	Bullet *fireBullet(Vector2f startBulletPosition);

	vector<Bullet> flyingBullets; // Pociski lec�ce w czasie rzeczywistym

private:

	Bullet createBullet();

	Clock clock; // Timer
	Time time; // Obiekt przechowuj�cy czas
	float elapsedTime;

	unsigned int firepower; // Si�a ra�enia
	unsigned int ID; // ID/Poziom broni
	bool automatic; // Automat?
	unsigned int  bulletsPerSecond; // Ilo�� pocisk�w na sekund�
	float speedBullet;

	unsigned int firedBullets; // Liczba wystrzelonych pocisk�w

	unsigned int magazineCapacity; // Pojemno�� magazynka, maksymalna ilo�� dost�pnych pocisk�w

	bool clickedButton; // Czy naci�ni�to spust

	Sprite bulletSprite; // Obraz pocisku
};

