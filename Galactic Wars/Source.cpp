#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Controller.h"
#include <vector>


using namespace std;
using namespace sf;

int main(int argc, char ** argv)
{
	Controller::getReference().run();
}
