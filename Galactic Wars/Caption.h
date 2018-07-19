#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Windows.h>

using namespace sf;
using namespace std;

void loadFont(Font &font, string path); // £adowanie czcionki
string intToString(int number);
int stringToInt(string text);
string convertToPolishChars(string text);
void setColorConsoleFont(unsigned int color);
bool isNumeric(string number); // Zwraca true jeœli ca³y napis jest liczb¹ ca³kowit¹ i nie posiada liter ani znaków specjalnych
bool isNumeric(char number); // Zwraca true jeœli dany znak jest liczb¹

class Caption : public Text
{
public:
	Caption();
	Caption(Font & font, string text = "", float x = 0, float y = 0, int size = 20);
	~Caption();
	
	//void setCaptionOptions()
};

