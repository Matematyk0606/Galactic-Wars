#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameInfo.h"
#include "Weapon.h"
#include "GraphicsController.h"
#include "Animation.h"
//#include "Collidable.h"

using namespace sf;
using namespace std;

class Player : public Sprite
{
	public:
		Player();
		~Player();

		void movePlayer(RenderWindow &window); // Przesuwa obiekt

		int getHP();
		float getSpeed();

		void setHP(int newHP);
		void setSpeed(float newSpeed);

		void setWeapon(Weapon schemeWeapon);
		Bullet *fireBullet(); // Wystrza� pocisku, je�li strzelono zwraca 'true'

		Animation a_death; // Animacja �mierci, a_ = animation

		Weapon weapon;

		bool canMove; // Czy mo�e si� porusza�; Je�li zginie zmienna ta jest r�wna jest 'false'

	private:

		int HP;
		float speed; // pr�dko�� statku
};

template<class ClassType>
inline ClassType * Player::getThisObject()
{
	return this
}
