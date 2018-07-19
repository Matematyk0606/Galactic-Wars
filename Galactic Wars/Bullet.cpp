#include "Bullet.h"




Bullet::Bullet(unsigned int firepower, Sprite bulletSprite)
{
	setFirepower(firepower);
	setSpriteFromSprite(*this, bulletSprite);

	// Losowanie ID dla danego pocisku
	bulletID = (rand() % 10000 + 1);
}


Bullet::~Bullet()
{
}

bool Bullet::operator==(const Bullet & bullet)
{
	return (firepower == bullet.firepower && 
			bulletID == bullet.bulletID);
}

int Bullet::getFirepower()
{
	return firepower;
}

unsigned int Bullet::getID()
{
	return bulletID;
}

void Bullet::setFirepower(unsigned int firepower)
{
	this->firepower = firepower;
}
