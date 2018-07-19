#ifndef GAMEINFO_H_INCLUDED
#define GAMEINFO_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class GameInfo
{
public:
    GameInfo();

    int score;

    enum PossibleGameStates { MENU, MENU_SETTINGS, MENU_INFO, GAME, SCORE, END };
    PossibleGameStates state;

    static const int widthWindow = 800;
    static const int heightWindow = 600;
	static constexpr const char* gameName = "Galactic Wars";
};

#endif // GAMEINFO_H_INCLUDED
