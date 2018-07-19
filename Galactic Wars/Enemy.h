#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicsController.h"
#include "Animation.h"
#include "Weapon.h"

using namespace std;
using namespace sf;

class Enemy : public Sprite
{
public:
	Enemy();
	Enemy(string texturePath, unsigned int HP);
	~Enemy();

	int getHP();
	float getSpeed();

	void setHP(int newHP);
	void setSpeed(float newSpeed);

	void fireTheBullet(); // Wystrza³ pocisku

	static vector<Enemy*> getEnemiesList();

	Weapon weapon;

	Animation a_death; // Animacja œmierci, a_ = animation

private:
	int HP;
	float speed;

	static vector<Enemy*> enemiesList;
};

