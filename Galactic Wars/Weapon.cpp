#include "Weapon.h"

Weapon::~Weapon()
{
}

Weapon::Weapon()
{
	ID = 1;
	firepower = 1;
	automatic = false;
	bulletsPerSecond = 0;
	speedBullet = 1.25;

	firedBullets = 0;

	//////////////////////////////////////////////////////////////////////////

	setMagazineCapacity(5);

	string nameTexture = "playerBullet1";

	// Ustawianie wygl¹du broni
	setImageToSprite(bulletSprite, nameTexture);

	//////////////////////////////////////////////////////////////////////////

	clickedButton = false;
	elapsedTime = 0;
}

Weapon::Weapon(unsigned int ID, unsigned int firepower, float speedBullet, unsigned int numberBullets, string nameTexture)
{
	this->ID = ID;
	this->firepower = firepower;
	this->speedBullet = speedBullet;

	setMagazineCapacity(numberBullets);
	firedBullets = 0;

	//////////////////////////////////////////////////////////////////////////

	automatic = false;
	bulletsPerSecond = 0;

	//////////////////////////////////////////////////////////////////////////

	// Ustawianie wygl¹du broni
	setImageToSprite(bulletSprite, nameTexture); // Ustawia wygl¹d pocisków
	
	//////////////////////////////////////////////////////////////////////////

	clickedButton = false;
}

Weapon::Weapon(unsigned int ID, unsigned int firepower, float speedBullet, unsigned int numberBullets, bool automatic, unsigned int bulletsPerSecond, string nameTexture)
{
	this->ID = ID;
	this->firepower = firepower;
	this->speedBullet = speedBullet;

	setMagazineCapacity(numberBullets);
	firedBullets = 0;
	
	//////////////////////////////////////////////////////////////////////////

	this->automatic = automatic;
	this->bulletsPerSecond = bulletsPerSecond;

	//////////////////////////////////////////////////////////////////////////

	// Ustawianie wygl¹du pocisków
	setImageToSprite(bulletSprite, nameTexture);

	//////////////////////////////////////////////////////////////////////////

	clickedButton = false;
}

int Weapon::getMagazineCapacity()
{
	return magazineCapacity;
}

void Weapon::setMagazineCapacity(int numberBullets)
{
	magazineCapacity = numberBullets;
}

void Weapon::setBulletSprite(Sprite sprite)
{
	setSpriteFromSprite(bulletSprite, sprite);
}

Bullet *Weapon::fireBullet(float xPos, float yPos)
{
	return fireBullet(Vector2f(xPos, yPos));
}

Bullet *Weapon::fireBullet(Vector2f startBulletPosition)
{
	// Prze³aduj jeœli wystrzelono wszystkie pociski i ¿aden aktualnie NIE leci:
	if (!Keyboard::isKeyPressed(Keyboard::Space) &&
		getFiredBullets() >= getMagazineCapacity() &&
		flyingBullets.size() == 0 &&
		clickedButton == false)
	{
		setFiredBullets(0);
	}

	// Jeœli broñ jest automatyczna, odblokuj automatyczne strzelanie
	if (Keyboard::isKeyPressed(Keyboard::Space) && isAutomatic())
	{
		time = clock.restart();
		elapsedTime += time.asMilliseconds();

		float timeToShot = 1000 / getBulletsPerSecond(); // Czas po którym ma zostaæ wystrzelony kolejny pocisk (w milisek.)

		if (elapsedTime >= timeToShot) // Jeœli ju¿ czas wystrzeliæ pocisk
		{
			clickedButton = false;
			elapsedTime = 0;
			clock.restart(); // Zerowanie timera
		}
	}
	else // Jeœli nie klikniêto spacji wyzeruj liczniki
	{
		elapsedTime = 0;
		clock.restart(); // Zerowanie timera
	}

	// Strzelanie
	if (Keyboard::isKeyPressed(Keyboard::Space) &&
		getFiredBullets() < getMagazineCapacity() &&
		clickedButton == false)
	{
		firedBullets++;

		Bullet bullet = createBullet();

		bullet.setPosition(startBulletPosition); // Ustawia pocisk do wystrza³u nad postaæ gracza

		flyingBullets.push_back(bullet);

		clickedButton = true;

		return &flyingBullets.back();
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space) && clickedButton == true)
	{
		clickedButton = false;
	}

	return NULL;
}

Bullet Weapon::createBullet()
{
	return Bullet(firepower, bulletSprite);
}

void Weapon::moveAllFlyingBullets()
{
	if (!flyingBullets.empty()) // Jeœli w tej chwili leci jakiœ pocisk
	{
		for (int i = 0; i < flyingBullets.size(); i++)
		{
			// Przesuwaj pocisk dopóki jest w polu widzenie
			if (flyingBullets[i].getPosition().y > -flyingBullets[i].getTextureRect().height)
				flyingBullets[i].move(0, -speedBullet);
			else
				flyingBullets.erase(flyingBullets.begin() + i);
		}
	}
}

unsigned int Weapon::getFirepower()
{
	return firepower;
}

unsigned int Weapon::getID()
{
	return ID;
}

bool Weapon::isAutomatic()
{
	return automatic;
}

unsigned int Weapon::getBulletsPerSecond()
{
	return bulletsPerSecond;
}

unsigned int Weapon::getFiredBullets()
{
	return firedBullets;
}

Sprite Weapon::getBulletSprite()
{
	return bulletSprite;
}

void Weapon::setFirepower(unsigned int newFirepower)
{
	firepower = newFirepower;
}

void Weapon::setID(unsigned int newID)
{
	ID = newID;
}

void Weapon::setAutomat(bool isAutomatic)
{
	automatic = isAutomatic;
}

void Weapon::setBulletsPerSecond(unsigned int newValue)
{
	bulletsPerSecond = newValue;
}

void Weapon::setFiredBullets(unsigned int newValue)
{
	firedBullets = newValue;
}

