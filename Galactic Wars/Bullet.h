#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicsController.h"
//#include "Collidable.h"

using namespace std;
using namespace sf;

class Bullet : public Sprite
{
public:
	Bullet(unsigned int firepower = 1, Sprite bulletSprite = Sprite());
	~Bullet();

	// Przeci��anie operatora ==, mo�liwo�ci por�wnywania obiet�w (Nie do ko�ca rozumiem);
	bool operator==(const Bullet &bullet);

	int getFirepower();
	unsigned int getID();

	void setFirepower(unsigned int firepower);

private:

	unsigned int firepower;

	unsigned int bulletID; // Unikalne ID, ma za zadanie umo�liwienie odr�nienia pocisk�w
};

