#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameInfo.h"
#include "Game.h"
#include "Player.h"
#include "Weapon.h"
#include "Menu.h"

using namespace std;
using namespace sf;

class Controller
{
private:

    Controller();
	Controller(const Controller &);

public:
    void run();

	static Controller &getReference();

	RenderWindow *getRenderWindow();
	GraphicsController *getGraphicsController();
	AudioController *getAudioController();
	GameInfo *getGameInfo();
	Game *getGameObject();
	Menu *getMenuObject();
	Font *getFont();

private:
    RenderWindow window;
	GraphicsController graphicsController;
	AudioController audioController;
    GameInfo gameInfo;
	Game game;
	Menu menu;
    Font font;

    void runGame();
    void showFinalScore();
    void showMenu();

	

};

#endif // CONTROLLER_H_INCLUDED
