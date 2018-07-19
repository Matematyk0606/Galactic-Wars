#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <unordered_map>
#include "GameInfo.h"
#include "Caption.h"
#include "File.h"
//#include "Collidable.h"

using namespace sf;
using namespace std;

IntRect getRect(string nameTexture); // Pobiera koordynaty pojedynczej tekstury
void setSpriteFromSprite(Sprite &newSprite, Sprite &spriteWithTexture); // Ustawia Spritowi teksturê z innego Sprita
void setImageToSprite(Sprite & sprite, string nameTexture = "");

/////////////////////////////////////////////////////////////////////////////////////////
// PONI¯SZY KOD DZIA£A, W PRZYPADKU WYST¥PIENIA B£ÊDÓW NIE MODYFIKUJ TEGO KODU !!! 
// B£¥D MUSI BYÆ W WYWO£ANIU PONI¯SZYCH FUNKCJI !!!
/////////////////////////////////////////////////////////////////////////////////////////

/*float centerPosition(FloatRect &object1, FloatRect object2, bool horizontal = true, bool set = false) // Oblicza po³o¿enie obiektu by by³ na œrodku wzglêdem innego obiektu
{
	if (horizontal == false)
	{
		float object1Height = object1.height;
		float object2Height = object2.height;

		float object1PositionY = object2Height / 2 - object1Height / 2 + object2.getPosition().y; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object1.setPosition(object1.getPosition().x, object1PositionY);

		return object1PositionY;
	}
	else if (horizontal == true)
	{
		float object1Width = object1.getGlobalBounds().width;
		float object2Width = object2.getGlobalBounds().width;

		float object1PositionX = object2Width / 2 - object1Width / 2 + object2.getPosition().x; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object1.setPosition(object1PositionX, object1.getPosition().y);

		return object1PositionX;
	}
}*/

template<class ClassType1>
float centerPosition(ClassType1 &object, bool horizontal = true, bool set = false) // Oblicza po³o¿enie obiektu by by³ na œrodku ekranu w poziomie lub pionie
{
	if (horizontal == false)
	{
		float objectHeight = object.getGlobalBounds().height;
		float windowHeight = GameInfo::heightWindow;

		float objectPositionY = windowHeight / 2 - objectHeight / 2; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object.setPosition(object.getPosition().y, objectPositionY);

		return objectPositionY;
	}
	else if (horizontal == true)
	{
		float objectWidth = object.getGlobalBounds().width;
		float windowWidth = GameInfo::widthWindow;

		float objectPositionX = windowWidth / 2 - objectWidth / 2; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object.setPosition(objectPositionX, object.getPosition().y);

		return objectPositionX;
	}
}

template<class ClassType1, class ClassType2>
float centerPosition(ClassType1 &object1, ClassType2 object2, bool horizontal = true, bool set = false) // Oblicza po³o¿enie obiektu by by³ na œrodku wzglêdem innego obiektu
{
	if (horizontal == false)
	{
		float object1Height = object1.getGlobalBounds().height;
		float object2Height = object2.getGlobalBounds().height;

		float object1PositionY = object2Height / 2 - object1Height / 2 + object2.getPosition().y; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object1.setPosition(object1.getPosition().x, object1PositionY);

		return object1PositionY;
	}
	else if (horizontal == true)
	{
		float object1Width = object1.getGlobalBounds().width;
		float object2Width = object2.getGlobalBounds().width;

		float object1PositionX = object2Width / 2 - object1Width / 2 + object2.getPosition().x; // Obliczanie nowego po³o¿enia na ekranie

		if (set == true)
			object1.setPosition(object1PositionX, object1.getPosition().y);

		return object1PositionX;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

class GraphicsController
{
public:
	GraphicsController();

	void slideBackground(RenderWindow &window);  // Przesuwa i wyœwietla t³o 

	// T³o
	Sprite background;
	Sprite background2;

	File texturePackTXT;
	static unordered_map<string, IntRect>texturesRect;

	// Atlas tekstur
	static Texture texturePack;

	string errorLoad; // Komunikat wyœwietlany przy b³êdzie podczas otwieraia lub pobierania jakiejœ wartoœci z pliku

private:
	void loadCoordinates(); // £aduje koordynaty tekstur w atlasie tekstur

	bool loadTexturePack(Texture &texture, string path); // £aduje teksturê z dysku
};


