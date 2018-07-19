#include "Player.h"


Player::Player()
{
	HP = 2;
	speed = 0.5;

	setWeapon(Weapon());

	canMove = true;

	// Ustawianie tekstury Player
	setImageToSprite(*this, "player");

	a_death = Animation(*this, 125, true);

	// Pobieranie klatek animacji
	// Animacja wybuchu gracza
	for (int i = 0; i < 3; i++)
	{
		string nameTexture = "explodingPlayer" + intToString(i + 1);
		IntRect tmp = getRect(nameTexture);
		a_death.addFrame(tmp);
	}

	//CollisionGroup<Sprite, Sprite> collid;
	
}


Player::~Player()
{

}

/*void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite);
}*/

int Player::getHP()
{
	return HP;
}

float Player::getSpeed()
{
	return speed;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void Player::setHP(int newHP)
{
	HP = newHP;
}

void Player::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void Player::setWeapon(Weapon schemeWeapon)
{
	weapon = schemeWeapon;
}

Bullet *Player::fireBullet()
{
	float xPosBullet = centerPosition(weapon.bulletSprite, *this); // Wyœrodkowana pozycja pocisku wzglêdem gracza w poziomie
	float heightBullet = weapon.bulletSprite.getGlobalBounds().height;

	return weapon.fireBullet(xPosBullet, this->getPosition().y - heightBullet);
}

void Player::movePlayer(RenderWindow & window)
{
	if (window.hasFocus() && canMove == true)
	{
		Vector2f mouse(Mouse::getPosition(window)); // Pozycja myszy wzglêdem okna

		if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) // W lewo
			&& (this->getPosition().x > 0))
		{
			this->move(-speed, 0);
			//this->rotate(-0.5);
		}

		else if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) // W prawo
			&& (this->getPosition().x < GameInfo::widthWindow - this->getGlobalBounds().width))
		{
			this->move(speed, 0);
			//this->rotate(0.5);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) // W gore
			&& (this->getPosition().y > 0))
		{
			this->move(0, -speed);
			//this->rotate(-0.5);
		}

		else if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) // W dol
			&& (this->getPosition().y < GameInfo::heightWindow - this->getGlobalBounds().height))
		{
			this->move(0, speed);
			//this->rotate(0.5);
		}
	}
}

