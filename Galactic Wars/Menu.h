#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Caption.h"
#include "GraphicsController.h"
#include "AudioController.h"
#include "View.h"

using namespace sf;
using namespace std;

class Menu : project::View
{
public:
	Menu();
	Menu(RenderWindow &window, GraphicsController &graphicsController, AudioController &audioController, Font &font, GameInfo &gameInfo);
	~Menu();

	virtual void show(); 

private:
	void loadData(); // Ustawia wszystkie tekstury, elementy dŸwiêkowe itd.
	bool changeOption();

	void displayMainMenu();
	void displaySettingsMenu();
	void displayInfoMenu();

	// Main Menu
	Sprite logo;
	Sprite border;
	RectangleShape sliderBar1;
	RectangleShape sliderMovingVol1;

	// Settings Menu
	Sprite longBorder;
	Caption settingsHeader;
	RectangleShape sliderBar2;
	RectangleShape sliderMovingVol2;

	// Info Menu
	Caption infoHeader;
	vector<Caption> gameInformations;

	vector<Caption> mainOptions;
	vector<Caption> settingsOptions;
	vector<Caption> infoOptions;
	
	vector<Caption> currentOptions;

	unsigned int selectedOption;

	bool clickedButton;
	bool clickedReturn;
};

