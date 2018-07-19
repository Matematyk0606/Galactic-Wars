#include "Enemy.h"

vector<Enemy*> Enemy::enemiesList;

Enemy::Enemy()
{
	HP = 1;
	speed = 0.4;

	setImageToSprite(*this, "enemy1");
	setPosition(200, 50);

	a_death = Animation(*this, 125, true);

	enemiesList.push_back(this);
}

Enemy::Enemy(string texturePath, unsigned int HP)
{
	Enemy();
}


Enemy::~Enemy()
{
	for (int i = 0; i <= enemiesList.size() - 1; i++)
	{
		if (enemiesList[i] == this)
		{
			enemiesList.erase(enemiesList.begin() + i);
			break;
		}
	}
}

int Enemy::getHP()
{
	return HP;
}

float Enemy::getSpeed()
{
	return speed;
}

void Enemy::setHP(int newHP)
{
	HP = newHP;
}

void Enemy::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Enemy::fireTheBullet()
{
}

vector<Enemy*> Enemy::getEnemiesList()
{
	return enemiesList;
}
