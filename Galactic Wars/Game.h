#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "GameInfo.h"
#include "Player.h"
#include "Enemy.h"
#include "GraphicsController.h"
#include "AudioController.h"
#include "Weapon.h"
#include "File.h"
#include "View.h"
#include "Animation.h"
#include "CollidingGroup.h"
#include "any.hpp"


using namespace sf;
using namespace std;


class Game : project::View
{
    public:
		Game();
		Game(RenderWindow &window, GraphicsController &graphicsController, AudioController &audioController, Font &font, GameInfo &gameInfo);
		void run();

	private:
		void loadData(); // Ustawia wszystkie tekstury, elementy dŸwiêkowe itd.
		void pause(); // Pauzuje grê
		void updateScore(int pointsToAdd);
		void checkCollisions();

		Player player;
		Enemy enemy1;
		vector<Weapon> availableWeapons; // Dostêpne bronie gracza
		//Collisions pBullets_Enemys; // Sprawdzanie kolizji miêdzy pociskami gracza a przeciwnikami
		Caption c_score;
		CollidingGroup<Bullet, Enemy> playerBullets_VS_enemies;

		bool paused;
		bool clicked;
};

#endif // GAME_H_INCLUDED
