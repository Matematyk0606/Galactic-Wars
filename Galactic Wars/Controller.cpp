#include "Controller.h"
#include <conio.h>


Controller::Controller()
{
	window.create(VideoMode(GameInfo::widthWindow, GameInfo::heightWindow, 32), GameInfo::gameName, Style::Titlebar | Style::Close);

	loadFont(font, "iron_man.ttf");

	// Tworzenie obiektu z gr¹
	game = Game(window, graphicsController, audioController, font, gameInfo);
	
	// Tworzenie obiektu wyœwietlaj¹cego menu
	menu = Menu(window, graphicsController, audioController, font, gameInfo);

	gameInfo.state = GameInfo::MENU;

    srand(time(NULL));
}

void Controller::run()
{
    while(true)
    {
        switch(gameInfo.state)
        {

        case GameInfo::MENU:
            showMenu();
            break;

        case GameInfo::GAME:
            runGame();
            break;

		case GameInfo::END:
			exit(0);
			break;

        default:
            showMenu();
            break;
        }
    }
}

Controller & Controller::getReference()
{
	static Controller controller;
	return controller;
}

RenderWindow * Controller::getRenderWindow()
{
	return &window;
}

GraphicsController * Controller::getGraphicsController()
{
	return &graphicsController;
}

AudioController * Controller::getAudioController()
{
	return &audioController;
}

GameInfo * Controller::getGameInfo()
{
	return &gameInfo;
}

Game * Controller::getGameObject()
{
	return &game;
}

Menu * Controller::getMenuObject()
{
	return &menu;
}

Font * Controller::getFont()
{
	return &font;
}

void Controller::runGame()
{
	game.run();
}

void Controller::showFinalScore()
{

}

void Controller::showMenu()
{
	menu.show();
}

	
